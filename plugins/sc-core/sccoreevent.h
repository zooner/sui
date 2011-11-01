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

#ifndef SCCOREEVENTHANDLER_H
#define SCCOREEVENTHANDLER_H

#include <QObject>
#include <libpm/sc_operation.h>
#include "interfaces/ScMemory.h"

class ScCoreMemory;

class ScCoreEvent : public QObject,
                    public ScOperation
{
    Q_OBJECT
public:
    /*! Construct operation
      * @param uri ScUri of listened sc-element
      * @param type Event type
      * @param name Operation name
      * @param callbackInterface Pointer to callback interface
      * @param memory Pointer to sc-memory interface to use in callback
      * @param parent Pointer to parent QObject
      */
    explicit ScCoreEvent(const ScUri &uri, ScEventType type, const QString &name,
                         ScEventCallbackInterface *callbackInterface,
                         ScCoreMemory *memory, QObject *parent = 0);
    virtual ~ScCoreEvent();

protected:
    /*! Emit event into callback
      * @param event Class that contains information about event
      * @return Return ScEventCallbackInterface::eventCallBack result
      */
    bool emitEvent(const ScEvent &event);

    //! @copydoc ScOperation::acrivateImpl
    bool activateImpl(sc_addr paramSystem, sc_segment *tmpSegment);
    //! @copydoc ScOperation::genActCond
    void genActCond(sc_generator &gen);

protected:
    //! ScUri of listened sc-element
    ScUri mUri;
    //! Pointer to callback interface
    ScEventCallbackInterface *mCallbackInterface;
    //! Event type
    ScEventType mType;
    //! Pointer to memory interface, that will used in callback
    ScCoreMemory *mMemory;

};

#endif // SCCOREEVENTHANDLER_H
