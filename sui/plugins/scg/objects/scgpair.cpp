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
#include "scgpair.h"

#include <QVector2D>

SCgPair::SCgPair(QObject *parent) :
    SCgPointContainer(parent),
    mBeginObject(0),
    mEndObject(0),
    mLineWidth(0.f),
    mBeginDotPos(0.f),
    mEndDotPos(0.f)
{
}

SCgPair::~SCgPair()
{
}

void SCgPair::setBeginObject(SCgObject *object)
{
    if (mBeginObject == object) return;

    if (mBeginObject != 0) mBeginObject->detachObserver(this);
    mBeginObject = object;
    if (mBeginObject != 0) mBeginObject->attachObserver(this);
    _notifyUpdate(SCgObjectObserver::PairBeginChanged);

    updateDotCoordinates();
}

void SCgPair::setEndObject(SCgObject *object)
{
    if (mEndObject == object) return;

    if (mEndObject != 0) mEndObject->detachObserver(this);
    mEndObject = object;
    if (mEndObject != 0) mEndObject->attachObserver(this);
    _notifyUpdate(SCgObjectObserver::PairEndChanged);

    updateDotCoordinates();
}

void SCgPair::setLineWidth(qreal width)
{
    mLineWidth = width;
    _notifyUpdate(SCgObjectObserver::PairWidthChanged);
}

void SCgPair::setBeginDotPosition(qreal dotPosition)
{
    mBeginDotPos = dotPosition;
    updateDotCoordinates();
}

void SCgPair::setEndDotPosition(qreal dotPosition)
{
    mEndDotPos = dotPosition;
    updateDotCoordinates();
}

QPointF SCgPair::calculateDotCoordinates(qreal dotPosition, const QPointF &point) const
{
    Q_UNUSED(point);

    QPointF res;

    Q_ASSERT(dotPosition >= 0.f);

    qint32 seg_num = (qint32)dotPosition;
    qreal seg_pos = dotPosition - seg_num;

    if (seg_num >= mPoints.size() - 1) seg_num = mPoints.size() - 2;

    QPointF p2 = mapToWorld(mPoints.at(seg_num + 1));
    QPointF p1 = mapToWorld(mPoints.at(seg_num));
    QPointF dir(p2 - p1);

    res = p1 + dir * seg_pos;

    return res;
}

qreal SCgPair::calculateDotPosition(const QPointF &point) const
{
    // get sector with minimal distance to point
    // and calculates relative dot position on it
    qreal minDist = -1.f;
    qreal result = 0.f;

    const QVector<QPointF>& sPoints = worldPoints();

    for (int i = 1; i < sPoints.size(); i++)
    {
        QPointF p1 = sPoints.at(i - 1);
        QPointF p2 = sPoints.at(i);

        QVector2D v(p2 - p1);
        QVector2D vp(point - p1);

        if(v.length() == 0)
            continue;

        qreal dotPos = QVector2D::dotProduct(vp, v.normalized()) / v.length();
        if (dotPos < 0.f || (dotPos > 1.f && !qFuzzyCompare((qreal)dotPos, (qreal)1)))
            continue;

        QPointF p = p1 + v.toPointF() * dotPos;
        // we doesn't need to get real length, because we need minimum
        // so we get squared length to make that procedure faster
        qreal d = QVector2D(point - p).lengthSquared();

        // compare with minimum distance
        if (minDist < 0.f || minDist > d)
        {
            minDist = d;
            result = (i - 1) + dotPos;
        }
    }

    return result;
}

void SCgPair::_notifyUpdate(SCgObjectObserver::UpdateEventType eventType)
{
    if(eventType == SCgObjectObserver::PositionChanged)
        updateDotCoordinates();
    SCgObject::_notifyUpdate(eventType);
}

void SCgPair::_update(UpdateEventType eventType, SCgObject *object)
{
    Q_UNUSED(object);

    if (eventType == SCgObjectObserver::PositionChanged ||
        eventType == SCgObjectObserver::PointsChanged ||
        eventType == SCgObjectObserver::SizeChanged)
        updateDotCoordinates();

}

void SCgPair::updateDotCoordinates()
{
    if (mEndObject == 0 || mBeginObject == 0 || mPoints.size() < 2) return;

    mPoints.front() = mapFromWorld(mBeginObject->calculateDotCoordinates(mBeginDotPos, mapToWorld(mPoints.at(1))));
    mPoints.back() = mapFromWorld(mEndObject->calculateDotCoordinates(mEndDotPos, mapToWorld(mPoints.at(mPoints.size() - 2))));

    _notifyUpdate(SCgObjectObserver::PointsChanged);
}
