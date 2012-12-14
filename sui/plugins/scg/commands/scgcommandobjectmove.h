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

#ifndef SCGCOMMANDOBJECTMOVE_H
#define SCGCOMMANDOBJECTMOVE_H

#include "scgbasecommand.h"
#include <QMap>
#include <QPair>
#include <QPointF>

/*! Moves objects from it's initial position to finish position.
 * Use \ref SCgCommandObjectMove::MoveInfo structure to move group of objects
 * First item in QPair - old position, second - new position.
 */
class SCgCommandObjectMove : public SCgBaseCommand
{
public:
    typedef QMap<SCgObject*, QPair<QPointF, QPointF> > MoveInfo;

    explicit SCgCommandObjectMove(SCgSceneBase *scene,
                                  SCgObject* obj,
                                  const QPointF& oldPos,
                                  const QPointF& newPos,
                                  QUndoCommand *parent = 0 );

    explicit SCgCommandObjectMove(SCgSceneBase *scene,
                                  const MoveInfo& moveInfo,
                                  QUndoCommand *parent = 0 );

    virtual ~SCgCommandObjectMove();

protected:
    void redo();
    void undo();

private:
    MoveInfo mMoveInfo;
};


#endif // SCGCOMMANDOBJECTMOVE_H
