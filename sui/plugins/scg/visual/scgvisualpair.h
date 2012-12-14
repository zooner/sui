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

#ifndef SCGVISUALPAIR_H
#define SCGVISUALPAIR_H

#include "scgvisualobject.h"


#include <QPainterPath>


class SCgVisualPair : public SCgVisualObject
{
    Q_OBJECT

protected:
    friend class SCgVisualObject;
    explicit SCgVisualPair(QGraphicsScene *scene = 0);
public:

    virtual ~SCgVisualPair();

    /*! Returns normal path, without pen width affected.
      */
    QPainterPath shapeNormal() const;

    //! @copydoc SCgPointObject::updateShape;
    void updateShape();

protected:
    //! @copydoc QGraphicsItem::boundingRect
    QRectF boundingRect() const;
    //! @copydoc QGraphicsItem::shape()
    QPainterPath shape() const;
    //! @copydoc QGraphicsItem::paint()
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    //! @copydoc SCgVisualObject::_update
    void _update(UpdateEventType eventType, SCgObject *object);
public:
    //! Type for qgraphicsitem_cast
    int type() const { return SCgPairType; }

public:
    //! Updates position for points
    void updatePosition();

private:
    //! Cached value of bounding box
    QRectF mBoundRect;
    //! Path that represents shape
    QPainterPath mShape;


};

#endif // SCGPAIR_H
