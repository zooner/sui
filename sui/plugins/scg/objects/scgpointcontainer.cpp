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

#include <QVector2D>
#include "scgprecompiled.h"
#include "scgpointcontainer.h"


SCgPointContainer::SCgPointContainer(QObject *parent) :
    SCgObject(parent)
{
}

SCgPointContainer::~SCgPointContainer()
{
}

void SCgPointContainer::appendPoint(const QPointF &worldPoint)
{
    mPoints.push_back(mapFromWorld(worldPoint));
    _notifyUpdate(SCgObjectObserver::PointsChanged);
}

void SCgPointContainer::insertPoint(quint32 idx, const QPointF &worldPoint)
{
    mPoints.insert(idx, mapFromWorld(worldPoint));
    _notifyUpdate(SCgObjectObserver::PointsChanged);
}

void SCgPointContainer::removePoint(quint32 idx)
{
    mPoints.remove(idx);
    _notifyUpdate(SCgObjectObserver::PointsChanged);
}

void SCgPointContainer::replacePoint(quint32 idx, const QPointF &worldPoint)
{
    Q_ASSERT(idx < mPoints.count());

    mPoints[idx] = mapFromWorld(worldPoint);
    _notifyUpdate(SCgObjectObserver::PointsChanged);
}

const QPointF& SCgPointContainer::pointAt(quint32 idx) const
{
    return mPoints.at(idx);
}

QPointF SCgPointContainer::worldPointAt(quint32 idx) const
{
    return mapToWorld(mPoints.at(idx));
}

quint32 SCgPointContainer::pointsCount() const
{
    return mPoints.size();
}

const QVector<QPointF>& SCgPointContainer::points() const
{
    return mPoints;
}

QPointF SCgPointContainer::calculateDotCoordinatesByAngle(qreal slope, const QPointF &point) const
{
    // get sector with minimal distance to point
    // and calculates relative dot position on it
    qreal minDist = -1.f;
    qreal minDistToSeg = -1.f;

    const QVector<QPointF>& sPoints = worldPoints();
    // No matter, which point is the second. We set the line angle.
    // Main requirement is that second point != first point.
    QLineF connectedSegment = QLineF(point, point + QPointF(5,5));
    connectedSegment.setAngle(slope);

    QPointF result = QPointF();

    QPointF segmentResult;

    for (int i = 1; i < sPoints.size(); i++)
    {
        const QPointF& p1 = sPoints.at(i - 1);
        const QPointF& p2 = sPoints.at(i);

        QLineF lineSegment = QLineF(p1, p2);
        qreal segLength = lineSegment.length();
        //note: floating comparison
        if(segLength == 0)
            continue;

        QPointF intersectionPoint = QPointF();

        if(lineSegment.intersect(connectedSegment, &intersectionPoint) != QLineF::NoIntersection)
        {
            //check if point belongs current line segment
            QVector2D v1(p2 - intersectionPoint);
            QVector2D v2(p1 - intersectionPoint);
            if(QVector2D::dotProduct(v1, v2) > 0)
            {
                // The point does NOT belong to segment
                // Distance from \p point to line segment lies on.
                qreal dist = qAbs((p2.x() - p1.x())*(point.y() - p1.y()) - (p2.y() - p1.y())*(point.x() - p1.x()))/segLength;
                QVector2D v = QVector2D(p2 - p1);
                v1 = QVector2D(point - p1);
                v2 = QVector2D(point - p2);
                qreal v1Length = v1.length();
                qreal v2Length = v2.length();
                if(QVector2D::dotProduct(v, v1) < 0 || QVector2D::dotProduct(-v, v2) < 0)
                {
                    //perpendicular does not hit the segment
                    dist = qMin(v1Length, v2Length);
                }

                if(minDistToSeg < 0.f || minDistToSeg > dist)
                {
                    minDistToSeg = dist;
                    QVector2D v = QVector2D(intersectionPoint - point);
                    qreal vLength = v.length();
                    // we should chouse the point with minimal angle
                    qreal angle1 = qAcos(QVector2D::dotProduct(v, -v1)/(vLength*v1Length));
                    qreal angle2 = qAcos(QVector2D::dotProduct(v, -v2)/(vLength*v2Length));

                    segmentResult = angle1 < angle2 ? p1 : p2;
                }
            }
            else
            {
                // The point belongs to segment.
                qreal d = QVector2D(intersectionPoint - point).lengthSquared();

                // compare with minimum distance
                if (minDist < 0.f || minDist > d)
                {
                    minDist = d;
                    result = intersectionPoint;
                }
            }
        }
    }

    if(minDist < 0.f)
    {
        // if we didn't find proper intersection point use the closiest segment
        return minDistToSeg < 0.f ? sPoints.at(0) : segmentResult;
    }

    return result;
}

QVector<QPointF> SCgPointContainer::worldPoints() const
{
    QVector<QPointF> result;
    foreach(const QPointF& point, mPoints)
    {
        result.append(mapToWorld(point));
    }
    return result;
}

QPointF SCgPointContainer::mapToWorld(const QPointF &point) const
{
    return point + position();
}

QPointF SCgPointContainer::mapFromWorld(const QPointF &point) const
{
    return point - position();
}
