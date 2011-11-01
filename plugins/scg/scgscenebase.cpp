/*
-----------------------------------------------------------------------------
This source file is part of OSTIS (Open Semantic Technology for Intelligent Systems)
For the latest info, see http://www.ostis.net

Copyright (c) 2011 OSTIS

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
#include "scgscenebase.h"

#include "interfaces/SCgInputHandlerInterface.h"
#include "objects/scgconstruction.h"

#include <QUndoStack>
#include <QUndoCommand>
#include <QGraphicsSceneContextMenuEvent>
#include <QFocusEvent>

SCgSceneBase::SCgSceneBase(SCgInputHandlerInterface *inputHandler, QObject *parent) :
    QGraphicsScene(parent),
    mInputHandler(inputHandler),
    mConstruction(0)
{
    Q_ASSERT(mInputHandler != 0);

    mInputHandler->setScene(this);
    mUndoStack = new QUndoStack(this);

    mConstruction = new SCgConstruction(this);
    mConstruction->attachObserver(this);
}

SCgSceneBase::~SCgSceneBase()
{
    mConstruction->detachObserver(this);
    delete mConstruction;

    delete mUndoStack;
}

void SCgSceneBase::setInputHandler(SCgInputHandlerInterface* handler)
{
    mInputHandler = handler;
}

void SCgSceneBase::appendUndoCommand(QUndoCommand *command)
{
    mUndoStack->push(command);
}

void SCgSceneBase::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    Q_ASSERT(mInputHandler != 0);
    mInputHandler->contextMenuEvent(event);

    if (!event->isAccepted())
        QGraphicsScene::contextMenuEvent(event);
}

void SCgSceneBase::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    Q_ASSERT(mInputHandler != 0);
    mInputHandler->dragEnterEvent(event);

    if (!event->isAccepted())
        QGraphicsScene::dragEnterEvent(event);
}

void SCgSceneBase::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    Q_ASSERT(mInputHandler != 0);
    mInputHandler->dragLeaveEvent(event);

    if (!event->isAccepted())
        QGraphicsScene::dragLeaveEvent(event);
}

void SCgSceneBase::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    Q_ASSERT(mInputHandler != 0);
    mInputHandler->dragMoveEvent(event);

    if (!event->isAccepted())
        QGraphicsScene::dragMoveEvent(event);
}

void SCgSceneBase::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_ASSERT(mInputHandler != 0);
    mInputHandler->drawBackground(painter, rect);

    QGraphicsScene::drawBackground(painter, rect);
}

void SCgSceneBase::drawForeground(QPainter *painter, const QRectF &rect)
{
    Q_ASSERT(mInputHandler != 0);
    mInputHandler->drawForeground(painter, rect);

    QGraphicsScene::drawForeground(painter, rect);
}

void SCgSceneBase::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    Q_ASSERT(mInputHandler != 0);
    mInputHandler->dropEvent(event);

    if (!event->isAccepted())
        QGraphicsScene::dropEvent(event);
}

void SCgSceneBase::focusInEvent(QFocusEvent *event)
{
    Q_ASSERT(mInputHandler != 0);
    mInputHandler->focusInEvent(event);

    if (!event->isAccepted())
        QGraphicsScene::focusInEvent(event);
}

void SCgSceneBase::focusOutEvent(QFocusEvent *event)
{
    Q_ASSERT(mInputHandler != 0);
    mInputHandler->focusOutEvent(event);

    if (!event->isAccepted())
        QGraphicsScene::focusOutEvent(event);
}

void SCgSceneBase::helpEvent(QGraphicsSceneHelpEvent *event)
{
    Q_ASSERT(mInputHandler != 0);
    mInputHandler->helpEvent(event);

    if (!event->isAccepted())
        QGraphicsScene::helpEvent(event);
}

void SCgSceneBase::inputMethodEvent(QInputMethodEvent *event)
{
    Q_ASSERT(mInputHandler != 0);
    mInputHandler->inputMethodEvent(event);

    if (!event->isAccepted())
        QGraphicsScene::inputMethodEvent(event);
}

void SCgSceneBase::keyPressEvent(QKeyEvent *event)
{
    Q_ASSERT(mInputHandler != 0);
    mInputHandler->keyPressEvent(event);

    if (!event->isAccepted())
        QGraphicsScene::keyPressEvent(event);
}

void SCgSceneBase::keyReleaseEvent(QKeyEvent *event)
{
    Q_ASSERT(mInputHandler != 0);
    mInputHandler->keyReleaseEvent(event);

    if (!event->isAccepted())
        QGraphicsScene::keyReleaseEvent(event);
}

void SCgSceneBase::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    Q_ASSERT(mInputHandler != 0);
    mInputHandler->mouseDoubleClickEvent(event);

    if (!event->isAccepted())
        QGraphicsScene::mouseDoubleClickEvent(event);
}

void SCgSceneBase::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    Q_ASSERT(mInputHandler != 0);
    mInputHandler->mouseMoveEvent(event);

    if (!event->isAccepted())
        QGraphicsScene::mouseMoveEvent(event);
}

void SCgSceneBase::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_ASSERT(mInputHandler != 0);
    mInputHandler->mousePressEvent(event);

    if (!event->isAccepted())
        QGraphicsScene::mousePressEvent(event);
}

void SCgSceneBase::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_ASSERT(mInputHandler != 0);
    mInputHandler->mouseReleaseEvent(event);

    if (!event->isAccepted())
        QGraphicsScene::mouseReleaseEvent(event);
}

void SCgSceneBase::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    Q_ASSERT(mInputHandler != 0);
    mInputHandler->wheelEvent(event);

    if (!event->isAccepted())
        QGraphicsScene::wheelEvent(event);
}

