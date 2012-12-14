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
#include "scgmodeselect.h"
#include "scgmovinghelper.h"

#include "commands/scgcommandcreatenode.h"


SCgModeSelect::SCgModeSelect(SCgInputHandlerInterface* inputHandler, SCgModeInterface* childMode):
                SCgModeInterface(inputHandler, childMode),
                mCurrentPointObject(0)
{
    mMovingHelper = new SCgMovingHelper();
}

SCgModeSelect::~SCgModeSelect()
{

}

void SCgModeSelect::keyPressEvent ( QKeyEvent * keyEvent )
{
    if(mDecoratedMode)
        mDecoratedMode->keyPressEvent(keyEvent);
}

void SCgModeSelect::keyReleaseEvent ( QKeyEvent * keyEvent )
{
    if(mDecoratedMode)
        mDecoratedMode->keyReleaseEvent(keyEvent);
}

void SCgModeSelect::mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * mouseEvent )
{
    mouseEvent->accept();

    QPointF mousePos = mouseEvent->scenePos();

    // left button
    if (mouseEvent->button() == Qt::LeftButton)
    {
        SCgObject *object = scene()->scgObjectAt(mousePos);
        //! TODO: contour
        if (object == 0)
            scene()->pushCommand(new SCgCommandCreateNode(scene(), mousePos, 0, 0));
    }

    if(mDecoratedMode)
        mDecoratedMode->mouseDoubleClickEvent(mouseEvent);
}

void SCgModeSelect::mouseMoveEvent (QGraphicsSceneMouseEvent * mouseEvent , bool afterSceneEvent)
{
    if(afterSceneEvent)
    {
        if(mDecoratedMode)
            mDecoratedMode->mouseMoveEvent(mouseEvent, afterSceneEvent);
        return;
    }

    if (mouseEvent->buttons() & Qt::LeftButton)
    {
        // We process this event only if there is SCgObject under mouse
        SCgObject* obj = scene()->scgObjectAt(mouseEvent->scenePos());

        // Assume that selection does not change during move operation
        if(obj && !mMovingHelper->isInitialized())
        {
            // Determine the list of items that need to be moved.
            QList<QGraphicsItem*> selectedItems = scene()->selectedItems();
            mMovingHelper->initializeWithObjects(selectedItems, mouseEvent->buttonDownScenePos(Qt::LeftButton));
        }

        if(mMovingHelper->isInitialized())
        {
            mouseEvent->accept();
            mMovingHelper->moveTo(mouseEvent->scenePos());
            return;
        }
    }

    mouseEvent->ignore();
    if(mDecoratedMode)
        mDecoratedMode->mouseMoveEvent(mouseEvent, afterSceneEvent);
}

void SCgModeSelect::mousePressEvent (QGraphicsSceneMouseEvent * mouseEvent , bool afterSceneEvent)
{
    if(afterSceneEvent)
    {
        if(mDecoratedMode)
            mDecoratedMode->mousePressEvent(mouseEvent, afterSceneEvent);
        return;
    }

    if(mDecoratedMode)
        mDecoratedMode->mousePressEvent(mouseEvent, afterSceneEvent);
    mouseEvent->ignore();

}

void SCgModeSelect::mouseReleaseEvent ( QGraphicsSceneMouseEvent * mouseEvent, bool afterSceneEvent )
{
    if(afterSceneEvent)
    {
        if(mDecoratedMode)
            mDecoratedMode->mouseReleaseEvent(mouseEvent, afterSceneEvent);
        return;
    }

    if(!afterSceneEvent && mMovingHelper->isInitialized())
    {
        mouseEvent->accept();
        bool isItemsMoved = (mouseEvent->scenePos() != mouseEvent->buttonDownScenePos(Qt::LeftButton));
        if(isItemsMoved)
        {
            scene()->pushCommand(mMovingHelper->createCommand(scene()));
        }
        mMovingHelper->resetState();

        return;
    }

    if(mDecoratedMode)
        mDecoratedMode->mouseReleaseEvent(mouseEvent, afterSceneEvent);
}

void SCgModeSelect::activate()
{
    if(mDecoratedMode)
        mDecoratedMode->activate();
}


void SCgModeSelect::deactivate()
{
    if(mDecoratedMode)
        mDecoratedMode->deactivate();
}
