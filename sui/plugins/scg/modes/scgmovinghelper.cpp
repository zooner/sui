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

#include "scgmovinghelper.h"
#include "visual/scgvisualobject.h"
#include "objects/scgobject.h"
#include "objects/scgpair.h"
#include <QPair>


SCgMovingHelper::SCgMovingHelper()
    :mStartPoint(0,0)
{
}

void SCgMovingHelper::initializeWithObjects(const QList<QGraphicsItem *> &objList, const QPointF &startPoint)
{
    mStartPoint = startPoint;

    foreach (QGraphicsItem *item, objList)
    {
        if(!SCgVisualObject::isSCgVisualObjectType(item->type())) continue;

        SCgVisualObject* visual = static_cast<SCgVisualObject*>(item);
        Q_ASSERT(visual && visual->baseObject());

        SCgObject* obj = visual->baseObject();

        storeInitialObjectPosition(obj);
    }
}

void SCgMovingHelper::setAndStoreDotPositions(SCgPair* pair)
{
    Q_ASSERT(mInitialPairsAngles.contains(pair));

    SCgObject* beginObj = pair->beginObject();
    SCgObject* endObj = pair->endObject();

    const QPair<qreal, qreal>& angles = mInitialPairsAngles[pair];

    qreal newBeginDotPos = beginObj->calculateDotPosition(
                beginObj->calculateDotCoordinatesByAngle(angles.first,
                                                         pair->worldPointAt(1)));
    qreal newEndDotPos = endObj->calculateDotPosition(
                endObj->calculateDotCoordinatesByAngle(angles.second,
                                                         pair->worldPointAt(pair->pointsCount() - 2)));
    pair->setBeginDotPosition(newBeginDotPos);
    pair->setEndDotPosition(newEndDotPos);

    mChangedPairsDotPositions[pair].second.first = newBeginDotPos;
    mChangedPairsDotPositions[pair].second.second = newEndDotPos;
}

void SCgMovingHelper::moveTo(const QPointF& toPoint)
{
    if(mMoveInfo.isEmpty()) return;

    // Move all registered items
    SCgCommandObjectMove::MoveInfo::iterator it = mMoveInfo.begin();
    for (;it != mMoveInfo.end(); ++it)
    {
        SCgObject *obj = it.key();
        QPointF offset =  toPoint - mStartPoint;

        QPair<QPointF, QPointF>& positions = it.value();
        QPointF newPos = positions.first + offset;
        obj->setPosition(newPos);
        positions.second = newPos;

        if(obj->type() == SCgObject::Pair)
        {
            setAndStoreDotPositions(static_cast<SCgPair*>(obj));
        }
    }
}

QUndoCommand *SCgMovingHelper::createCommand(SCgSceneBase *scene) const
{
    Q_ASSERT(scene);
    SCgCommandObjectMove* parent = new SCgCommandObjectMove(scene, mMoveInfo);
    /*child = */new SCgCommandChangePairBeginEndDots(scene, mChangedPairsDotPositions, parent);
    return parent;
}

void SCgMovingHelper::resetState()
{
    mMoveInfo.clear();
    mChangedPairsDotPositions.clear();
    mInitialPairsAngles.clear();
    mStartPoint = QPointF();
}

void SCgMovingHelper::storeInitialObjectPosition(SCgPair *pair)
{
    SCgObject *begin = pair->beginObject(), *end = pair->endObject();
    if(begin->type() == SCgObject::Node)
        mMoveInfo[begin] = QPair<QPointF, QPointF>(begin->position(), QPointF());

    if(end->type() == SCgObject::Node)
        mMoveInfo[end] = QPair<QPointF, QPointF>(end->position(), QPointF());

    const QVector<QPointF>& pairPoints = pair->points();
    qint32 pairsCount = pairPoints.count();
    Q_ASSERT(pairsCount >= 2);

    SCgCommandChangePairBeginEndDots::BeginEndPairDots emptyDots;
    SCgCommandChangePairBeginEndDots::BeginEndPairDots oldDots(pair->beginDotPosition(), pair->endDotPosition());

    mChangedPairsDotPositions[pair] = QPair<SCgCommandChangePairBeginEndDots::BeginEndPairDots,
            SCgCommandChangePairBeginEndDots::BeginEndPairDots>(oldDots, emptyDots);

    const QPointF& p2 = pairPoints.at(1);
    const QPointF& p1 = pairPoints.at(0);
    qreal startSegmentAngle = QLineF(p1, p2).angle();

    const QPointF& last = pairPoints.at(pairsCount - 1);
    const QPointF& penultimate = pairPoints.at(pairsCount - 2);
    qreal endSegmentAngle = QLineF(last, penultimate).angle();

    mInitialPairsAngles[pair] = QPair<qreal, qreal>(startSegmentAngle, endSegmentAngle);
}

void SCgMovingHelper::storeInitialObjectPosition(SCgObject *object)
{
    mMoveInfo[object] = QPair<QPointF, QPointF>(object->position(), QPointF());

    // For pairs we should either move connected node or change it's dot position
    if(object->type() == SCgObject::Pair)
    {
        SCgPair* pair = static_cast<SCgPair*>(object);
        storeInitialObjectPosition(pair);
    }

    SCgObject::SCgObjectList children = object->childObjects();
    foreach(SCgObject* o, children)
        storeInitialObjectPosition(o);
}

bool SCgMovingHelper::isInitialized() const
{
    return !mMoveInfo.isEmpty();
}
