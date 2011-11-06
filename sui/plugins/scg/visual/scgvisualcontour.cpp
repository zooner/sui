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
#include "scgvisualcontour.h"

#include "scgvisualpair.h"
#include "scgvisualcontour.h"

#include <QColor>
#include <QGraphicsScene>
#include <QPainter>

SCgVisualContour::SCgVisualContour(QGraphicsItem *parent, QGraphicsScene *scene) :
    SCgVisualObject(parent, scene),
    mColorBack(QColor(250, 250, 250, 224))
{
    setFlag(QGraphicsItem::ItemIsMovable, true);
    //setFlag(QGraphicsItem::ItemClipsChildrenToShape, true);
    setToolTip(QObject::tr("SCg-contour"));
    setZValue(7);
}

SCgVisualContour::~SCgVisualContour()
{

}

QPainterPath SCgVisualContour::shape() const
{
    return mShape;
}

QRectF SCgVisualContour::boundingRect() const
{
    return mShape.boundingRect().adjusted(-5.f, -5.f, 5.f, 5.f);
}

void SCgVisualContour::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //SCgAlphabet::paintContour(painter, this);
    // synchronize with sc.g-object
    sync();

    SCgContour *contour = qobject_cast<SCgContour*>(observedObject(0));
    Q_ASSERT(contour != 0);

    painter->setBrush(QBrush(mColorBack));
    painter->setPen(QPen(QBrush(mColor), 5.f));

    const QVector<QPointF>& points = contour->points();
    QPainterPath path;
    QVector<QPointF>::const_iterator it;
    for (it = points.begin(); it != points.end(); ++it)
    {
        if (it == points.begin())
            path.moveTo(*it);
        else
            path.lineTo(*it);
    }
    path.lineTo(points.first());
    painter->drawPath(path);

    SCgVisualObject::paint(painter, option, widget);
}

void SCgVisualContour::setColorBack(const QColor &color)
{
    mColorBack = color;
}

QColor SCgVisualContour::colorBack() const
{
    return mColorBack;
}

void SCgVisualContour::updatePosition()
{
    updateShape();
}

void SCgVisualContour::_update(UpdateEventType eventType, SCgObject *object)
{
    SCgVisualObject::_update(eventType, object);

    if (eventType == PointsChanged)
        updateShape();
}

void SCgVisualContour::_reSync()
{
    SCgVisualObject::_reSync();

    updateShape();
}

void SCgVisualContour::updateShape()
{
    prepareGeometryChange();
    mShape = QPainterPath();

    const QVector<QPointF>& points = static_cast<SCgContour*>(observedObject(0))->points();

    if (points.size() < 3) return; // do nothing

    mShape.moveTo(points.at(0));
    for (qint32 i = 1; i < points.size(); i++)
        mShape.lineTo(points.at(i));
    mShape.closeSubpath();

    update();
}


