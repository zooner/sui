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
#include "scgcommandcreatebus.h"

SCgCommandCreateBus::SCgCommandCreateBus(SCgSceneBase *scene,
                                           SCgNode *owner,
                                           const QVector<QPointF> &points,
                                           SCgContour *parentContour,
                                           QUndoCommand *parent) :
    SCgBaseCommand(scene, 0, parent),
    mOwner(owner),
    mPoints(points),
    mParentContour(parentContour)
{

    setText(QObject::tr("Create bus"));
}

SCgCommandCreateBus::~SCgCommandCreateBus()
{
}

void SCgCommandCreateBus::busDestroyed()
{
    mObject = 0;
}

void SCgCommandCreateBus::redo()
{
    SCgBaseCommand::redo();

    SCgBus *bus = 0;
    if (mObject == 0)
    {
        bus = mScene->construction()->createBus();
        bus->setOwner(mOwner);

        mObject = bus;

        QPointF pt;
        foreach (pt, mPoints)
            bus->appendPoint(pt);

        connect(mObject, SIGNAL(destroyed()), this, SLOT(busDestroyed()));
    }else
    {
        mScene->construction()->appendObject(mObject);
        bus = qobject_cast<SCgBus*>(mObject);
    }

    bus->setOwner(mOwner);
    bus->updatePoints();
}

void SCgCommandCreateBus::undo()
{
    Q_ASSERT_X(mObject != 0,
               "void SCgCommandCreateBus::undo()",
               "Bus doesn't exists");

    mScene->construction()->removeObject(mObject);
    SCgBus *bus = qobject_cast<SCgBus*>(mObject);
    bus->setOwner(mOwner);

    SCgBaseCommand::undo();
}
