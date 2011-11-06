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
#include "scgcommandcreatenode.h"

SCgCommandCreateNode::SCgCommandCreateNode(SCgSceneBase *scene,
                                           const QPointF &point,
                                           SCgVisualContour *parentContour,
                                           QUndoCommand *parent) :
    SCgBaseCommand(scene, 0, parent),
    mPoint(point),
    mParentContour(parentContour)
{


    setText(QObject::tr("Create node"));
}

SCgCommandCreateNode::~SCgCommandCreateNode()
{
    delete mObject;
}

void SCgCommandCreateNode::nodeDestroyed()
{
    mObject = 0;
}

void SCgCommandCreateNode::undo()
{
    Q_ASSERT_X(mObject != 0,
               "void SCgCommandCreateNode::undo()",
               "Node doesn't exists");

    mScene->construction()->removeObject(mObject);

    SCgBaseCommand::undo();
}

void SCgCommandCreateNode::redo()
{

    if (mObject == 0)
    {
        mObject = mScene->construction()->createNode();
        mObject->setPosition(mPoint);
        mObject->setObjectType(ScElementType(ScNode | ScConst));

        connect(mObject, SIGNAL(destroyed()), this, SLOT(nodeDestroyed()));
    }else
        mScene->construction()->appendObject(mObject);


    SCgBaseCommand::redo();
}
