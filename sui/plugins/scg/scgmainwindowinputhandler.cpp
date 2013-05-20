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
#include "scgmainwindowinputhandler.h"

#include "commands/scgcommandcreatepair.h"

#include "commands/scgcommandobjectdelete.h"
#include "commands/scgcommanddeletecontour.h"

#include "scgmainwindowscene.h"

#include "modes/scgmodemenu.h"
#include "modes/scgmodeselect.h"
#include "modes/scgmodebus.h"
#include "modes/scgmodecontour.h"
#include "modes/scgmodepair.h"

#include "widgets/menuWidget/sunmenurepresentation.h"

#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QGraphicsPathItem>

SCgMainWindowInputHandler::SCgMainWindowInputHandler(SunMenuRepresentation* nodeMenu, QObject* parent) :
    QObject(parent),
    SCgInputHandlerInterface(), mActiveMenu(nodeMenu)
{
    mAvailableModes.resize(ModeCount);

    SCgModeSelect* pureSelect = new SCgModeSelect(this);

    mMode = mAvailableModes[(int)ModeSelect] = new SCgModeMenu(this, nodeMenu, pureSelect);
    mAvailableModes[(int)ModeBus] = new SCgModeBus(this, pureSelect);
    mAvailableModes[(int)ModePair] = new SCgModePair(this, pureSelect);
    mAvailableModes[(int)ModeContour] = new SCgModeContour(this, pureSelect);

    mMode->activate();
}

SCgMainWindowInputHandler::~SCgMainWindowInputHandler()
{
    foreach(SCgModeInterface* mode, mAvailableModes)
        delete mode;

    mAvailableModes.clear();
}

void SCgMainWindowInputHandler::changeMode(Mode newMode)
{
    mMode->deactivate();

    mMode = mAvailableModes[(int)newMode];

    mMode->activate();
}

void SCgMainWindowInputHandler::keyPressEvent(QKeyEvent *keyEvent)
{
    // switch to new mode
    if (keyEvent->key() == Qt::Key_1)   { changeMode(ModeSelect); return; }
    if (keyEvent->key() == Qt::Key_2)   { changeMode(ModePair); return; }
    if (keyEvent->key() == Qt::Key_3)   { changeMode(ModeBus); return; }
    if (keyEvent->key() == Qt::Key_4)   { changeMode(ModeContour); return; }
    mMode->keyPressEvent(keyEvent);
}

void SCgMainWindowInputHandler::keyReleaseEvent(QKeyEvent *keyEvent)
{
    mMode->keyReleaseEvent(keyEvent);
}

void SCgMainWindowInputHandler::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    mMode->mouseDoubleClickEvent(mouseEvent);
}

void SCgMainWindowInputHandler::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent, bool afterSceneEvent)
{
    mMode->mouseMoveEvent(mouseEvent, afterSceneEvent);
}

void SCgMainWindowInputHandler::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent, bool afterSceneEvent)
{
    mMode->mousePressEvent(mouseEvent, afterSceneEvent);
}

void SCgMainWindowInputHandler::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent, bool afterSceneEvent)
{
    mMode->mouseReleaseEvent(mouseEvent, afterSceneEvent);
}

void SCgMainWindowInputHandler::wheelEvent(QGraphicsSceneWheelEvent *wheelEvent){Q_UNUSED(wheelEvent);}
void SCgMainWindowInputHandler::contextMenuEvent(QGraphicsSceneContextMenuEvent *contextMenuEvent){Q_UNUSED(contextMenuEvent);}
void SCgMainWindowInputHandler::dragEnterEvent(QGraphicsSceneDragDropEvent *event){Q_UNUSED(event);}
void SCgMainWindowInputHandler::dragLeaveEvent(QGraphicsSceneDragDropEvent *event){Q_UNUSED(event);}
void SCgMainWindowInputHandler::dragMoveEvent(QGraphicsSceneDragDropEvent *event){Q_UNUSED(event);}
void SCgMainWindowInputHandler::drawBackground(QPainter *painter, const QRectF &rect){Q_UNUSED(painter);Q_UNUSED(rect);}
void SCgMainWindowInputHandler::drawForeground(QPainter *painter, const QRectF &rect){Q_UNUSED(painter);Q_UNUSED(rect);}
void SCgMainWindowInputHandler::dropEvent(QGraphicsSceneDragDropEvent *event){Q_UNUSED(event);}
void SCgMainWindowInputHandler::focusInEvent(QFocusEvent *focusEvent){Q_UNUSED(focusEvent);}
void SCgMainWindowInputHandler::focusOutEvent(QFocusEvent *focusEvent){Q_UNUSED(focusEvent);}
void SCgMainWindowInputHandler::helpEvent(QGraphicsSceneHelpEvent *helpEvent){Q_UNUSED(helpEvent);}
void SCgMainWindowInputHandler::inputMethodEvent(QInputMethodEvent *event){Q_UNUSED(event);}


void SCgMainWindowInputHandler::drawPairMenuTriggered()
{
    SCgModePair* pairMode = (SCgModePair*)mAvailableModes[ModePair];
    connect(pairMode, SIGNAL(operationCompleted(bool)), this, SLOT(pairDrawingOperationCompleted(bool)));
    changeMode(ModePair);
    pairMode->startPairCreation(qobject_cast<SCgVisualObject*>(mActiveMenu->associatedObject()),
                                mActiveMenu->scenePos());
}

void SCgMainWindowInputHandler::pairDrawingOperationCompleted(bool success)
{
    Q_UNUSED(success);
    SCgModePair* pairMode = qobject_cast<SCgModePair*>(QObject::sender());
    if(pairMode == NULL) return;
    disconnect(pairMode, SIGNAL(operationCompleted(bool)), this, SLOT(pairDrawingOperationCompleted(bool)));
    changeMode(ModeSelect);
}


void SCgMainWindowInputHandler::deleteJustContour()
{
//    QList<SCgVisualContour*> contourList;
//    foreach(QGraphicsItem* it, mScene->selectedItems())
//    {
//        if (it->type() == SCgVisualObject::SCgContourType)
//            contourList.append(static_cast<SCgVisualContour*>(it));
//    }

//    SCgBaseCommand* cmd = 0;

//    foreach(SCgVisualContour* contour, contourList)
//        if(! cmd)
//            cmd = new SCgCommandDeleteContour(mScene, contour);
//        else
//            new SCgCommandDeleteContour(mScene, contour, cmd);

//    mScene->appendUndoCommand(cmd);
}

void SCgMainWindowInputHandler::deleteSelected()
{
//    QList<QGraphicsItem*> selObjects = mScene->selectedItems();
//    QList<QGraphicsItem*>::iterator it = selObjects.begin();

//    SCgBaseCommand *cmd = 0;

//    for (; it != selObjects.end(); ++it)
//    {
//        // skip non SCg-objects
//        if ( !SCgVisualObject::isSCgObjectType((*it)->type()) )
//            continue;

//        SCgVisualObject *obj = static_cast<SCgVisualObject*>(*it);

//        if (!cmd)
//            cmd = new SCgCommandObjectDelete(mScene, obj);
//        else
//            new SCgCommandObjectDelete(mScene, obj, cmd);
//    }
//    // Delete points only if object is not deleted by previous operations
//    if(!cmd)
//    {
//        SCgVisualPointObject* parent = 0;
//        SCgVisualPointObject::PointFVector newPoints;
//        QList<int> delIndexes; //< list with indexes of points which will be deleted

//        for (it = selObjects.begin(); it != selObjects.end(); ++it)
//        {
//            // skip none Point items
//            if ( (*it)->type() != PointGraphicsItem::Type)
//                continue;

//            PointGraphicsItem *item = static_cast<PointGraphicsItem*>(*it);
//            if(!parent)
//            {
//                parent = item->parentSCgPointObject();
//                newPoints = parent->points();
//                if(newPoints.size() < 2 || (parent->type() == SCgVisualObject::SCgContourType && newPoints.size() < 3))
//                    break; //If there are not enough points, we  should do nothing.
//            }
//            //We expect, that at the same time only one SCgPointObject is editable.
//            Q_ASSERT(parent == item->parentSCgPointObject());

//            delIndexes.push_back(item->pointIndex());
//        }
//        if(parent)
//        {
//            // Sort list in back order. Because after erasing item from vector, indexes
//            // can be wrong. So we should delete in back order.
//            qSort(delIndexes.begin(), delIndexes.end(), qGreater<int>());

//            foreach(const int& index, delIndexes)
//            {
//                int s = newPoints.size();
//                if(s > 2 && (parent->type() != SCgVisualObject::SCgContourType || s > 3))//< another checking of points count
//                    newPoints.erase(newPoints.begin()+index);
//            }

//            if(newPoints != parent->points())
//                cmd = new SCgCommandPointsChange(mScene, parent, newPoints);
//        }
//    }

//    if(cmd)
//        mScene->appendUndoCommand(cmd);
}


