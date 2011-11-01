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

#include "sccoreevent.h"
#include "sccorememory.h"

ScCoreEvent::ScCoreEvent(const ScUri &uri, ScEventType type,
                         const QString &name, ScEventCallbackInterface *callbackInterface,
                         ScCoreMemory *memory, QObject *parent) :
    QObject(parent),
    ScOperation(name.toStdString()),
    mUri(uri),
    mCallbackInterface(callbackInterface),
    mType(type),
    mMemory(memory)
{
    Q_ASSERT(mMemory != 0);
    registerOperation();
}

ScCoreEvent::~ScCoreEvent()
{
}

bool ScCoreEvent::activateImpl(sc_addr paramSystem, sc_segment *tmpSegment)
{
    mMemory->_listenSegment(tmpSegment);

    QMutexLocker locker(mMemory->globalMutex());

    ScTemplate search_templ, res_templ;
    ScUri param_uri = sc_addr2ScUri(paramSystem);

    if (mType == ScEventOutputEdgeAdded)
    {
        ScIteratorInterface *iter = mMemory->create_iterator(ScTemplate() << mUri
                                                             << ScElementType(0)
                                                             << ScElementType(0)
                                                             << ScElementType(ScArcMain | ScConst | ScPos)
                                                             << param_uri);
        if (!iter->is_over())
            res_templ << iter->value(0) << iter->value(1) << iter->value(2);

        mMemory->destroy_iterator(iter);
    }

    if (mType == ScEventInputEdgeAddded)
    {
        ScIteratorInterface *iter = mMemory->create_iterator(ScTemplate() << ScElementType(0)
                                                             << ScElementType(0)
                                                             << mUri
                                                             << ScElementType(ScArcMain | ScConst | ScPos)
                                                             << param_uri);
        if (!iter->is_over())
            res_templ << iter->value(0) << iter->value(1) << iter->value(2);

        mMemory->destroy_iterator(iter);
    }

    if (mType == ScEventTypeChanged)
    {
        res_templ << mUri;
    }

    if (mType == ScEventContentChanged)
    {
        res_templ << mUri;
    }

    if (mType == ScEventDeleted)
    {
        res_templ << mUri;
    }

    if (res_templ.count() == 0)
        SuiExcept(SuiExceptionInternalError,
                  QString("Invalid result template"),
                  "bool ScCoreEvent::activateImpl(sc_addr paramSystem, sc_segment *tmpSegment)");

    ScEvent event(mType, mUri, res_templ, mMemory);
    return mCallbackInterface->eventCallBack(event);
}

void ScCoreEvent::genActCond(sc_generator &gen)
{

    sc_addr aset = mMemory->getScAddr(mUri);
    QMutexLocker locker(mMemory->globalMutex());

    if (mType == ScEventOutputEdgeAdded)
    {
        sc_addr e1 = gen.element("", SC_N_VAR);
        sc_addr e3 = gen.element("", SC_N_VAR);
        gen.gen_arc(e1, e3, "", SC_A_VAR|SC_POS);

        bindParam(e1, aset);

        sc_param prm[1];
        prm[0].addr = aset;
        attach_to(system_session, SC_WAIT_HACK_SET_MEMBER, prm, 1);
        return;
    }

    if (mType == ScEventInputEdgeAddded)
    {
        sc_addr e1 = gen.element("", SC_N_VAR);
        sc_addr e3 = gen.element("", SC_N_VAR);
        gen.gen_arc(e1, e3, "", SC_A_VAR|SC_POS);

        bindParam(e3, aset);

        sc_param prm[1];
        prm[0].addr = aset;
        attach_to(system_session, SC_WAIT_HACK_IN_SET, prm, 1);
        return;
    }

    if (mType == ScEventTypeChanged)
    {
        sc_addr e1 = gen.element("", SC_N_VAR);

        bindParam(e1, aset);

        sc_param prm[1];
        prm[0].addr = aset;
        attach_to(system_session, SC_WAIT_CHANGE_TYPE, prm, 1);
        return;
    }

    if (mType == ScEventContentChanged)
    {
        sc_addr e1 = gen.element("", SC_N_VAR);

        bindParam(e1, aset);

        sc_param prm[1];
        prm[0].addr = aset;
        attach_to(system_session, SC_WAIT_CONT, prm, 1);
        return;
    }

    if (mType == ScEventDeleted)
    {
        sc_addr e1 = gen.element("", SC_N_VAR);

        bindParam(e1, aset);

        sc_param prm[1];
        prm[0].addr = aset;
        attach_to(system_session, SC_WAIT_DIE, prm, 1);
        return;
    }

}

bool ScCoreEvent::emitEvent(const ScEvent &event)
{
    Q_ASSERT(mCallbackInterface != 0);
    return mCallbackInterface->eventCallBack(event);
}
