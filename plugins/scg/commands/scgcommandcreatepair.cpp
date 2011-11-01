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
#include "scgcommandcreatepair.h"

SCgCommandCreatePair::SCgCommandCreatePair(SCgSceneBase *scene,
                                           const QVector<QPointF> &points,
                                           SCgObject *beginObject,
                                           SCgObject *endObject,
                                           SCgContour *parentContour,
                                           QUndoCommand *parent) :
    SCgBaseCommand(scene, 0, parent),
    mPoints(points),
    mBeginObject(beginObject),
    mEndObject(endObject),
    mParentContour(parentContour)
{
    setText(QObject::tr("Create pair"));
}

SCgCommandCreatePair::~SCgCommandCreatePair()
{
    delete mObject;
}

void SCgCommandCreatePair::pairDestroyed()
{
    mObject = 0;
}

void SCgCommandCreatePair::redo()
{

    SCgBaseCommand::redo();

    Q_ASSERT(mBeginObject && mEndObject);
    SCgPair *pair = 0;
    if (mObject == 0)
    {
        pair = mScene->construction()->createPair(mBeginObject, mEndObject);
        mObject = pair;

        QPointF pt;
        foreach (pt, mPoints)
            pair->appendPoint(pt);

        pair->setBeginDotPosition(mBeginObject->calculateDotPosition(mPoints.front()));
        pair->setEndDotPosition(mEndObject->calculateDotPosition(mPoints.back()));

        connect(mObject, SIGNAL(destroyed()), this, SLOT(pairDestroyed()));
    }else
    {
        mScene->construction()->appendObject(mObject);
        pair = qobject_cast<SCgPair*>(mObject);

        pair->setBeginObject(mBeginObject);
        pair->setEndObject(mEndObject);
    }

    pair->updateDotCoordinates();
}

void SCgCommandCreatePair::undo()
{
    Q_ASSERT_X(mObject != 0,
               "void SCgCommandCreatePair::undo()",
               "Pair doesn't exists");

    mScene->construction()->removeObject(mObject);
    SCgPair *pair = qobject_cast<SCgPair*>(mObject);

    pair->setBeginObject(0);
    pair->setEndObject(0);

    SCgBaseCommand::undo();
}
