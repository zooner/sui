/*
 * scgmodeselect.cpp
 *
 *  Created on: 14.07.2011
 *      Author: ZooNer
 */

#include "scgprecompiled.h"
#include "scgmodeselect.h"

#include "commands/scgcommandcreatenode.h"


SCgModeSelect::SCgModeSelect(SCgInputHandlerInterface* inputHandler):
                SCgModeInterface(inputHandler),
                mIsItemsMoved(false),
                mCurrentPointObject(0)
{

}

SCgModeSelect::~SCgModeSelect()
{

}

void SCgModeSelect::keyPressEvent ( QKeyEvent * keyEvent )
{

}

void SCgModeSelect::keyReleaseEvent ( QKeyEvent * keyEvent )
{

}

void SCgModeSelect::mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * mouseEvent )
{
    QPointF mousePos = mouseEvent->scenePos();

    // left button
    if (mouseEvent->button() == Qt::LeftButton)
    {
        SCgObject *object = scene()->scgObjectAt(mousePos);
        //! TODO: contour
        if (object == 0)
            scene()->appendUndoCommand(new SCgCommandCreateNode(scene(), mousePos, 0, 0));
    }
}

void SCgModeSelect::mouseMoveEvent ( QGraphicsSceneMouseEvent * mouseEvent )
{
    if(mouseEvent->buttons() == Qt::LeftButton && !mIsItemsMoved)
    {

    }
}

void SCgModeSelect::mousePressEvent ( QGraphicsSceneMouseEvent * mouseEvent )
{

}

void SCgModeSelect::mouseReleaseEvent ( QGraphicsSceneMouseEvent * mouseEvent )
{
    if(mIsItemsMoved)
    {

    }
}



void SCgModeSelect::activate()
{

}


void SCgModeSelect::deactivate()
{
    mIsItemsMoved = false;
}
