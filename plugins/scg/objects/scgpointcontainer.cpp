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
#include "scgpointcontainer.h"

SCgPointContainer::SCgPointContainer(QObject *parent) :
    SCgObject(parent)
{
}

SCgPointContainer::~SCgPointContainer()
{
}

void SCgPointContainer::appendPoint(const QPointF &point)
{
    mPoints.push_back(point);
    _notifyUpdate(SCgObjectObserver::PointsChanged);
}

void SCgPointContainer::insertPoint(quint32 idx, const QPointF &point)
{
    mPoints.insert(idx, point);
    _notifyUpdate(SCgObjectObserver::PointsChanged);
}

void SCgPointContainer::removePoint(quint32 idx)
{
    mPoints.remove(idx);
    _notifyUpdate(SCgObjectObserver::PointsChanged);
}

const QPointF& SCgPointContainer::point(quint32 idx) const
{
    return mPoints.at(idx);
}

quint32 SCgPointContainer::pointsCount() const
{
    return mPoints.size();
}

const QVector<QPointF>& SCgPointContainer::points() const
{
    return mPoints;
}
