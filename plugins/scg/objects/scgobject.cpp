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
#include "scgobject.h"

SCgObject::SCgObject(QObject *parent) :
    QObject(parent),
    mConstruction(0),
    mParent(0)
{
    _resetUpdateFalgs();
}

SCgObject::~SCgObject()
{
    while (!mObservers.empty())
        detachObserver(mObservers.front());
}

void SCgObject::_notifyUpdate(SCgObjectObserver::UpdateEventType eventType)
{
    mUpdateFlags[(quint32)eventType] = 1;
    SCgObjectObserver *observer = 0;
    foreach(observer, mObservers)
        observer->_needSync();
}

void SCgObject::_sync()
{
    SCgObjectObserver *observer = 0;
    for (quint32 idx = 0; idx < (quint32)SCgObjectObserver::UpdateEventCount; idx++)
        if (mUpdateFlags[idx] != 0)
        {
            foreach(observer, mObservers)
                observer->_update((SCgObjectObserver::UpdateEventType)idx, this);
            mUpdateFlags[idx] = 0;
        }
}

void SCgObject::_resetUpdateFalgs()
{
    memset(&mUpdateFlags[0], 0, sizeof(char) * (quint32)SCgObjectObserver::UpdateEventCount);
}

void SCgObject::attachObserver(SCgObjectObserver *observer)
{
    if (hasAttachedObserver(observer)) SuiExcept(SuiExceptionDuplicateItem,
                                                 "Observer already attached",
                                                 "void SCgObject::attachObserver(SCgObjectObserver *observer)");
    mObservers.push_back(observer);
    observer->mObservedObjects.push_back(this);
}

void SCgObject::detachObserver(SCgObjectObserver *observer)
{
    if (!hasAttachedObserver(observer)) SuiExcept(SuiExceptionItemNotFound,
                                                  "Observer doesn't attached",
                                                  "void SCgObject::detachObserver(SCgObjectObserver *observer)");
    observer->mObservedObjects.removeOne(this);
    mObservers.removeOne(observer);
}

bool SCgObject::hasAttachedObserver(SCgObjectObserver *observer) const
{
    return mObservers.contains(observer);
}

void SCgObject::setParentObject(SCgObject *parent)
{
    if (parent == mParent) return; // do nothing

    if (mParent)
    {
        mParent->_removeChild(this);
        mParent = 0;
    }

    if (mParent != 0)
        mParent->_appendChild(this);

    _notifyUpdate(SCgObjectObserver::ParentChanged);
}

void SCgObject::setPosition(const QPointF &pos)
{
    if (mPosition == pos) return; // do nothing

    mPosition = pos;
    _notifyUpdate(SCgObjectObserver::PositionChanged);
}

void SCgObject::setSize(const QPointF &size)
{
    if (mSize == size) return; // do nothing

    mSize = size;
    _notifyUpdate(SCgObjectObserver::SizeChanged);
}

void SCgObject::setColorForeground(const QColor &color)
{
    if (mColorForeground == color) return; // do nothing

    mColorForeground = color;
    _notifyUpdate(SCgObjectObserver::ForegroundColorChanged);
}

void SCgObject::setColorBackground(const QColor &color)
{
    if (mColorBackground == color) return; // do nothing

    mColorBackground = color;
    _notifyUpdate(SCgObjectObserver::BackgroundColorCahnged);
}

void SCgObject::setIdentifier(const QString &idtf)
{
    if (mIdentifier == idtf) return; // do nothing

    mIdentifier = idtf;
    _notifyUpdate(SCgObjectObserver::IdentifierChanged);
}

void SCgObject::setObjectType(ScElementType _type)
{
    if (mObjectType == _type) return; // do nothing

    mObjectType = _type;
    _notifyUpdate(SCgObjectObserver::TypeChanged);
}

void SCgObject::_removeChild(SCgObject *object)
{
    Q_ASSERT(object != 0); // Null pointer to object
    Q_ASSERT(mChildObjects.removeOne(object)); // There are no specified object in childs list
}

void SCgObject::_appendChild(SCgObject *object)
{
    Q_ASSERT(object != 0); // Null pointer to object
    Q_ASSERT(!mChildObjects.contains(object)); // Specified object already exist
    mChildObjects.push_back(object);
}

QPointF SCgObject::worldPosition() const
{
    return mParent ? (mPosition + mParent->worldPosition()) : mPosition;
}
