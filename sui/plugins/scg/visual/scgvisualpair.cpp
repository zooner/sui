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
#include "scgvisualpair.h"
#include "scgvisualbus.h"

#include "objects/scgpair.h"

#include <QPainter>
#include <QVector2D>

SCgVisualPair::SCgVisualPair(QGraphicsScene *scene) :
    SCgVisualObject(scene)
{
    setToolTip(QObject::tr("SCg-pair"));
    setZValue(1);
}

SCgVisualPair::~SCgVisualPair()
{
}

QRectF SCgVisualPair::boundingRect() const
{
    return mShape.boundingRect().adjusted(-11, -11, 11, 11);
}

QPainterPath SCgVisualPair::shapeNormal() const
{
    return mShape;
}

void SCgVisualPair::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    SCgPair *pair = static_cast<SCgPair*>(baseObject());
    const QVector<QPointF>& points = pair->points();

    Q_ASSERT(pair != 0);
    Q_ASSERT(points.size() > 1);

    static float arrowLength = 15.f;
    static float arrowWidth = 9.f;

    if (!baseObject()->scObjectType().check(ScEdgeCommon))
    {

        static const QPointF arrowPoints[3] = {QPointF(-arrowWidth / 2.f, 0.f),
                                               QPointF(arrowWidth / 2.f, 0.f),
                                               QPointF(0.f, arrowLength)};

        // draw arrow for orient pairs
        QLineF line(points.at(points.size() - 2), points.last());
        double angle = ::atan2(line.dx(), line.dy());

        painter->save();
        painter->translate(line.p2());
        painter->rotate(-angle * 180.f / M_PI);
        painter->translate(0.f, -arrowLength);

        painter->setBrush(QBrush(mColor, Qt::SolidPattern));
        painter->setPen(QPen(mColor, 0));
        painter->drawConvexPolygon(arrowPoints, 3);

        painter->restore();

        // correct last point
        //points.last() -= QPointF((arrowLength + 3.f) * ::sin(angle), (arrowLength + 3.f) * ::cos(angle));
    }
    painter->setPen(QPen(mColor, 2));

    QPainterPath path;
    QVector<QPointF>::const_iterator it = points.begin();
    path.moveTo(*(it++));
    for (; it != points.end(); ++it)
        path.lineTo(*it);

    painter->drawPath(path);

    SCgVisualObject::paint(painter, option, widget);
}

void SCgVisualPair::_update(UpdateEventType eventType, SCgObject *object)
{
    SCgVisualObject::_update(eventType, object);

    if (eventType == PointsChanged)
        updateShape();
}

void SCgVisualPair::updateShape()
{
    prepareGeometryChange();
    // Rebuilding shape
    mShape = QPainterPath();

    const QVector<QPointF>& points = static_cast<SCgPair*>(baseObject())->points();

    mShape.moveTo(points.at(0));
    for (int i = 1; i < points.size(); i++)
        mShape.lineTo(points.at(i));

    QPainterPathStroker path_stroker;
    path_stroker.setJoinStyle(Qt::MiterJoin);
    path_stroker.setWidth(10.f);

    mShape = path_stroker.createStroke(mShape);

    // updating pair
    update();

//    // update text position
//    if (mTextItem)
//    {
//        Q_ASSERT(points.size() > 1);
//        QPointF text_pos = (points[0].toPointF() + points[1].toPointF()) / 2.f;
//        mTextItem->setPos(text_pos);
//    }
}

QPainterPath SCgVisualPair::shape() const
{
    return mShape;
}

void SCgVisualPair::updatePosition()
{
    // update shape with new points.
    updateShape();
}
