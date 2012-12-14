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

void SCgSceneBase::pushCommand(QUndoCommand *command)
{
    Q_ASSERT(command);
    mUndoStack->push(command);
}

void SCgSceneBase::beginMacro(const QString &name)
{
    mUndoStack->beginMacro(name);
}

void SCgSceneBase::endMacro()
{
    mUndoStack->endMacro();
}

QUndoStack* SCgSceneBase::undoStack()
{
    return mUndoStack;
}

void SCgSceneBase::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    Q_ASSERT(mInputHandler != 0);
    event->ignore();

    if (!event->isAccepted())
        QGraphicsScene::contextMenuEvent(event);

    mInputHandler->contextMenuEvent(event);
}

void SCgSceneBase::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    Q_ASSERT(mInputHandler != 0);
    event->ignore();

    if (!event->isAccepted())
        QGraphicsScene::dragEnterEvent(event);

    mInputHandler->dragEnterEvent(event);
}

void SCgSceneBase::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    Q_ASSERT(mInputHandler != 0);
    event->ignore();

    if (!event->isAccepted())
        QGraphicsScene::dragLeaveEvent(event);

    mInputHandler->dragLeaveEvent(event);
}

void SCgSceneBase::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    Q_ASSERT(mInputHandler != 0);
    event->ignore();

    if (!event->isAccepted())
        QGraphicsScene::dragMoveEvent(event);

    mInputHandler->dragMoveEvent(event);
}

void SCgSceneBase::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_ASSERT(mInputHandler != 0);

    QGraphicsScene::drawBackground(painter, rect);

    mInputHandler->drawBackground(painter, rect);
}

void SCgSceneBase::drawForeground(QPainter *painter, const QRectF &rect)
{
    Q_ASSERT(mInputHandler != 0);

    QGraphicsScene::drawForeground(painter, rect);

    mInputHandler->drawForeground(painter, rect);
}

void SCgSceneBase::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    Q_ASSERT(mInputHandler != 0);
    event->ignore();

    if (!event->isAccepted())
        QGraphicsScene::dropEvent(event);

    mInputHandler->dropEvent(event);
}

void SCgSceneBase::focusInEvent(QFocusEvent *event)
{
    Q_ASSERT(mInputHandler != 0);
    event->ignore();

    if (!event->isAccepted())
        QGraphicsScene::focusInEvent(event);

    mInputHandler->focusInEvent(event);
}

void SCgSceneBase::focusOutEvent(QFocusEvent *event)
{
    Q_ASSERT(mInputHandler != 0);
    event->ignore();

    if (!event->isAccepted())
        QGraphicsScene::focusOutEvent(event);

    mInputHandler->focusOutEvent(event);
}

void SCgSceneBase::helpEvent(QGraphicsSceneHelpEvent *event)
{
    Q_ASSERT(mInputHandler != 0);
    event->ignore();

    if (!event->isAccepted())
        QGraphicsScene::helpEvent(event);

    mInputHandler->helpEvent(event);
}

void SCgSceneBase::inputMethodEvent(QInputMethodEvent *event)
{
    Q_ASSERT(mInputHandler != 0);
    event->ignore();

    if (!event->isAccepted())
        QGraphicsScene::inputMethodEvent(event);

    mInputHandler->inputMethodEvent(event);
}

void SCgSceneBase::keyPressEvent(QKeyEvent *event)
{
    Q_ASSERT(mInputHandler != 0);
    event->ignore();

    if (!event->isAccepted())
        QGraphicsScene::keyPressEvent(event);

    mInputHandler->keyPressEvent(event);
}

void SCgSceneBase::keyReleaseEvent(QKeyEvent *event)
{
    Q_ASSERT(mInputHandler != 0);
    event->ignore();

    if (!event->isAccepted())
        QGraphicsScene::keyReleaseEvent(event);

    mInputHandler->keyReleaseEvent(event);
}

void SCgSceneBase::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    Q_ASSERT(mInputHandler != 0);
    event->ignore();

    if (!event->isAccepted())
        QGraphicsScene::mouseDoubleClickEvent(event);

    mInputHandler->mouseDoubleClickEvent(event);
}

void SCgSceneBase::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    Q_ASSERT(mInputHandler != 0);
    event->ignore();

    mInputHandler->mouseMoveEvent(event, false);

    if (!event->isAccepted())
    {
        QGraphicsScene::mouseMoveEvent(event);
        mInputHandler->mouseMoveEvent(event, true);
    }
}

void SCgSceneBase::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_ASSERT(mInputHandler != 0);
    event->ignore();

    mInputHandler->mousePressEvent(event, false);

    if (!event->isAccepted())
    {
        QGraphicsScene::mousePressEvent(event);
        mInputHandler->mousePressEvent(event, true);
    }
}

void SCgSceneBase::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_ASSERT(mInputHandler != 0);
    event->ignore();

    mInputHandler->mouseReleaseEvent(event, false);

    if (!event->isAccepted())
    {
        QGraphicsScene::mouseReleaseEvent(event);
        mInputHandler->mouseReleaseEvent(event, true);
    }
}

void SCgSceneBase::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    Q_ASSERT(mInputHandler != 0);
    event->ignore();

    if (!event->isAccepted())
        QGraphicsScene::wheelEvent(event);

    mInputHandler->wheelEvent(event);
}
