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
#include "scgmodecontour.h"

#include <QVector2D>


#include "commands/scgcommandcreatecontour.h"

#include "scgpathitem.h"


SCgModeContour::SCgModeContour(SCgInputHandlerInterface* inputHandler, SCgModeInterface* childMode):
                SCgModeInterface(inputHandler, childMode),
                mPathItem(0),
                mParentContour(0),
                mPassMouseReleaseEvent(false)
{

}

SCgModeContour::~SCgModeContour()
{

}

QList<QGraphicsItem* > SCgModeContour::selectItemsForContour() const
{
    QList<QGraphicsItem* > result;
    foreach(QGraphicsItem* it, scene()->items())
    {
        bool isWithinPath = it->collidesWithPath( it->mapFromScene(mPathItem->path()), Qt::ContainsItemShape);
        bool hasSameParent = it->parentItem() == mParentContour;

        if (isWithinPath && hasSameParent)
            result.append(it);
    }

    return result;
}

void SCgModeContour::keyPressEvent (QKeyEvent * keyEvent)
{
    if(mDecoratedMode)
        mDecoratedMode->keyPressEvent(keyEvent);
}

void SCgModeContour::keyReleaseEvent (QKeyEvent * keyEvent)
{
    if(mDecoratedMode)
        mDecoratedMode->keyReleaseEvent(keyEvent);
}

void SCgModeContour::mouseDoubleClickEvent (QGraphicsSceneMouseEvent * mouseEvent)
{
    if(mDecoratedMode)
        mDecoratedMode->mouseDoubleClickEvent(mouseEvent);
}

void SCgModeContour::mouseMoveEvent ( QGraphicsSceneMouseEvent * mouseEvent, bool afterSceneEvent )
{
    if(afterSceneEvent)
    {
        if(mDecoratedMode)
            mDecoratedMode->mouseMoveEvent(mouseEvent, afterSceneEvent);
        return;
    }

    if(mPathItem)
    {
        mouseEvent->accept();

        QVector2D vec(mouseEvent->scenePos() - mPathItem->points().first());

        QPen pen = mPathItem->pen();
        Qt::PenStyle s;

        if (vec.length() < 5.f)
            s = Qt::SolidLine;
        else
            s = Qt::DashDotLine;

        if(s != pen.style())
        {
            pen.setStyle(s);
            mPathItem->setPen(pen);
        }

        mPathItem->update(mouseEvent->scenePos());

        return;
    }

    if(mDecoratedMode)
        mDecoratedMode->mouseMoveEvent(mouseEvent, afterSceneEvent);
}

void SCgModeContour::mousePressEvent (QGraphicsSceneMouseEvent * mouseEvent , bool afterSceneEvent)
{
    if(afterSceneEvent)
    {
        if(mDecoratedMode)
            mDecoratedMode->mousePressEvent(mouseEvent, afterSceneEvent);
        return;
    }

    QPointF mousePos = mouseEvent->scenePos();
    // Process this event only if there is no items under mouse.
    QGraphicsItem* scgVisObjectUnderMouse = scene()->scgVisualObjectAt(mousePos);
    if(!mPathItem && scgVisObjectUnderMouse)
    {
        if(mDecoratedMode)
            mDecoratedMode->mousePressEvent(mouseEvent, afterSceneEvent);

        mPassMouseReleaseEvent = true;
        return;
    }

    // left button
    if (mouseEvent->button() == Qt::LeftButton)
    {
       mouseEvent->accept();

        if (!mPathItem)
        {
            mPathItem = new SCgPathItem(scene(), true);
            mPathItem->pushPoint(mousePos);

            QPen pen;

            pen.setColor(Qt::green);
            pen.setCapStyle(Qt::RoundCap);
            pen.setStyle(Qt::DashLine);
            pen.setWidthF(2.f);

            mPathItem->setPen(pen);
            return;
        }

        QVector<QPointF> points = mPathItem->points();
        QVector2D vec(points.at(0) - mousePos);

        if (vec.length() < 5.f && points.size() > 2)
        {
            // get child items
            QList<QGraphicsItem*> childs = selectItemsForContour();

            scene()->pushCommand(new SCgCommandCreateContour(scene(), childs, points, 0));

            mParentContour = 0;
            delete mPathItem;
            mPathItem = 0;
        }
        else
        {
            mPathItem->pushPoint(mousePos);
        }
    }

    // right button
    if (mouseEvent->button() == Qt::RightButton)
    {
        if (mPathItem)
        {
            mouseEvent->accept();

            mPathItem->popPoint();
            if (mPathItem->points().empty())
                delete mPathItem;
        }
    }
}

void SCgModeContour::mouseReleaseEvent ( QGraphicsSceneMouseEvent * mouseEvent, bool afterSceneEvent )
{
    if(afterSceneEvent)
    {
        if(mDecoratedMode)
            mDecoratedMode->mouseReleaseEvent(mouseEvent, afterSceneEvent);
        return;
    }

    if(mPassMouseReleaseEvent && mDecoratedMode)
        mDecoratedMode->mouseReleaseEvent(mouseEvent, afterSceneEvent);

    mPassMouseReleaseEvent = false;
}


void SCgModeContour::activate()
{
    if(mDecoratedMode)
        mDecoratedMode->activate();
}


void SCgModeContour::deactivate()
{
    if (mPathItem)
        delete mPathItem;
    if(mDecoratedMode)
        mDecoratedMode->deactivate();
}
