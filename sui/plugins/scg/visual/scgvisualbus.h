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

#ifndef SCGVISUALBUS_H
#define SCGVISUALBUS_H

#include "scgvisualobject.h"

class SCgVisualNode;


class SCgVisualBus : public SCgVisualObject
{
public:
    explicit SCgVisualBus(QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);
    virtual ~SCgVisualBus();

protected:
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    //! @copydoc SCgVisualObject::_update
    void _update(UpdateEventType eventType, SCgObject *object);

public:

    void updatePosition();
    //! @copydoc SCgPointObject::updateShape;
    void updateShape();

    //! Type for qgraphicsitem_cast
    int type() const { return SCgBusType; }

private:
    //! Path that represents shape
    QPainterPath mShape;
};

#endif // SCGBUS_H
