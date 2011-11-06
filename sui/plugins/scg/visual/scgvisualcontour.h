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

#ifndef SCGVISUALCONTOUR_H
#define SCGVISUALCONTOUR_H

#include "scgvisualobject.h"

#include <QColor>

class SCgVisualContour : public SCgVisualObject
{

public:
    explicit SCgVisualContour(QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);
    virtual ~SCgVisualContour();

    /*! Set background color
      @param color BAckground color
      */
    void setColorBack(const QColor &color);

    /*! Get background color
      @return Background color
      */
    QColor colorBack() const;

    /*! Updates contour data.
      */
    void updatePosition();

    //! @see SCgPointObject::updateShape;
    void updateShape();

protected:
    //! @see QGraphicsItem::boundingRect()
    QRectF boundingRect() const;
    //! @see QGraphicsItem::shape()
    QPainterPath shape() const;

    /*! @see QGraphicsItem::paint
      */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    //! @copydoc SCgVisualObject::_update
    void _update(UpdateEventType eventType, SCgObject *object);

    //! @copydoc SCgVisualObject::_reSync
    void _reSync();

public:
    //! Type for qgraphicsitem_cast
    int type() const { return SCgContourType; }

protected:
    //! Contour shape
    QPainterPath mShape;
    //! Background color
    QColor mColorBack;
};

#endif // SCGVISUALCONTOUR_H
