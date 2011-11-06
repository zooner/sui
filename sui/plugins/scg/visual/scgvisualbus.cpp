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
#include "scgvisualbus.h"

#include "scgvisualnode.h"

#include <QPainterPathStroker>
#include <QVector2D>
#include <QPainter>

SCgVisualBus::SCgVisualBus(QGraphicsItem *parent, QGraphicsScene *scene) :
    SCgVisualObject(parent, scene)
{
    setFlag(QGraphicsItem::ItemIsMovable, false);
    setToolTip(QObject::tr("SCg-bus"));
}

SCgVisualBus::~SCgVisualBus()
{

}

QRectF SCgVisualBus::boundingRect() const
{
    return mShape.boundingRect().adjusted(-5, -5, 5, 5);
}

QPainterPath SCgVisualBus::shape() const
{
    return mShape;
}

void SCgVisualBus::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // synchronize with sc.g-object
    sync();

    SCgBus *bus = qobject_cast<SCgBus*>(observedObject(0));
    const QVector<QPointF>& points = bus->points();

    painter->setPen(QPen(QBrush(mColor), 7.f));

    QPainterPath path;
    QVector<QPointF>::const_iterator it;
    for (it = points.begin(); it != points.end(); ++it)
    {
        if (it == points.begin())
            path.moveTo(*it);
        else
            path.lineTo(*it);
    }
    painter->drawPath(path);

    SCgVisualObject::paint(painter, option, widget);
}

QVariant SCgVisualBus::itemChange(GraphicsItemChange change, const QVariant &value)
{
//    if (change == QGraphicsItem::ItemPositionHasChanged && !mParentChanging
//            && mOwner && !mOwner->isDead())
//        mOwner->setPos(mapToParent(mOwnerPos));

    return SCgVisualObject::itemChange(change, value);
}

void SCgVisualBus::_update(UpdateEventType eventType, SCgObject *object)
{
    SCgVisualObject::_update(eventType, object);

    if (eventType == PointsChanged)
        updateShape();
}

void SCgVisualBus::updatePosition()
{
    updateShape();
}

void SCgVisualBus::updateShape()
{
    prepareGeometryChange();
    // Rebuilding shape
    mShape = QPainterPath();

    const QVector<QPointF>& points = static_cast<SCgBus*>(observedObject(0))->points();

    mShape.moveTo(points.at(0));
    for (int i = 1; i < points.size(); i++)
        mShape.lineTo(points.at(i));

    QPainterPathStroker path_stroker;
    path_stroker.setJoinStyle(Qt::MiterJoin);
    path_stroker.setWidth(7.f);

    mShape = path_stroker.createStroke(mShape);

    // updating pair
    update();
}
