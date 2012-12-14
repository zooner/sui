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

SCgObject::ScUriToSCgObjectListMap SCgObject::mScUriToSCgObjects = SCgObject::ScUriToSCgObjectListMap();

const SCgObject::SCgObjectList& SCgObject::objectsByScUri(const ScUri &uri)
{
    ScUriToSCgObjectListMap::iterator it = mScUriToSCgObjects.find(uri);
    if (it != mScUriToSCgObjects.end())
        return it.value();

    static SCgObjectList empty_list;

    return empty_list;
}

SCgObject::SCgObject(QObject *parent) :
    QObject(parent),
    mConstruction(0),
    mParent(0),
    mPosition(0,0)
{
    _resetUpdateFalgs();
}

SCgObject::~SCgObject()
{
    while (!mObservers.empty())
        detachObserver(mObservers.front());

    if (!uri().isEmpty()) _removeSCgObjectFromUriMap(uri());
}

void SCgObject::setUri(const ScUri &_uri)
{
    if (!uri().isEmpty())
        _removeSCgObjectFromUriMap(uri());

    ScObjectInterface::setUri(_uri);

    if (!_uri.isEmpty())
        _appendScgObjectIntoUriMap(_uri);
}

void SCgObject::_appendScgObjectIntoUriMap(const ScUri &uri)
{
    ScUriToSCgObjectListMap::iterator it = mScUriToSCgObjects.find(uri);

    if (it == mScUriToSCgObjects.end())
    {
        SCgObjectList list;
        list.push_back(this);
        mScUriToSCgObjects[uri] = list;
    }else
    {
        SCgObjectList &list = it.value();
        if (list.contains(this))    SuiExcept(SuiExceptionDuplicateItem,
                                              "sc.g-object already exist in that list",
                                              "void SCgObject::_appendScgObjectIntoUriMap(const ScUri &uri)");
        list.push_back(this);
    }
}

void SCgObject::_removeSCgObjectFromUriMap(const ScUri &uri)
{
    ScUriToSCgObjectListMap::iterator it = mScUriToSCgObjects.find(uri);

    if (it != mScUriToSCgObjects.end())
    {
        SCgObjectList &list = it.value();
        if (!list.removeOne(this))
            SuiExcept(SuiExceptionItemNotFound,
                      QString("There are not sc.g-object in list for uri: %1").arg(uri.value()),
                      "void SCgObject::_removeSCgObjectFromUriMap(const ScUri &uri)")
    }else
    {
        SuiExcept(SuiExceptionItemNotFound,
                  QString("There are no any sc.g-object assigned to uri: %1").arg(uri.value()),
                  "void SCgObject::_removeSCgObjectFromUriMap(const ScUri &uri)")
    }
}

void SCgObject::_notifyUpdate(SCgObjectObserver::UpdateEventType eventType)
{
    //mUpdateFlags[(quint32)eventType] = 1;
    SCgObjectObserver *observer = 0;
    foreach(observer, mObservers)
        observer->_update(eventType, this);
        //observer->_needSync();
}

//void SCgObject::notifyObservers()
//{
//    SCgObjectObserver *observer = 0;
//    for (quint32 idx = 0; idx < (quint32)SCgObjectObserver::UpdateEventCount; idx++)
//        if (mUpdateFlags[idx] != 0)
//        {
//            foreach(observer, mObservers)
//                observer->_update((SCgObjectObserver::UpdateEventType)idx, this);
//            mUpdateFlags[idx] = 0;
//        }
//}

void SCgObject::_resetUpdateFalgs()
{
    memset(&mUpdateFlags[0], 0, sizeof(char) * (quint32)SCgObjectObserver::UpdateEventCount);
}

void SCgObject::attachObserver(SCgObjectObserver *observer)
{
    Q_ASSERT(observer);
    if (isObserverAttached(observer)) SuiExcept(SuiExceptionDuplicateItem,
                                                 "Observer already attached",
                                                 "void SCgObject::attachObserver(SCgObjectObserver *observer)");
    mObservers.push_back(observer);
    observer->mObservedObjects.push_back(this);
}

void SCgObject::detachObserver(SCgObjectObserver *observer)
{
    if (!isObserverAttached(observer)) SuiExcept(SuiExceptionItemNotFound,
                                                  "Observer doesn't attached",
                                                  "void SCgObject::detachObserver(SCgObjectObserver *observer)");
    observer->mObservedObjects.removeOne(this);
    mObservers.removeOne(observer);
}

bool SCgObject::isObserverAttached(SCgObjectObserver *observer) const
{
    return mObservers.contains(observer);
}

void SCgObject::setParentObject(SCgObject *parent)
{
    if (parent == mParent) return;

    // remove from old parent
    if (mParent)
        mParent->_removeChild(this);

    mParent = parent;

    // add to new parent
    if (mParent)
        mParent->_appendChild(this);

    _notifyUpdate(SCgObjectObserver::ParentChanged);
}

void SCgObject::setPosition(const QPointF &pos)
{
    if (mPosition == pos) return; // do nothing

    mPosition = pos;
    _notifyUpdate(SCgObjectObserver::PositionChanged);
}

void SCgObject::setSize(const QSizeF &size)
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
