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

#ifndef SCGOBJECTOBSERVER_H
#define SCGOBJECTOBSERVER_H

#include "scgprerequest.h"

#include <QList>

/*! Class provides interfaces and basical functionality
  * for sc.g-object observer. That class recive update
  * notification messages from observed sc.g-object.
  * To attach observer to sc.g-object, you need to call
  * SCgObject::attachObserver
  *
  * @see SCgObject::UpdateEventType, SCgObject::attachObserver, SCgObject::detachObserver
  */
class SCgObjectObserver
{
    friend class SCgObject;

public:
    /*! Update event types enumeration */
    typedef enum
    {
        AllChanged = 0,             /*! whole object changed */
        PositionChanged,            /*! object position changed */
        SizeChanged,                /*! object size changed */
        ForegroundColorChanged,     /*! object foreground color changed*/
        BackgroundColorCahnged,     /*! object background color changed */
        PointsChanged,              /*! line object points changed*/
        IdentifierChanged,          /*! object identifier changed*/
        IdentifierPositionChanged,  /*! object identifier position changed*/
        IdentifierColorChanged,     /*! object identifier color changed */
        TypeChanged,                /*! object type changed */
        ParentChanged,              /*! parend tobject changed */
        OwnerChanged,               /*! object owner changed (used for sc.g-bus) */
        PairBeginChanged,           /*! sc.g-pair begin object changed */
        PairEndChanged,             /*! sc.g-pair end object changed */
        PairWidthChanged,           /*! sc.g-pair width */
        UpdateEventCount
    } UpdateEventType;

    explicit SCgObjectObserver();
    virtual ~SCgObjectObserver();

    //! Return pointer to observed object by index
    SCgObject* observedObject(quint32 idx) const { return mObservedObjects.at(idx); }

protected:
    /*! Observed object update callback. Calls when observed object
      * has changed.
      * @param eventType Type of update event
      * @param object Pointer to sc.g-object, that was changed
      */
    virtual void _update(UpdateEventType eventType, SCgObject *object) = 0;

    /*! Update notification. That function calls by SCgObject class
      * when it change any state. So it point to observer, that it need to
      * be synchronized with sc.g-object.
      * To synchronize use SCgObject::_sync function
      */
    virtual void _needSync() { mNeedSync = true; }

    /*! Check if observer need to synchronization with sc.g-object
      */
    bool isNeedSync() const { return mNeedSync; }

protected:
    //! List of observed objects
    QList<SCgObject*> mObservedObjects;
    //! Flag to sync
    bool mNeedSync;
};

#endif // SCGOBJECTOBSERVER_H
