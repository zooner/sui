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

#ifndef SCGVISUALCONTROL_H
#define SCGVISUALCONTROL_H

#include "scgprerequest.h"
#include "scgvisualobject.h"

/*! This object visualize sc.g-controls. You can work with that object
  * like with any sc.g-node object. Command starts on left mouse button click.
  */
class SCgVisualControl : public SCgVisualObject
{
    Q_OBJECT

protected:
    friend class SCgVisualObject;
    explicit SCgVisualControl(QGraphicsScene *scene = 0);
public:

    //! Type for qgraphicsitem_cast
    int type() const { return SCgControlType; }

    virtual ~SCgVisualControl();

    //! @copydoc SCgObject::boundingRect
    QRectF boundingRect() const;
    //! @copydoc SCgObject::updatePosition
    void updatePosition();

protected:
    //! @copydoc QGraphicsItem::paint
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    //! @copydoc SCgObject::hoverEnterEvent
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    //! @copydoc SCgObject::hoverLeaveEvent
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    //! @copydoc SCgObject::itemChange
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    //! @copydoc QGraphicsItem::mousePressEvent
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    //! @copydoc QGraphicsItem::mouseReleaseEvent
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    //! @copydoc QGraphicsItem::mouseMoveEvent
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    //! Return object shape
    QPainterPath shape() const;

    //! @copydoc SCgVisualObject::_update
    void _update(UpdateEventType eventType, SCgObject *object);

    //! @copydoc SCgVisualObject::clone()
//    virtual SCgVisualObject* clone(){return 0;}
protected:
    //! Backgound color
    QColor mBackColor;
    //! Dragged path length
    qreal mDragLength;
    //! Last mouse position
    QPointF mLastDragPos;

signals:

public slots:

};

#endif // SCGCONTROL_H
