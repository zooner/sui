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

#ifndef SCCOREMEMORY_H
#define SCCOREMEMORY_H

#include <QObject>
#include "interfaces/ScMemory.h"
#include <QThread>
#include <libsc/libsc.h>

#define sc_addr2ScUri(x)    (ScUri((quint64)x))

class ScCoreEvent;

class ProcessThread : public QThread
{
    Q_OBJECT
public:
    ProcessThread(QMutex *mutex, const QString &repoPath);
    virtual ~ProcessThread();

    //! Finish process loop
    void finish();
    /*! Wait until memory will be started
      * Use that function to get moment, when sc-core memory initialized.
      * Usage:
      * thread->start();
      * thread->waitStart();
      */
    void waitStart();
    /*! Wait until memory will be shutted down
      * Use that function to get moment, when sc-core memory will be shutted down
      * Usage:
      * thread->finish();
      * thread->waitFinish();
      */
    void waitFinish();

protected:
    //! @see QThread::run
    void run();

protected:
    //! Processor module started flag
    volatile bool mStarted;
    //! Process function finish flag
    volatile bool mFinished;
    //! Synchronization mutex
    QMutex *mMutex;
    //! Path to repository
    QString mRepoPath;
};

class sc_session;

class ScCoreMemory : public QObject,
                     public ScMemoryInterface
{
    Q_OBJECT
    Q_INTERFACES(ScMemoryInterface)

    friend class ScCoreEvent;

    //! structure to store callback data
    struct ScEventCallbackInfo
    {
        explicit ScEventCallbackInfo() :
            event_listener(0),
            type(ScEventUnknown)
        {
        }

        explicit ScEventCallbackInfo(ScEventType _type, const ScUri &_uri) :
            event_listener(0),
            type(_type),
            uri(_uri)
        {
        }

        //! Compare just event type and listened sc-element uri
        bool operator ==(const ScEventCallbackInfo &other) { return (type == other.type) && (uri == other.uri) && !uri.isEmpty(); }

        //! Pointer to event listener for current callback
        ScCoreEvent *event_listener;
        //! Event type
        ScEventType type;
        //! Listened sc-element
        ScUri uri;
    };

public:
    explicit ScCoreMemory(QObject *parent = 0);
    virtual ~ScCoreMemory();

    //! @copydoc ScMemoryInterface::_printEl
    void _printEl(const ScUri &uri);
    //! @copydoc ScMemoryInterface::initialize
    bool initialize(const QString &path);
    //! @copydoc ScMemoryInterface::shutdown
    void shutdown();
    //! @copydoc ScMemoryInterface::gen_el
    ScUri gen_el(const ScElementType &type);
    //! @copydoc ScMemoryInterface::erase_el
    bool erase_el(const ScUri &uri);
    //! @copydoc ScMemoryInterface::set_beg
    bool set_beg(const ScUri &uri, const ScUri &beg_el);
    //! @copydoc ScMemoryInterface::get_beg
    ScUri get_beg(const ScUri &uri);
    //! @copydoc ScMemoryInterface::set_end
    bool set_end(const ScUri &uri, const ScUri &end_el);
    //! @copydoc ScMemoryInterface::get_end
    ScUri get_end(const ScUri &uri);
    //! @copydoc ScMemoryInterface::set_content
    bool set_content(const ScUri &uri, QIODevice &device);
    //! @copydoc ScMemoryInterface::open_content
    QIODevice* open_content(const ScUri &uri);
    //! @copydoc ScMemoryInterface::close_content
    bool close_content(QIODevice *device);
    //! @copydoc ScMemoryInterface::is_content_opened
    bool is_content_opened(const ScUri &uri) const;
    //! @copydoc ScMemoryInterface::find_content
    bool find_content(QIODevice &device, ScUriList &result);
    //! @copydoc ScMemoryInterface::find_str_content
    bool find_str_content(const QString &str, ScUriList &result);
    //! @copydoc ScMemoryInterface::decode_str_content
    QString decode_str_content(QIODevice &device);

    //! @copydoc ScMemoryInterface::set_el_type
    bool set_el_type(const ScUri &uri, const ScElementType &type);
    //! @copydoc ScMemoryInterface::get_el_type
    ScElementType get_el_type(const ScUri &uri) const;
    //! @copydoc ScMemoryInterface::create_iterator
    ScIteratorInterface* create_iterator(const ScTemplate &templ);
    ScIteratorInterface* _create_iterator3(const ScTemplate &templ);
    ScIteratorInterface* _create_iterator5(const ScTemplate &templ);
    //! @see ScMemoryInterface::destroy_iterator
    bool destroy_iterator(ScIteratorInterface *it);
    //! @see ScMemoryInterface::connect_callback
    bool connect_callback(const ScEventType &eventType, const ScUri &uri, ScEventCallbackInterface *callback);
    //! @see ScMemoryInterface::disconnect_callback(ScEventType, ScUri, ScEventCallbackInterface*)
    bool disconnect_callback(const ScEventType &eventType, const ScUri &uri, ScEventCallbackInterface *callback);
    //! @see ScMemoryInterface::disconnect_callback(ScEventCallbackInterface*)
    bool disconnect_callback(ScEventCallbackInterface *callback);

    //! Function that converts sc-type into sc-core types
    static sc_type ScElementType2sc_type(const ScElementType &type);
    //! Function that converts sc-core type into sc-type
    static ScElementType sc_type2ScElementType(const sc_type &type);
    /*! Get sc_addr by ScUri
      * @param uri ScUri of element
      * @return Element sc_addr
      */
    sc_addr getScAddr(const ScUri &uri) const;

    //! Return pointer to global mutex
    static QMutex* globalMutex() { return mGlobalMutex; }

protected:
    /*! Check if element with specified uri exist
      * @param uri ScUri that need to be checked
      * @return Return true, if sc-element with \p uri exist; otherwise return false.
      */
    bool isScUriExist(const ScUri &uri) const;

    /*! Sc-core memory listener class
     */
    class ScCoreSink : public event_sink
    {
    public:
        ScCoreSink(ScCoreMemory *memory, sc_segment *seg) :
            mMemory(memory),
            mSegment(seg)
        {
            Q_ASSERT(mMemory != 0);
            Q_ASSERT(mSegment != 0);
        }

        virtual ~ScCoreSink() {}

        void operator ()(const event_struct &event);

        //! Return pointer to listened segment
        sc_segment* segment() { return mSegment; }

    private:
        //! Pointer to sc-core memory instance to send notifications
        ScCoreMemory *mMemory;
        //! Pointer to listened segment
        sc_segment *mSegment;
    };

    /*! New element generated notification
      * @param sink Pointer to sink that recieve event
      * @param idtf Identifier of generated sc-element
      */
    void _notifyGenElement(ScCoreSink *sink, const QString &idtf);

    /*! Destroy sc-element notification
      * @param sink Pointer to sink that send event
      * @param idtf Identifier of destoyed sc-element
      */
    void _notifyEraseElement(ScCoreSink *sink, const QString &idtf);

    /*! Setup listening to segment
      * @param seg Pointer to segment for listening
      */
    void _listenSegment(sc_segment *seg);

    /*! Notification about segment unlink
      * @param sink Pointer to sink that recieve event
      */
    void _notifySegUnlink(ScCoreSink *sink);

    //! Structure to store information about segment listener
    struct ScSegListenInfo
    {
        ScSegListenInfo() :
            sink(0),
            fifo(0),
            segment(0)
        {

        }

        bool operator ==(const ScSegListenInfo &other)
        {
            return segment == other.segment;
        }

        ScCoreSink *sink;
        event_fifo *fifo;
        sc_segment *segment;
    };

private:
    //! Process function
    static void process(const QString &repoPath);
    //! Pointer to sc-session
    static sc_session *mSession;
    //! Pointer to main segment
    static sc_segment *mSegment;
    //! Processor thread
    static ProcessThread *mProcThread;
    //! Synchronization mutex
    static QMutex *mGlobalMutex;
    //! List of segment listeners
    typedef QList<ScSegListenInfo> ScSegListeners;
    ScSegListeners mSegmentListeners;

    typedef QMap<ScUri, sc_addr> ScUri2ScAddrMap;
    //! Map that convert sc-uri to sc-addr
    static ScUri2ScAddrMap mScUri2ScAddr;

    typedef QMap<QIODevice*, ScUri> Device2ScUriMap;
    typedef QMap<ScUri, QIODevice*> ScUriMap2Device;
    //! Map that store uri for each opened device
    Device2ScUriMap mDevice2ScUri;
    //! Map that store device for each uri
    ScUriMap2Device mScUri2Device;

    typedef QSet<ScIteratorInterface*> ScIteratorSet;
    //! Set of created sc-iterators
    ScIteratorSet mScIterators;

    //! List of callback info structure
    typedef QList<ScEventCallbackInfo*> ScEventCallbackInfoList;
    //! Map of registered callbacks
    typedef QMap<ScEventCallbackInterface*, ScEventCallbackInfoList> ScEventCallbackMap;
    ScEventCallbackMap mEventCallbackMap;




signals:

public slots:

};

class ScCoreMemoryIterator : public QObject,
                             public ScIteratorInterface
{
    friend class ScCoreMemory;

    Q_OBJECT
    Q_INTERFACES(ScIteratorInterface)

protected:
    ScCoreMemoryIterator(sc_iterator *iterator);
    virtual ~ScCoreMemoryIterator();

protected:
    //! @see ScIteratorInterface::has_next
    bool is_over() const;
    //! @see ScIteratorInterface::value
    ScUri value(int num) const;
    //! @see ScIteratorInterface::next
    void next();

private:
    //! Pointer to sc-core iterator
    sc_iterator *mScIterator;
};

class ScCoreMemoryFactory : public QObject,
                            public ScMemoryFactoryInterface
{
    Q_OBJECT
    Q_INTERFACES(ScMemoryFactoryInterface)

public:
    ScCoreMemoryFactory(QObject *parent = 0) :
        QObject(parent)
    {

    }

    virtual ~ScCoreMemoryFactory() {}

    //! @see ScMemoryFactoryInterface::createInstance
    ScMemoryInterface* createInstance()
    {
        return new ScCoreMemory(this);
    }
};

#endif // SCCOREMEMORY_H
