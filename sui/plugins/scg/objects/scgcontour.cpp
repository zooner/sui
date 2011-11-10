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
#include "scgcontour.h"

#include <QVector2D>

SCgContour::SCgContour(QObject *parent) :
    SCgPointContainer(parent),
    mBorderAccuracy(15.f)
{
}

SCgContour::~SCgContour()
{

}

QPointF SCgContour::calculateDotCoordinates(qreal dotPosition, const QPointF &point) const
{
    QPointF res;

    QPointF wpos = worldPosition();
    if (dotPosition != 0)
    {
        quint32 seg_num = (quint32)dotPosition;
        qreal seg_pos = dotPosition - (qreal)seg_num;
        quint32 sz = mPoints.size();

        seg_num = qMin(sz - 1, seg_num);

        QPointF p2 = mPoints.at((seg_num + 1) % sz);
        QPointF p1 = mPoints.at((seg_num) % sz);
        QPointF dir(p2 - p1);

        res = p1 + dir * seg_pos;
    }
    else
    {
        QRectF bound = QPolygonF(mPoints).boundingRect();
        QPointF p(bound.center());

        QPointF p1 = mPoints.last();
        QPointF p2, intersectPoint, result;
        QLineF line, pair(point - wpos, p);
        // Ensure, that pair definitely have intersections with contour.
        pair.setLength(pair.length() + bound.width() + bound.height());
        qreal minLength = -1;

        //Find intersection point with minimal distance from @p from to contour
        for (int i = 0; i < mPoints.size(); i++)
        {
            p2 = mPoints[i];
            line.setPoints(p1,p2);
            QLineF::IntersectType intersectType = line.intersect(pair, &intersectPoint);
            if (intersectType == QLineF::BoundedIntersection)
            {
                pair.setP2(intersectPoint);
                if(minLength == -1 || pair.length() < minLength)
                {
                    minLength = pair.length();
                    res = intersectPoint;
                }
            }

            p1 = p2;
        }
    }

    return res + wpos;
}

qreal SCgContour::calculateDotPosition(const QPointF &point) const
{
    // get sector with minimal distance to point
    // and calculates relative dot position on it
    qreal minDist = -1.f;
    qreal result = 0.f;
    QPointF wpos = worldPosition();
    quint32 sz = mPoints.size();

    for (quint32 i = 0; i < sz; i++)
    {
        QPointF p1 = mPoints.at(i) + wpos;
        QPointF p2 = mPoints.at((i + 1) % sz) + wpos;

        QVector2D v(p2 - p1);
        QVector2D vp(point - p1);

        if(v.length() == 0)
            return result;

        qreal dotPos = QVector2D::dotProduct(vp, v.normalized()) / v.length();
        QPointF p = p1 + v.toPointF() * dotPos;

        if (dotPos < 0.f || dotPos > 1.f)
            continue;

        // we doesn't need to get real length, because we need minimum
        // so we get squared length to make that procedure faster
        qreal d = QVector2D(point - p).lengthSquared();

        // compare with minimum distance
        if (d < mBorderAccuracy)
        {
            if (minDist < 0.f || minDist > d)
            {
                minDist = d;
                result = i + dotPos;
            }
        }
    }

    return result;
}

void SCgContour::setBorderAccuracy(qreal value)
{
    mBorderAccuracy = value;
}

qreal SCgContour::borderAccuracy() const
{
    return mBorderAccuracy;
}
