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
#include "scgnode.h"

#include <QVector2D>

SCgNode::SCgNode(QObject *parentObject) :
    SCgObject(parentObject)
{
    setSize(QSizeF(20, 20));
}

SCgNode::~SCgNode()
{
}

QPointF SCgNode::calculateDotCoordinates(qreal dotPosition, const QPointF &point) const
{
    Q_UNUSED(dotPosition);

    QPointF pos = position();
    QVector2D dir(pos - point);
    qreal l = size().width() / 2.f;

    return pos - dir.normalized().toPointF() * l;
}

QPointF SCgNode::calculateDotCoordinatesByAngle(qreal slope, const QPointF &point) const
{
    return calculateDotCoordinates(slope, point);
}

qreal SCgNode::calculateDotPosition(const QPointF &point) const
{
    Q_UNUSED(point);
    return -1.f;
}
