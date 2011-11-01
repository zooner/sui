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

#ifndef SCGBUS_H
#define SCGBUS_H

#include "scgpointcontainer.h"
#include "scgobjectobserver.h"

/*! Class describes scg-bus object. That type of object used
  * to extend connection area for scg-nodes.
  * Node that have attached scg-bus is an owner. @see SCgBus::setOwner, SCgBus::owner
  * Bus object can be created without owner.
  */
class SCgBus : public SCgPointContainer,
                public SCgObjectObserver
{
    friend class SCgConstruction;

    Q_OBJECT

public:
    explicit SCgBus(QObject *parent = 0);
    virtual ~SCgBus();

    //! @copydoc SCgObjectObserver::_update
    void _update(UpdateEventType eventType, SCgObject *object);

    /*! Setup new bus owner
     * @param owner Pointer to new bus owner
     */
    void setOwner(SCgObject *owner);

    //! Return pointer to bus owner
    SCgObject* owner() const;

    //! Recalculate bus points
    void updatePoints();

protected:

    //! @copydoc SCgObject::calculateDotCoordinates
    QPointF calculateDotCoordinates(qreal dotPosition, const QPointF &point) const;

    //! @copydoc SCgObject::calculateDotPosition
    qreal calculateDotPosition(const QPointF &point) const;

protected:
    //! Pointer to bus owner
    SCgObject *mOwner;

signals:

public slots:

};

#endif // SCGBUS_H
