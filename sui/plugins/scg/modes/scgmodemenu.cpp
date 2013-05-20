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

#include <QAction>
#include <QTimer>


#include "scgmodemenu.h"

#include "scgprecompiled.h"
#include "widgets/menuWidget/menuitemmodel.h"
#include "widgets/menuWidget/sunmenurepresentation.h"
#include "widgets/menuWidget/sizableItems/textsizableitem.h"

SCgModeMenu::SCgModeMenu(SCgInputHandlerInterface* inputHandler, SunMenuRepresentation *nodeMenu, SCgModeInterface* childMode):
    SCgModeInterface(inputHandler, childMode), mMenuRepresentation(nodeMenu)
{
    mShowMenuTimer = new QTimer(this);
    connect(mShowMenuTimer, SIGNAL(timeout()), this, SLOT(showMenu()));
}

SCgModeMenu::~SCgModeMenu()
{

}

void SCgModeMenu::keyPressEvent ( QKeyEvent * keyEvent )
{
    if (mDecoratedMode)
        mDecoratedMode->keyPressEvent(keyEvent);
}

void SCgModeMenu::keyReleaseEvent ( QKeyEvent * keyEvent )
{
    if (mDecoratedMode)
        mDecoratedMode->keyReleaseEvent(keyEvent);
}

void SCgModeMenu::mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * mouseEvent )
{
    if (mDecoratedMode)
        mDecoratedMode->mouseDoubleClickEvent(mouseEvent);
}

void SCgModeMenu::mouseMoveEvent (QGraphicsSceneMouseEvent * mouseEvent , bool afterSceneEvent)
{
    if(afterSceneEvent)
    {
        if(mDecoratedMode)
            mDecoratedMode->mouseMoveEvent(mouseEvent, afterSceneEvent);
        return;
    }

    QGraphicsItem* menuItem = mMenuRepresentation->menuItem();
    //TODO: need more accurate hit testing
    if((menuItem->scene() == scene() && !mMenuRepresentation->menuContainsPoint(mouseEvent->scenePos()))
            || mouseEvent->buttons() !=Qt::NoButton)
    {
        associateMenuWithObject(NULL, mSceneMenuPosition);
    }
    else if(menuItem->scene() != scene())
    {
        mShowMenuTimer->stop();
        SCgVisualObject* obj = scene()->scgVisualObjectAt(mouseEvent->scenePos());
        if(obj!=NULL)
        {
            mSceneMenuPosition = mouseEvent->scenePos();
            mShowMenuTimer->start(MenuTimerDelayInMs);
        }
    }

    if (mDecoratedMode)
        mDecoratedMode->mouseMoveEvent(mouseEvent, afterSceneEvent);
}

void SCgModeMenu::mousePressEvent (QGraphicsSceneMouseEvent * mouseEvent , bool afterSceneEvent)
{
    if (mDecoratedMode)
        mDecoratedMode->mousePressEvent(mouseEvent, afterSceneEvent);
}

void SCgModeMenu::mouseReleaseEvent (QGraphicsSceneMouseEvent * mouseEvent , bool afterSceneEvent)
{
    if(mDecoratedMode)
        mDecoratedMode->mouseReleaseEvent(mouseEvent, afterSceneEvent);
}

void SCgModeMenu::showMenu()
{
    SCgVisualObject* obj = scene()->scgVisualObjectAt(mSceneMenuPosition);
    associateMenuWithObject(obj, mSceneMenuPosition);
    mShowMenuTimer->stop();
}

void SCgModeMenu::associateMenuWithObject(SCgVisualObject* object, const QPointF& scenePos)
{
    if(object == NULL)
    {
        mMenuRepresentation->assoiciateWith(NULL);
        hideMenu();
        return;
    }

    QGraphicsItem* menuItem = mMenuRepresentation->menuItem();
    switch (object->type()) {
    case SCgVisualObject::SCgNodeType:
        mMenuRepresentation->setInnerRadius(object->boundingRect().width());
        menuItem->setPos(object->pos());
        scene()->addItem(menuItem);
        break;
    case SCgVisualObject::SCgPairType:
    case SCgVisualObject::SCgBusType:
        mMenuRepresentation->setInnerRadius(10);
        menuItem->setPos(scenePos);
        scene()->addItem(menuItem);
        break;
    case SCgVisualObject::SCgContourType:

        break;
    default:
        break;
    }
    mMenuRepresentation->assoiciateWith(object);
}

void SCgModeMenu::hideMenu()
{
    mShowMenuTimer->stop();
    mMenuRepresentation->resetMenu();
    scene()->removeItem(mMenuRepresentation->menuItem());
}

void SCgModeMenu::activate()
{
    if(mDecoratedMode)
        mDecoratedMode->activate();
}

void SCgModeMenu::deactivate()
{
    hideMenu();
    if(mDecoratedMode)
        mDecoratedMode->deactivate();
}
