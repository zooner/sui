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
#include "scgcommandobjectmove.h"

SCgCommandObjectMove::SCgCommandObjectMove(SCgSceneBase *scene,
                                           SCgObject *obj,
                                           const QPointF &oldPos,
                                           const QPointF &newPos,
                                           QUndoCommand *parent):
        SCgBaseCommand(scene, obj, parent)
{
    mMoveInfo[obj] = QPair<QPointF, QPointF>(oldPos, newPos);
    setText(QObject::tr("Move item"));
}

SCgCommandObjectMove::SCgCommandObjectMove(SCgSceneBase *scene,
                                           const MoveInfo &moveInfo,
                                           QUndoCommand *parent):
        SCgBaseCommand(scene, 0, parent),
        mMoveInfo(moveInfo)
{
    setText(QObject::tr("Move items"));
}

SCgCommandObjectMove::~SCgCommandObjectMove()
{

}

void SCgCommandObjectMove::redo()
{
    SCgBaseCommand::redo();
    MoveInfo::const_iterator it = mMoveInfo.constBegin();
    for(;it != mMoveInfo.constEnd(); ++it)
    {
        SCgObject* obj = it.key();
        const QPair<QPointF, QPointF>& positions = it.value();
        obj->setPosition(positions.second);
    }
}

void SCgCommandObjectMove::undo()
{
    SCgBaseCommand::undo();
    MoveInfo::const_iterator it = mMoveInfo.constBegin();
    for(;it != mMoveInfo.constEnd(); ++it)
    {
        SCgObject* obj = it.key();
        const QPair<QPointF, QPointF>& positions = it.value();
        obj->setPosition(positions.first);
    }
}
