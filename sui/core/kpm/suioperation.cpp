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

#include "../suiprecompiled.h"
#include "suioperation.h"
#include "../suikpm.h"
#include "../suiroot.h"

suiOperation::suiOperation(const QString &_name, QObject *parent) :
    QObject(parent),
    mName(_name),
    mScMemory(0),
    mEventType(ScEventUnknown)
{
}

suiOperation::~suiOperation()
{
}

void suiOperation::init(ScEventType eventType, const ScUri &uri, ScMemoryInterface *memory)
{
    // get sc-memory interface
    mScMemory = (memory != 0) ?  (memory) : (suiRoot::getInstance()->scMemory());
    Q_ASSERT(mScMemory != 0);

    mEventType = eventType;
    mUri = uri;

    // register callback
    if (!mScMemory->connect_callback(mEventType, mUri, this))
        SuiExcept(SuiExceptionInternalError,
                  QString("Can't register callback for operation %1").arg(name()),
                  "void suiOperation::init(ScEventType eventType, const ScUri &uri, ScMemoryInterface *memory)");

    // register operation
    Q_ASSERT(suiRoot::getInstance()->kpm() != 0);
    suiRoot::getInstance()->kpm()->registerOperation(this);
}

void suiOperation::shutdown()
{
    // unregister operation
    Q_ASSERT(suiRoot::getInstance()->kpm() != 0);
    suiRoot::getInstance()->kpm()->unregisterOperation(this);

    // disconnect callback
    mScMemory->disconnect_callback(mEventType, mUri, this);
}

bool suiOperation::eventCallBack(const ScEvent &event)
{
    if (!checkCondition(event))
        return false;

    return run_impl(event);
}

const QString& suiOperation::name() const
{
    return mName;
}
