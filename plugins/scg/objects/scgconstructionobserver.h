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

#ifndef SCGCONSTRUCTIONOBSERVER_H
#define SCGCONSTRUCTIONOBSERVER_H

#include <QObject>

class SCgObject;
class SCgConstruction;

class SCgConstructionObserver
{
    friend class SCgConstruction;

public:
    explicit SCgConstructionObserver();
    virtual ~SCgConstructionObserver();

    /*! Update event types enumeration */
    typedef enum
    {
        ObjectCreated = 0,    /*! object created in construction.
                                    Object was constructed with memory allocation */
        ObjectDeleted,        /*! object deleted from construction.
                                    Object was deleted and allocated memory was freed */
        ObjectAppended,       /*! object appended into construction.
                                    Object was added into construction, but it was already existed */
        ObjectRemoved         /*! object removed from construction.
                                    Object was removed from construction, but allocated to it memory, wasn't free */

    } UpdateEventType;

    /*! Observed object update callback. Calls when observed object
      * has changed. If you get ObjectDelete event, then you need to process
      * it imideately, because after function return, allocated memory for
      * \p object will be free.
      * @param eventType Update event type
      * @param object Pointer to updated object
      */
    virtual void _update(UpdateEventType eventType, QObject *object) = 0;

protected:
    //! Pointer to observed construction
    SCgConstruction *mConstruction;
};

#endif // SCGCONSTRUCTIONOBSERVER_H
