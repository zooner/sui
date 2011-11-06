/*
-----------------------------------------------------------------------------
This source file is part of OSTIS (Open Semantic Technology for Intelligent Systems)
For the latest info, see http://www.ostis.net

Copyright (c) 2011 OSTIS

OSTIS is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

OSTIS is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with OSTIS.  If not, see <http://www.gnu.org/licenses/>.
-----------------------------------------------------------------------------
*/

#include "sccorememory.h"
#include "sccoreevent.h"
#include "libsc/libsc.h"
#include "libsc/segment_utils.h"
#include "libpm/pm.h"
#include <libsc/sc_print_utils.h>

#include <QMutexLocker>
#include <QMutex>
#include <QWaitCondition>

sc_session* ScCoreMemory::mSession = 0;
sc_segment* ScCoreMemory::mSegment = 0;
ProcessThread* ScCoreMemory::mProcThread = 0;

QMutex* ScCoreMemory::mGlobalMutex = 0;

ScCoreMemory::ScUri2ScAddrMap ScCoreMemory::mScUri2ScAddr = ScCoreMemory::ScUri2ScAddrMap();

QWaitCondition waitStartStop;

/*! FIXME: Остается одна проблема, при работе sc-памяти в ней могут появлятся sc-элементы,
  * созданные scp-программами, поэтому наш интерфейс памяти ничего про них не знает.
  * Необходимо каким-то образом учесть эту ситуацию
  *
  * Кроме того необходимо отслеживать ситуацию, когда удаление элемента влечет за собой удаление
  * связанных с ним.
  *
  * Выходом является подписка на сообщения от памяти, чтобы синхронизировать ее с данной реализацией.
  */


ProcessThread::ProcessThread(QMutex *mutex, const QString &repoPath) :
    mStarted(false),
    mFinished(false),
    mMutex(mutex),
    mRepoPath(repoPath)
{

}

ProcessThread::~ProcessThread()
{

}

void ProcessThread::finish()
{
    mStarted = false;
}

void ProcessThread::waitStart()
{
    while (!mStarted)
        msleep(10);  // Causes the current thread to sleep for msecs milliseconds.
}

void ProcessThread::waitFinish()
{
    while (!mFinished)
        msleep(10); // Causes the current thread to sleep for msecs milliseconds.
}

void ProcessThread::run()
{
    qDebug() << "Start sc-memory from path: " << mRepoPath << "\n";

    mFinished = false;

    do_init(true, !mRepoPath.isEmpty(), mRepoPath.toStdString());
    do_dedicated(false);

    mStarted = true;

    while (mStarted)
    {
        mMutex->lock();
        do_step();
        mMutex->unlock();
        QThread::msleep(5);
    }
    qDebug() << "Stop sc-memory\n";
    mStarted = false;
    do_deinit();

    mFinished = true;
}


ScCoreMemory::ScCoreMemory(QObject *parent) :
    QObject(parent)
{
}

ScCoreMemory::~ScCoreMemory()
{
}

bool ScCoreMemory::initialize(const QString &path)
{
    mGlobalMutex = new QMutex(QMutex::Recursive);
    mProcThread = new ProcessThread(mGlobalMutex, path);

    mProcThread->start();
    mProcThread->waitStart();


    mSession = get_session();
    if (!mSession) SuiExcept(SuiExceptionInternalError,
                             "Pointer to session is null",
                             "bool ScCoreMemory::initialize(const QString &path)");

    // create main segment
    mSession->create_segment("/work");
    mSegment = mSession->open_segment("/work");

    //_listenSegment(mSession->open_segment("/main/ui"));
    //_listenSegment(mSession->open_segment("/main/etc"));
    _listenSegment(mSession->open_segment("/main"));
    _listenSegment(mSession->open_segment("/info"));

    // listen segment
    _listenSegment(mSegment);

//    /// test
//      sc_segment *seg = mSession->open_segment("/main");
////    sc_addr el = mSession->find_by_idtf("main_", seg);
////    print_el(el);

//      sc_addr e1 = 0;
//      e1 = mSession->find_by_idtf("123", seg);
//      sc_iterator *it = mSession->create_iterator(sc_constraint_new(CONSTR_3_f_a_a, e1, SC_ARC|SC_CONST, 0), true);
//      print_el(e1);
//      if (it->is_over())
//          printf("nothing");

//    ///test


    return true;
}

void ScCoreMemory::shutdown()
{
    mProcThread->finish();
    mProcThread->waitFinish();

    delete mGlobalMutex;
    mGlobalMutex = 0;

    if (mGlobalMutex) delete mGlobalMutex;
    mGlobalMutex = 0;
}

ScUri ScCoreMemory::gen_el(const ScElementType &type)
{    
    QMutexLocker locker(mGlobalMutex);

    // check type
    if (!type.isValid()) SuiExcept(SuiExceptionInvalidParameters,
                                   "Passed invalid sc-element type",
                                   "ScUri ScCoreMemory::gen_el(const ScElementType &type)");

    // create sc-element
    sc_addr addr = mSession->create_el(mSegment, ScElementType2sc_type(type));
    mScUri2ScAddr[sc_addr2ScUri(addr)] = addr;
    return sc_addr2ScUri(addr);
}

bool ScCoreMemory::erase_el(const ScUri &uri)
{
    QMutexLocker locker(mGlobalMutex);

    // trying to find sc_addr
    sc_addr addr = getScAddr(uri);
    mScUri2ScAddr.remove(uri);
    mSession->erase_el(addr);

    return true;
}

bool ScCoreMemory::set_beg(const ScUri &uri, const ScUri &beg_el)
{
    QMutexLocker locker(mGlobalMutex);

    // check if sc-element \p uri exist
    sc_addr sc_el = getScAddr(uri);
    sc_addr sc_beg_el = getScAddr(beg_el);

    ScElementType type = sc_type2ScElementType(mSession->get_type(sc_el));
    // check type
    if (!type.isArcOrEdge()) SuiExcept(SuiExceptionInvalidParameters,
                                       QString("Sc-element with uri=%1 isn't arc or edge").arg(uri.value()),
                                       "bool ScCoreMemory::set_beg(const ScUri &uri, const ScUri &beg_el)");

    mSession->set_beg(sc_el, sc_beg_el);
    return true;
}

ScUri ScCoreMemory::get_beg(const ScUri &uri)
{
    QMutexLocker locker(mGlobalMutex);

    sc_addr sc_el = getScAddr(uri);

    ScElementType type = sc_type2ScElementType(mSession->get_type(sc_el));
    if (!type.isArcOrEdge() || !type.isValid())   SuiExcept(SuiExceptionInvalidParameters,
                                                            "One of arguments have invalid type",
                                                            "ScUri ScCoreMemory::get_beg(const ScUri &uri)");

    // get begin element
    sc_addr sc_beg = mSession->get_beg(sc_el);

    // append it into convertion map
    if (sc_beg != 0)    mScUri2ScAddr[sc_addr2ScUri(sc_beg)] = sc_beg;

    return sc_addr2ScUri(sc_beg);
}

bool ScCoreMemory::set_end(const ScUri &uri, const ScUri &end_el)
{
    QMutexLocker locker(mGlobalMutex);

    sc_addr sc_el = getScAddr(uri);
    sc_addr sc_end_el = getScAddr(end_el);

    ScElementType type = sc_type2ScElementType(mSession->get_type(sc_el));
    // check type
    if (!type.isArcOrEdge()) SuiExcept(SuiExceptionInvalidParameters,
                                       QString("Sc-element with uri=%1 isn't arc or edge").arg(uri.value()),
                                       "bool ScCoreMemory::set_beg(const ScUri &uri, const ScUri &beg_el)");




    mSession->set_end(sc_el, sc_end_el);
    return true;
}

ScUri ScCoreMemory::get_end(const ScUri &uri)
{
    QMutexLocker locker(mGlobalMutex);

    sc_addr sc_el = getScAddr(uri);

    ScElementType type = sc_type2ScElementType(mSession->get_type(sc_el));
    if (!type.isArcOrEdge() || !type.isValid())   SuiExcept(SuiExceptionInvalidParameters,
                                                            "One of arguments have invalid type",
                                                            "ScUri ScCoreMemory::get_end(const ScUri &uri)");

    // get end element
    sc_addr sc_end = mSession->get_end(sc_el);

    // append it into convertion map
    if (sc_end != 0)    mScUri2ScAddr[sc_addr2ScUri(sc_end)] = sc_end;

    return sc_addr2ScUri(sc_end);

}

bool ScCoreMemory::set_content(const ScUri &uri, QIODevice &device)
{
    QMutexLocker locker(mGlobalMutex);

    // set type
    sc_addr el = getScAddr(uri);

    // check element type
    ScElementType type = sc_type2ScElementType(mSession->get_type(el));
    //if (!(type & ScLink)) ScExceptionInvalidType().raise();

    // copy data from device
    device.open(QIODevice::ReadOnly);
    QByteArray data = device.readAll();
    // create content data
    Content cont = Content::data(data.size(), (void*)data.constData());
    cont.set_type(TCDATA);
    int ret = mSession->set_content(el, cont);
    device.close();

    return ret == RV_OK;
}

QIODevice* ScCoreMemory::open_content(const ScUri &uri)
{
    QMutexLocker locker(mGlobalMutex);

    sc_addr el = getScAddr(uri);

    // check element type
    ScElementType type = sc_type2ScElementType(mSession->get_type(el));
    //! FIXME: uncomment code when sc-core will support sc-links
//    if (!type.check(ScLink)) SuiExcept(SuiExceptionInvalidParameters,
//                                    "Element 'uri' isn't sc-link",
//                                    "QIODevice* ScCoreMemory::open_content(const ScUri &uri)");

    // create new IODevice for content data
    QBuffer *buffer = new QBuffer(this);
    buffer->open(QIODevice::WriteOnly);
    Content cont = mSession->get_content(mScUri2ScAddr[uri]);
    const Cont &cnt = cont;

    switch (cont.type())
    {
    case TCINT:
        buffer->write((char*)&cnt.i, sizeof(cnt.i));
        break;

    case TCREAL:
        buffer->write((char*)&cnt.r, sizeof(cnt.r));
        break;

    case TCSTRING:
    case TCDATA:
        buffer->write(cnt.d.ptr, cnt.d.size);
        break;
    default:
        qWarning() << QString("Unsupported content type: %1").arg(uri.value());
        break;
    }

    mDevice2ScUri[buffer] = uri;
    mScUri2Device[uri] = buffer;
    buffer->close();
    return buffer;
}

bool ScCoreMemory::close_content(QIODevice *device)
{
    QMutexLocker locker(mGlobalMutex);

    Q_ASSERT(mDevice2ScUri.find(device) != mDevice2ScUri.end());

    ScUri uri = mDevice2ScUri[device];

    mDevice2ScUri.remove(device);
    mScUri2Device.remove(uri);

    delete device;
    return true;
}

bool ScCoreMemory::is_content_opened(const ScUri &uri) const
{
    QMutexLocker locker(mGlobalMutex);

    sc_addr el = getScAddr(uri);

    // check element type
    ScElementType type = sc_type2ScElementType(mSession->get_type(el));
    if (!type.check(ScLink))   SuiExcept(SuiExceptionInvalidParameters,
                                      "Element 'uri' isn't sc-link",
                                      "bool ScCoreMemory::is_content_opened(const ScUri &uri) const");

    return mScUri2Device.find(uri) != mScUri2Device.end();
}

bool ScCoreMemory::find_content(QIODevice &device, ScUriList &result)
{
    QMutexLocker locker(mGlobalMutex);

    // create template content
    device.open(QIODevice::ReadOnly);
    QByteArray data = device.readAll();
    Content cont = Content::data(data.size(), (void*)data.data());
    cont.set_type(TCDATA);

    // result list
    addr_list sc_res;
    mSession->find_by_content(cont, sc_res);
    addr_list::iterator it;
    for (it = sc_res.begin(); it != sc_res.end(); ++it)
    {
        mScUri2ScAddr[sc_addr2ScUri(*it)] = *it;
        result.append(sc_addr2ScUri(*it));
    }

    device.close();

    return !result.isEmpty();
}

bool ScCoreMemory::find_str_content(const QString &str, ScUriList &result)
{
    QBuffer buffer;
    QByteArray data = str.toUtf8();
    data.append((char)0);
    buffer.open(QIODevice::WriteOnly);
    buffer.write(data.data(), data.size());
    buffer.close();

    return find_content(buffer, result);
}

QString ScCoreMemory::decode_str_content(QIODevice &device)
{
    device.open(QIODevice::ReadOnly);
    QByteArray data = device.readAll();
    QString res = QString::fromUtf8(data.data(), data.size() - 1);  // don't use last byte, we have added it manualy
    device.close();
    return res;
}

bool ScCoreMemory::set_el_type(const ScUri &uri, const ScElementType &type)
{
    QMutexLocker locker(mGlobalMutex);

    // check if type is correct
    if (!type.isValid()) SuiExcept(SuiExceptionInvalidParameters,
                                   "Invalid type parameter",
                                   "bool ScCoreMemory::set_el_type(const ScUri &uri, const ScElementType &type)");

    sc_addr addr = getScAddr(uri);

    return mSession->change_type(addr, ScElementType2sc_type(type)) == RV_OK;
}

ScElementType ScCoreMemory::get_el_type(const ScUri &uri) const
{
    QMutexLocker locker(mGlobalMutex);

    // Check if element exist
    ScUri2ScAddrMap::const_iterator it = mScUri2ScAddr.find(uri);
    if (it == mScUri2ScAddr.end())  SuiExcept(SuiExceptionItemNotFound,
                                              QString("Element with uri=%1 doesn't exist").arg(uri.value()),
                                              "ScElementType ScCoreMemory::get_el_type(const ScUri &uri) const")

    return sc_type2ScElementType(mSession->get_type(it.value()));
}

/*! Macros for iterator parameter checking. It check if
  * type is valid, or uri exist. If it's uri, then flag value will be set to 1, else - 0
  */
#define check_iterator_param(param, flag) \
    if ((param).is_uri()) \
    { \
        (flag) = 1; \
        if (!isScUriExist((param).uri())) ScExceptionElementNotExist().raise(); \
    } else \
    { \
        (flag) = 0; \
        if (!isScTypeCorrect((param).type())) ScExceptionInvalidType().raise(); \
    }

ScIteratorInterface* ScCoreMemory::create_iterator(const ScTemplate &templ)
{
    if (templ.count() == 3)
        return _create_iterator3(templ);

    return _create_iterator5(templ);
}

ScIteratorInterface* ScCoreMemory::_create_iterator3(const ScTemplate &templ)
{
    QMutexLocker locker(mGlobalMutex);

    sc_constraint *sc_constr = 0;
    bool flags[3] = {0, 0, 0};

    flags[0] = templ.param(0).is_uri();
    flags[1] = templ.param(1).is_uri();
    flags[2] = templ.param(2).is_uri();

    // get constraint. Possible to do that with bits mask
    if (flags[0] && !flags[1] && !flags[2])
        sc_constr = sc_constraint_new(CONSTR_3_f_a_a,
                                      getScAddr(templ.param(0).uri()),
                                      ScElementType2sc_type(templ.param(1).type()),
                                      ScElementType2sc_type(templ.param(2).type()));
    else
    {
        if (!flags[0] && !flags[1] && flags[2])
            sc_constr = sc_constraint_new(CONSTR_3_a_a_f,
                                          ScElementType2sc_type(templ.param(0).type()),
                                          ScElementType2sc_type(templ.param(1).type()),
                                          getScAddr(templ.param(2).uri()));
        else
        {
            if (flags[0] && !flags[1] && flags[2])
                sc_constr = sc_constraint_new(CONSTR_3_f_a_f,
                                              getScAddr(templ.param(0).uri()),
                                              ScElementType2sc_type(templ.param(1).type()),
                                              getScAddr(templ.param(2).uri()));
        }
    }

    // check if constraint founded
    if (sc_constr == 0) return (ScIteratorInterface*)0;

    ScCoreMemoryIterator *iterator = new ScCoreMemoryIterator(mSession->create_iterator(sc_constr, false));

    mScIterators.insert(iterator);
    return iterator;

}

ScIteratorInterface* ScCoreMemory::_create_iterator5(const ScTemplate &templ)
{
    QMutexLocker locker(mGlobalMutex);

    sc_constraint *sc_constr = 0;
    bool flags[5] = {0, 0, 0, 0, 0};

    flags[0] = templ.param(0).is_uri();
    flags[1] = templ.param(1).is_uri();
    flags[2] = templ.param(2).is_uri();
    flags[3] = templ.param(3).is_uri();
    flags[4] = templ.param(4).is_uri();

    // get constraint. One of: CONSTR_5_a_a_f_a_a, CONSTR_5_a_a_f_a_f,
    // CONSTR_5_f_a_f_a_a, CONSTR_5_f_a_f_a_f, CONSTR_5_a_a_a_a_f,
    // CONSTR_5_f_a_a_a_a, CONSTR_5_f_a_a_a_f

    if (!flags[0] && !flags[1] && flags[2] && !flags[3] && !flags[4]) // CONSTR_5_a_a_f_a_a
        sc_constr = sc_constraint_new(CONSTR_5_a_a_f_a_a,
                                      ScElementType2sc_type(templ.param(0).type()),
                                      ScElementType2sc_type(templ.param(1).type()),
                                      getScAddr(templ.param(2).uri()),
                                      ScElementType2sc_type(templ.param(3).type()),
                                      ScElementType2sc_type(templ.param(4).type()));
    else
    {
        if (!flags[0] && !flags[1] && flags[2] && !flags[3] && flags[4]) // CONSTR_5_a_a_f_a_f
            sc_constr = sc_constraint_new(CONSTR_5_a_a_f_a_f,
                                          ScElementType2sc_type(templ.param(0).type()),
                                          ScElementType2sc_type(templ.param(1).type()),
                                          getScAddr(templ.param(2).uri()),
                                          ScElementType2sc_type(templ.param(3).type()),
                                          getScAddr(templ.param(4).uri()));
        else
        {
            if (flags[0] && !flags[1] && flags[2] && !flags[3] && !flags[4]) // CONSTR_5_f_a_f_a_a
                sc_constr = sc_constraint_new(CONSTR_5_f_a_f_a_a,
                                              getScAddr(templ.param(0).uri()),
                                              ScElementType2sc_type(templ.param(1).type()),
                                              getScAddr(templ.param(2).uri()),
                                              ScElementType2sc_type(templ.param(3).type()),
                                              ScElementType2sc_type(templ.param(4).type()));
            else
            {
                if (flags[0] && !flags[1] && flags[2] && !flags[3] && flags[4]) // CONSTR_5_f_a_f_a_f
                    sc_constr = sc_constraint_new(CONSTR_5_f_a_f_a_f,
                                                  getScAddr(templ.param(0).uri()),
                                                  ScElementType2sc_type(templ.param(1).type()),
                                                  getScAddr(templ.param(2).uri()),
                                                  ScElementType2sc_type(templ.param(3).type()),
                                                  getScAddr(templ.param(4).uri()));
                else
                {
                    if (!flags[0] && !flags[1] && !flags[2] && !flags[3] && flags[4]) // CONSTR_5_a_a_a_a_f
                        sc_constr = sc_constraint_new(CONSTR_5_a_a_a_a_f,
                                                      ScElementType2sc_type(templ.param(0).type()),
                                                      ScElementType2sc_type(templ.param(1).type()),
                                                      ScElementType2sc_type(templ.param(2).type()),
                                                      ScElementType2sc_type(templ.param(3).type()),
                                                      getScAddr(templ.param(4).uri()));
                    else
                    {
                        if (flags[0] && !flags[1] && !flags[2] && !flags[3] && !flags[4]) // CONSTR_5_f_a_a_a_a
                            sc_constr = sc_constraint_new(CONSTR_5_f_a_a_a_a,
                                                          getScAddr(templ.param(0).uri()),
                                                          ScElementType2sc_type(templ.param(1).type()),
                                                          ScElementType2sc_type(templ.param(2).type()),
                                                          ScElementType2sc_type(templ.param(3).type()),
                                                          ScElementType2sc_type(templ.param(4).type()));
                        else
                            if (flags[0] && !flags[1] && !flags[2] && !flags[3] && flags[4]) // CONSTR_5_f_a_a_a_f
                                sc_constr = sc_constraint_new(CONSTR_5_f_a_a_a_f,
                                                              getScAddr(templ.param(0).uri()),
                                                              ScElementType2sc_type(templ.param(1).type()),
                                                              ScElementType2sc_type(templ.param(2).type()),
                                                              ScElementType2sc_type(templ.param(3).type()),
                                                              getScAddr(templ.param(4).uri()));
                    }
                }
            }
        }
    }

    // check if constraint founded
    if (sc_constr == 0) return (ScIteratorInterface*)0;
    ScCoreMemoryIterator *iterator = new ScCoreMemoryIterator(mSession->create_iterator(sc_constr, false));

    mScIterators.insert(iterator);
    return iterator;
}

bool ScCoreMemory::destroy_iterator(ScIteratorInterface *it)
{
    QMutexLocker locker(mGlobalMutex);

    Q_ASSERT(it != 0);

    ScIteratorSet::iterator set_it = mScIterators.find(it);
    if (set_it == mScIterators.end()) SuiExcept(SuiExceptionInvalidParameters,
                                                "Invalid iterator pointer",
                                                "bool ScCoreMemory::destroy_iterator(ScIteratorInterface *it)")

    mScIterators.erase(set_it);
    delete it;

    return true;
}

bool ScCoreMemory::connect_callback(const ScEventType &eventType,
                                    const ScUri &uri,
                                    ScEventCallbackInterface *callback)
{
    QMutexLocker locker(mGlobalMutex);

    // trying to find callback
    ScEventCallbackMap::iterator it = mEventCallbackMap.find(callback);
    if (it != mEventCallbackMap.end())
    {
        ScEventCallbackInfo info(eventType, uri);
        ScEventCallbackInfoList &list = it.value();
        ScEventCallbackInfoList::iterator itL;
        for (itL = list.begin(); itL != list.end(); ++itL)
        {
            if (*(*itL) == info)
                SuiExcept(SuiExceptionDuplicateItem,
                          QString("Event callback %1 (type: %2, uri: %3) already registered").arg((quint32)callback).arg(eventType).arg(uri.value()),
                          "bool ScCoreMemory::connect_callback(const ScEventType &eventType,"
                          "const ScUri &uri,"
                          "ScEventCallbackInterface *callback)");
        }
    }

    ScEventCallbackInfo *info = new ScEventCallbackInfo(eventType, uri);
    info->event_listener = new ScCoreEvent(uri, eventType, "", callback, this, this);

    // append new callback
    if (it != mEventCallbackMap.end())
        it.value().append(info);
    else
        mEventCallbackMap[callback] = ScEventCallbackInfoList() << info;

    return true;
}

bool ScCoreMemory::disconnect_callback(const ScEventType &eventType, const ScUri &uri, ScEventCallbackInterface *callback)
{
    QMutexLocker locker(mGlobalMutex);

    ScEventCallbackMap::iterator it = mEventCallbackMap.find(callback);

    if (it != mEventCallbackMap.end())
    {
        ScEventCallbackInfo info_templ(eventType, uri);

        // iterate all event listeners registered to specified callback and destroy them
        ScEventCallbackInfoList &list = it.value();
        ScEventCallbackInfoList::iterator itL;
        for (itL = list.begin(); itL != list.end(); ++itL)
        {
            ScEventCallbackInfo *info = *itL;
            if (*info == info_templ)
            {
                delete info->event_listener;
                delete info;
                list.erase(itL);

                return true;
            }
        }
    }
    SuiExcept(SuiExceptionItemNotFound,
              QString("Event callback %1 (type: %2, uri: %3) isn't registered").arg((quint32)callback).arg(eventType).arg(uri.value()),
              "bool ScCoreMemory::disconnect_callback(const ScEventType &eventType, const ScUri &uri, ScEventCallbackInterface *callback)");

    return false;
}

bool ScCoreMemory::disconnect_callback(ScEventCallbackInterface *callback)
{
    QMutexLocker locker(mGlobalMutex);

    ScEventCallbackMap::iterator it = mEventCallbackMap.find(callback);

    if (it == mEventCallbackMap.end())
        SuiExcept(SuiExceptionItemNotFound,
                  QString("Callback %1 doesn't registered").arg((quint32)callback),
                  "bool ScCoreMemory::disconnect_callback(ScEventCallbackInterface *callback)");

    // iterate all event listeners registered to specified callback and destroy them
    ScEventCallbackInfoList &list = it.value();
    ScEventCallbackInfoList::iterator itL;
    for (itL = list.begin(); itL == list.end(); ++itL)
    {
        ScEventCallbackInfo *info = *itL;
        delete info->event_listener;
        delete info;
    }

    mEventCallbackMap.erase(it);

    return true;
}

bool ScCoreMemory::isScUriExist(const ScUri &uri) const
{
    return mScUri2ScAddr.find(uri) != mScUri2ScAddr.end();
}

void ScCoreMemory::_printEl(const ScUri &uri)
{
    QMutexLocker locker(mGlobalMutex);

    sc_addr addr = getScAddr(uri);
    print_el(mSession, addr);
}

sc_type ScCoreMemory::ScElementType2sc_type(const ScElementType &type)
{
    sc_type res_type = 0;

    if (type.check(ScNode)) res_type = res_type | SC_NODE;
    if (type.check(ScLink)) res_type = res_type | SC_LINK;

    if (type.check(ScArcMain)) res_type = res_type | SC_ARC_MAIN;
    if (type.check(ScArcCommon)) res_type = res_type | SC_ARC;
    if (type.check(ScEdgeCommon)) res_type = res_type | SC_EDGE;

    if (type.check(ScPos)) res_type = res_type | SC_POS;
    if (type.check(ScNeg)) res_type = res_type | SC_NEG;

    if (type.check(ScConst)) res_type = res_type | SC_CONST;
    if (type.check(ScVar)) res_type = res_type | SC_VAR;
    if (type.check(ScMeta)) res_type = res_type | SC_METAVAR;

    if (type.check(ScTemp)) res_type = res_type | SC_TEMPORARY;
    if (type.check(ScPerm)) res_type = res_type | SC_PERMANENT;

    if (type.check(ScStruct)) res_type = res_type | SC_STRUCT;
    if (type.check(ScTuple)) res_type = res_type | SC_TUPLE;
    if (type.check(ScRole)) res_type = res_type | SC_ROLE;
    if (type.check(ScBinary)) res_type = res_type | SC_BINARY;
    if (type.check(ScConcept)) res_type = res_type | SC_CONCEPT;
    if (type.check(ScAbstract)) res_type = res_type | SC_ABSTRACT;

    return res_type;
}

ScElementType ScCoreMemory::sc_type2ScElementType(const sc_type &type)
{
    ScElementType res_type;

    if (type & SC_NODE) res_type.add(ScNode);
    if (type & SC_LINK) res_type.add(ScLink);
    if (type & SC_ARC) res_type.add(ScArcCommon);
    if (sc_isa(type, SC_ARC_MAIN)) res_type.add(ScArcMain);
    if (type & SC_EDGE) res_type.add(ScEdgeCommon);

    if (type & SC_POS) res_type.add(ScPos);
    if (type & SC_NEG) res_type.add(ScNeg);

    if (type & SC_CONST) res_type.add(ScConst);
    if (type & SC_VAR) res_type.add(ScVar);
    if (type & SC_METAVAR) res_type.add(ScMeta);

    if (type & SC_TEMPORARY) res_type.add(ScTemp);
    if (type & SC_PERMANENT) res_type.add(ScPerm);

    if (type & SC_STRUCT) res_type.add(ScStruct);
    if (type & SC_TUPLE) res_type.add(ScTuple);
    if (type & SC_ROLE) res_type.add(ScRole);
    if (type & SC_BINARY) res_type.add(ScBinary);
    if (type & SC_CONCEPT) res_type.add(ScConcept);
    if (type & SC_ABSTRACT) res_type.add(ScAbstract);

    return res_type;
}



sc_addr ScCoreMemory::getScAddr(const ScUri &uri) const
{
    QMutexLocker locker(mGlobalMutex);

    ScUri2ScAddrMap::const_iterator it = mScUri2ScAddr.find(uri);
    if (it == mScUri2ScAddr.end()) SuiExcept(SuiExceptionItemNotFound,
                                             QString("Element with uri=%1 doesn't exist").arg(uri.value()),
                                             "sc_addr ScCoreMemory::getScAddr(const ScUri &uri) const")
    return it.value();
}

void ScCoreMemory::_notifyGenElement(ScCoreSink *sink, const QString &idtf)
{
    QMutexLocker locker(mGlobalMutex);

    // get sc_addr
    sc_addr addr = mSession->find_by_idtf(idtf.toStdString(), sink->segment());

    if (addr == 0)
        SuiExcept(SuiExceptionItemNotFound,
                  QString("Can't find element with idtf = '%1'").arg(idtf),
                  "void ScCoreMemory::_notifyGenElement(ScCoreSink *sink, const QString &idtf)");

    ScUri uri = sc_addr2ScUri(addr);

    // check if element exist in map
    ScUri2ScAddrMap::iterator it = mScUri2ScAddr.find(uri);
    if (it == mScUri2ScAddr.end())
        mScUri2ScAddr[uri] = addr;
}

void ScCoreMemory::_notifyEraseElement(ScCoreSink *sink, const QString &idtf)
{
    QMutexLocker locker(mGlobalMutex);

    // get sc_addr
    sc_addr addr = mSession->find_by_idtf(idtf.toStdString(), sink->segment());

    if (addr == 0)
        SuiExcept(SuiExceptionItemNotFound,
                  QString("Can't find element with idtf = '%1'").arg(idtf),
                  "void ScCoreMemory::_notifyEraseElement(ScCoreSink *sink, const QString &idtf)");

    ScUri uri = sc_addr2ScUri(addr);

    // check if element exist in map
    ScUri2ScAddrMap::iterator it = mScUri2ScAddr.find(uri);
    if (it == mScUri2ScAddr.end())
        mScUri2ScAddr.erase(it);
}

void ScCoreMemory::_listenSegment(sc_segment *seg)
{
    QMutexLocker locker(mGlobalMutex);

    // check if segment already listened
    ScSegListeners::iterator it;
    for (it = mSegmentListeners.begin(); it != mSegmentListeners.end(); ++it)
        if ((*it).segment == seg)
            return;

    // get all elements from segment
    sc_segment::iterator *it_seg = seg->create_iterator_on_elements();//mSession->create_iterator(sc_constraint_new(CONSTR_ON_SEGMENT, seg, false), true);
    while (!it_seg->is_over())
    {
        sc_addr_ll addr_ll = it_seg->next();
        // skip links
        if (!seg->is_link(addr_ll))
        {
            sc_addr addr = seg->get_element_addr(addr_ll);

            // check if sc-element exist in map
            ScUri uri = sc_addr2ScUri(addr);
            ScUri2ScAddrMap::iterator it_uri = mScUri2ScAddr.find(uri);
            if (it_uri == mScUri2ScAddr.end())
            {
                mScUri2ScAddr[uri] = addr;
                qDebug() << uri.value() << " --- " << mSession->get_idtf(addr).c_str() << "\n";
            }
        }
    }

    // apped new listener
    ScSegListenInfo info;
    info.sink = new ScCoreSink(this, seg);
    info.fifo = new event_fifo(*info.sink);
    info.segment = seg;

    seg->listen_segment(info.fifo);

    mSegmentListeners.append(info);
}

void ScCoreMemory::_notifySegUnlink(ScCoreSink *sink)
{
    QMutexLocker locker(mGlobalMutex);

    ScSegListenInfo info;
    info.sink = sink;

    ScSegListeners::iterator it;
    while (it != mSegmentListeners.end() || (*it).sink != sink)
    if (it == mSegmentListeners.end())
        SuiExcept(SuiExceptionInternalError,
                  QString("Segment already unlinked"),
                  "void ScCoreMemory::_notifySegUnlink(ScCoreSink *sink)");
    info = *it;
    mSegmentListeners.erase(it);

    sc_segment *seg = info.segment;
    info.segment->unlisten_segment(info.fifo);

    delete info.fifo;
    delete info.sink;

    // get all elements from segment and remove them from ScUri map
    sc_segment::iterator *it_seg = seg->create_iterator_on_elements();
    while (!it_seg->is_over())
    {
        sc_addr_ll addr_ll = it_seg->next();
        // skip links
        if (!seg->is_link(addr_ll))
        {
            sc_addr addr = seg->get_element_addr(addr_ll);

            // check if sc-element exist in map
            ScUri uri = sc_addr2ScUri(addr);
            ScUri2ScAddrMap::iterator it_uri = mScUri2ScAddr.find(uri);
            if (it_uri != mScUri2ScAddr.end())
                mScUri2ScAddr.erase(it_uri);
        }
    }
}

/// ---- sink
void ScCoreMemory::ScCoreSink::operator ()(const event_struct &event)
{

    if (event.type == SCEV_GENEL)
        mMemory->_notifyGenElement(this, QString().fromStdString(event.idtf));

    if (event.type == SCEV_ERASEEL)
        mMemory->_notifyEraseElement(this, QString().fromStdString(event.idtf));

    if (event.type == SCEV_UNLINK)
        mMemory->_notifySegUnlink(this);

}

/// ---------------- Iterator -------
ScCoreMemoryIterator::ScCoreMemoryIterator(sc_iterator *iterator) :
    mScIterator(iterator)
{
    Q_ASSERT(mScIterator != 0);
}

ScCoreMemoryIterator::~ScCoreMemoryIterator()
{
    if (mScIterator)    delete mScIterator;
}

bool ScCoreMemoryIterator::is_over() const
{
    QMutexLocker locker(ScCoreMemory::globalMutex());
    return mScIterator->is_over();
}

ScUri ScCoreMemoryIterator::value(int num) const
{
    QMutexLocker locker(ScCoreMemory::globalMutex());
    return sc_addr2ScUri(mScIterator->value(num));
}

void ScCoreMemoryIterator::next()
{
    QMutexLocker locker(ScCoreMemory::globalMutex());
    mScIterator->next();
}


