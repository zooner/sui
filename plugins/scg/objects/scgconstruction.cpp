/*
-----------------------------------------------------------------------------
This source file is part of OSTIS (Open Semantic Technology for Intelligent Systems)
For the latest info, see http://www.ostis.net

Copyright (c) 2010 OSTIS

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

#include "scgprecompiled.h"
#include "scgconstruction.h"
#include "scgconstructionobserver.h"

SCgConstruction::SCgConstruction(QObject *parent) :
    QObject(parent)
{
}

SCgConstruction::~SCgConstruction()
{
}

void SCgConstruction::_notifyUpdate(SCgConstructionObserver::UpdateEventType eventType, QObject *object)
{
    SCgConstructionObserver *observer = 0;
    foreach(observer, mObservers)
        observer->_update(eventType, object);
}

void SCgConstruction::attachObserver(SCgConstructionObserver *observer)
{
    Q_ASSERT(observer != 0);

    if (hasAttachedObserver(observer))  SuiExcept(SuiExceptionDuplicateItem,
                                                  "Observer is already attached to sc.g-construction",
                                                  "void SCgConstruction::attachObserver(SCgConstructionObserver *observer)");

    if (observer->mConstruction != 0)
        observer->mConstruction->detachObserver(observer);

    observer->mConstruction = this;
    mObservers.push_back(observer);
}

void SCgConstruction::detachObserver(SCgConstructionObserver *observer)
{
    Q_ASSERT(observer != 0);

    if (!hasAttachedObserver(observer)) SuiExcept(SuiExceptionItemNotFound,
                                                  "Observer doesn't attached to sc.g-construction",
                                                  "void SCgConstruction::detachObserver(SCgConstructionObserver *observer)");

    observer->mConstruction = 0;
    mObservers.removeOne(observer);
}

bool SCgConstruction::hasAttachedObserver(SCgConstructionObserver *observer) const
{
    return mObservers.contains(observer);
}


SCgNode* SCgConstruction::createNode()
{
    SCgNode *node = new SCgNode(this);
    mObjects.push_back(node);
    node->mConstruction = this;

    _notifyUpdate(SCgConstructionObserver::ObjectCreated, node);

    return node;
}

SCgPair* SCgConstruction::createPair(SCgObject *beginObject, SCgObject *endObject)
{
    SCgPair *pair = new SCgPair(this);
    mObjects.push_back(pair);
    pair->mConstruction = this;

    if (beginObject != 0) pair->setBeginObject(beginObject);
    if (endObject != 0) pair->setEndObject(endObject);

    _notifyUpdate(SCgConstructionObserver::ObjectCreated, pair);

    return pair;
}

SCgContour* SCgConstruction::createContour()
{
    SCgContour *contour = new SCgContour(this);
    mObjects.push_back(contour);
    contour->mConstruction = this;

    _notifyUpdate(SCgConstructionObserver::ObjectCreated, contour);

    return contour;
}

SCgBus* SCgConstruction::createBus()
{
    SCgBus *bus = new SCgBus(this);
    mObjects.push_back(bus);
    bus->mConstruction = this;

    _notifyUpdate(SCgConstructionObserver::ObjectCreated, bus);

    return bus;
}

void SCgConstruction::destroyObject(SCgObject *object)
{
    if (!mObjects.removeOne(object)) SuiExcept(SuiExceptionItemNotFound,
                                               "sc.g-object doesn't exist in that construction",
                                               "void SCgConstruction::destroyObject(SCgObject *object)");

    _notifyUpdate(SCgConstructionObserver::ObjectDeleted, object);
    delete object;
}

void SCgConstruction::appendObject(SCgObject *object)
{
    if (mObjects.contains(object)) SuiExcept(SuiExceptionDuplicateItem,
                                             "sc.g-object already exist in this construction",
                                             "void SCgConstruction::appendObject(SCgObject *object)");
    if (object->mConstruction != 0)
        object->mConstruction->removeObject(object);

    object->mConstruction = this;
    mObjects.push_back(object);

    _notifyUpdate(SCgConstructionObserver::ObjectAppended, object);
}

void SCgConstruction::removeObject(SCgObject *object)
{
    if (!mObjects.removeOne(object)) SuiExcept(SuiExceptionItemNotFound,
                                               "sc.g-object doesn't exist",
                                               "void SCgConstruction::removeObject(SCgObject *object)");
    object->mConstruction = 0;

    _notifyUpdate(SCgConstructionObserver::ObjectRemoved, object);
}

bool SCgConstruction::hasObject(SCgObject *object) const
{
    return mObjects.contains(object);
}
