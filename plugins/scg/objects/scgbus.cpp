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
#include "scgbus.h"

#include <QVector2D>

SCgBus::SCgBus(QObject *parent) :
    SCgPointContainer(parent),
    mOwner(0)
{
}

SCgBus::~SCgBus()
{
}

void SCgBus::_update(UpdateEventType eventType, SCgObject *object)
{
    if (eventType == SCgObjectObserver::PositionChanged ||
            eventType == SCgObjectObserver::SizeChanged)
        updatePoints();
}

void SCgBus::updatePoints()
{
    if (mPoints.size() < 2) return; // do nothing

    if (mOwner != 0)
    {
        mPoints.first() = mOwner->calculateDotCoordinates(0.f, mPoints[1]);
        _notifyUpdate(SCgObjectObserver::PointsChanged);
    }
}

QPointF SCgBus::calculateDotCoordinates(qreal dotPosition, const QPointF &point) const
{
    QPointF res;

    Q_ASSERT(dotPosition >= 0.f);

    qint32 seg_num = (qint32)dotPosition;
    qreal seg_pos = dotPosition - (qreal)seg_num;

    if (seg_num >= mPoints.size() - 1) seg_num = (qint32)mPoints.size() - 2;

    QPointF p2 = mPoints.at(seg_num + 1);
    QPointF p1 = mPoints.at(seg_num);
    QPointF dir(p2 - p1);

    res = p1 + dir * seg_pos;

    return res;
}

qreal SCgBus::calculateDotPosition(const QPointF &point) const
{
    // get sector with minimal distance to point
    // and calculates relative dot position on it
    qreal minDist = -1.f;
    qreal result = 0.f;

    for (int i = 1; i < mPoints.size(); i++)
    {
        QPointF p1 = mPoints.at(i - 1);
        QPointF p2 = mPoints.at(i);

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
        if (minDist < 0.f || minDist > d)
        {
            minDist = d;
            result = (i - 1) + dotPos;
        }
    }

    return result;
}

void SCgBus::setOwner(SCgObject *owner)
{
    if (mOwner == owner) return; // do nothing

    if (mOwner)
        mOwner->detachObserver(this);

    mOwner = owner;

    if (mOwner)
        mOwner->attachObserver(this);

    _notifyUpdate(SCgObjectObserver::OwnerChanged);
}

SCgObject* SCgBus::owner() const
{
    return mOwner;
}
