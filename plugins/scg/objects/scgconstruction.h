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

#ifndef SCGCONSTRUCTION_H
#define SCGCONSTRUCTION_H

#include <QObject>
#include <QList>

#include "scgconstructionobserver.h"

class SCgNode;
class SCgPair;
class SCgContour;
class SCgBus;

/*! Class realize sc.g-construction logic. All algorithms operate with
  * sc.g-constructions. You can append or remove sc.g-object from construction.
  * All layout algorithms operate them.
  * That class allow to create any type of sc.g-object. For that purposes you
  * need to use functions that begins with \e create...
  * Each construction can contains child sc.g-constructions, so you can control
  * their hierarchy.
  */
class SCgConstruction : public QObject
{
    Q_OBJECT
public:
    explicit SCgConstruction(QObject *parent = 0);
    virtual ~SCgConstruction();

protected:
    /*! Call update event callback function for all attached observers
      * @param eventType Update event type
      * @param object Pointer to updated object
      */
    void _notifyUpdate(SCgConstructionObserver::UpdateEventType eventType, QObject *object);

public:
    /*! Attach new observer to construction
      * @param observer Pointer to construction observer, that need to be attached
      */
    void attachObserver(SCgConstructionObserver *observer);

    /*! Detach observer from construction
      * @param observer Pointer to construction observer, that need to be detached
      */
    void detachObserver(SCgConstructionObserver *observer);

    /*! Check if observer attached to sc.g-object
      * @param observer Pointer to observer, that need to be checked
      * @return Return true, if \p observer already attached to this sc.g-construction;
      * otherwise return false.
      */
    bool hasAttachedObserver(SCgConstructionObserver *observer) const;

    /*! Create new sc.g-node in construction
      * @return Return pointer to created sc.g-node
      */
    SCgNode* createNode();

    /*! Create new sc.g-pair object
      * @param beginObject Pointer to begin sc.g-object
      * @param endObject Pointer to end sc.g-object
      *
      * @return Return pointer to created sc.g-pair
      */
    SCgPair* createPair(SCgObject *beginObject = 0, SCgObject *endObject = 0);

    /*! Create new sc.g-contour object
      * @return Return pointer to created sc.g-contour
      */
    SCgContour* createContour();

    /*! Create new sc.g-bus object
      * @return Return pointer to created sc.g-bus
      */
    SCgBus* createBus();

    /*! Destroy specified sc.g-object. It free allocated memory, so
      * all pointer to sc.g-object will be invalid.
      * @param object Pointer to sc.g-object that need to be destroyed
      */
    void destroyObject(SCgObject *object);

    /*! Append object into construction
      * @param object Pointer to sc.g-object that need to be appended into construction
      */
    void appendObject(SCgObject *object);

    /*! Remove object from construction
      * @param object Pointer to sc.g-object that need to be removed
      */
    void removeObject(SCgObject *object);

    /*! Check if specified sc.g-object exist in construction
      * @return Return true, if \p object exists in construction
      */
    bool hasObject(SCgObject *object) const;

protected:
    //! List of attached observers
    QList<SCgConstructionObserver*> mObservers;
    //! List of all objects that contained in construction
    QList<SCgObject*> mObjects;

};

#endif // SCGCONSTRUCTION_H
