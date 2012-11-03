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
#include "scgvisualnode.h"
#include "scgvisualbus.h"

#include <QPainter>
#include <QVector2D>
#include <QGraphicsScene>
#include <QGraphicsView>

SCgVisualNode::SCgVisualNode(QGraphicsItem *parent, QGraphicsScene *scene) :
    SCgVisualObject(parent, scene)
{
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setToolTip(QObject::tr("SCg-node"));
    setZValue(2);
}

SCgVisualNode::~SCgVisualNode()
{

}


QRectF SCgVisualNode::boundingRect() const
{
    QRectF res;

//    if (mConstType == SCgAlphabet::Meta)
//        res = QRectF(-size().width() / 2.f - 1.f, -size().height() / 2.f - 1.f, mSize.width() + 2.f, mSize.height() + 2.f);
//    else
    SCgObject *object = observedObject(0);
    QPointF size = object->size();
    res = QRectF(-size.x() / 2.f, -size.y() / 2.f, size.x(), size.y());

    if (!object->objectType().check(ScStructuralMask))
        res.adjust(5, 5, -5, -5);

    return res;
}

QPainterPath SCgVisualNode::shape() const
{
    QPainterPath path;
    QRectF boundRect = boundingRect();

    QMatrix matrix;

    SCgObject *object = observedObject(0);

    if (object->objectType().check(ScConst))
        path.addEllipse(boundRect);
    else if (object->objectType().check(ScVar))
        path.addRect(boundRect);
    else if (object->objectType().check(ScMeta))
        path.addPolygon(matrix.rotate(45.f).mapToPolygon(boundRect.toRect()));
    else
        SuiExcept(SuiExceptionInvalidState,
                  "Object haven't any constancy flag",
                  "QPainterPath SCgVisualNode::shape() const");

    return path;
}

QVariant SCgVisualNode::itemChange(GraphicsItemChange change, const QVariant &value)
{
//    if (mBus && !mBus->isDead() && change == QGraphicsItem::ItemParentHasChanged)
//        mBus->setParentItem(parentItem());

    return SCgVisualObject::itemChange(change, value);
}

void SCgVisualNode::updatePosition()
{
}

void SCgVisualNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // synchronize with sc.g-object
    sync();

    /* need to rebuild that code to more flexible.
       Just for example make drawers class for different types.
     */
    QRectF boundRect = boundingRect();

    // draw shape
    QPen pen = QPen(QBrush(mColor, Qt::SolidPattern), 4, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin);
    QBrush brush = QBrush(QColor(255, 255, 255, 224), Qt::SolidPattern);

    QRectF bound = boundRect.adjusted(2, 2, -2, -2);
    SCgObject *object = observedObject(0);

    if (!object->objectType().check(ScStructuralMask))
    {
        brush.setColor(mColor);
    }
    painter->setPen(pen);
    painter->setBrush(brush);

    if (object->objectType().check(ScConst))
    {
        painter->drawEllipse(bound);

        //paintStruct(painter, mObject->colorForeground(), bound, type_struct);
    }else
    {
        if (object->objectType().check(ScMeta))
        {
            painter->save();

            painter->rotate(45.f);
            painter->scale(0.85f, 0.85f);
            painter->drawRect(bound.adjusted(2, 2, -2, -2));

            //paintStruct(painter, color, bound, type_struct);

            painter->restore();

        }else
        {
            painter->scale(0.9f, 0.9f);
            painter->drawRect(bound);

            //paintStruct(painter, color, bound, type_struct);
        }

    }

    //! TODO: add struct types paint


    SCgVisualObject::paint(painter, option, widget);
}

