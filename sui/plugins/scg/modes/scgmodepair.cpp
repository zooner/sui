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
#include "scgmodepair.h"

#include "commands/scgcommandcreatepair.h"

#include "scgpathitem.h"

SCgModePair::SCgModePair(SCgInputHandlerInterface* inputHandler, SCgModeInterface* childMode):
                SCgModeInterface(inputHandler, childMode),
                mPathItem(0),
                mObjectAtFirstPoint(0),
                mPassMouseReleaseEvent(false)
{

}

SCgModePair::~SCgModePair()
{
    if (mPathItem)
        delete mPathItem;
}

void SCgModePair::keyPressEvent ( QKeyEvent * keyEvent )
{
    if (mDecoratedMode)
        mDecoratedMode->keyPressEvent(keyEvent);
}

void SCgModePair::keyReleaseEvent ( QKeyEvent * keyEvent )
{
    if (mDecoratedMode)
        mDecoratedMode->keyReleaseEvent(keyEvent);
}

void SCgModePair::mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * mouseEvent )
{
    if (mDecoratedMode)
        mDecoratedMode->mouseDoubleClickEvent(mouseEvent);
}

void SCgModePair::mouseMoveEvent (QGraphicsSceneMouseEvent * mouseEvent , bool afterSceneEvent)
{
    if(afterSceneEvent)
    {
        if(mDecoratedMode)
            mDecoratedMode->mouseMoveEvent(mouseEvent, afterSceneEvent);
        return;
    }

    if(!afterSceneEvent && mPathItem)
    {
        mouseEvent->accept();
        mPathItem->update(mouseEvent->scenePos());

        SCgVisualObject *begObj = mObjectAtFirstPoint;
        SCgVisualObject *endObj = scene()->scgVisualObjectAt(mouseEvent->scenePos());

        QPen pen = mPathItem->pen();

        Qt::PenStyle s;

        if (endObj != begObj && endObj && begObj && endObj != begObj->parentItem())
            s = Qt::SolidLine;
        else
            s = Qt::DashDotLine;

        if(s != pen.style())
        {
            pen.setStyle(s);
            mPathItem->setPen(pen);
        }
        return;
    }

    if (mDecoratedMode)
        mDecoratedMode->mouseMoveEvent(mouseEvent, afterSceneEvent);
}

void SCgModePair::mousePressEvent ( QGraphicsSceneMouseEvent * mouseEvent, bool afterSceneEvent )
{
    if(afterSceneEvent)
    {
        if(mDecoratedMode)
            mDecoratedMode->mousePressEvent(mouseEvent, afterSceneEvent);
        return;
    }

    if (mPathItem)
    {
        mouseEvent->accept();
        QPointF mousePos = mouseEvent->scenePos();

        if (mouseEvent->button() == Qt::LeftButton)
            mPathItem->pushPoint(mousePos);

        if (mouseEvent->button() == Qt::RightButton)
        {
            mPathItem->popPoint();
            // If there is no more points
            if (mPathItem->points().isEmpty())
                delete mPathItem;
        }
    }

    if (mouseEvent->button() == Qt::LeftButton)
    {
        QPointF mousePos = mouseEvent->scenePos();

        SCgVisualObject *obj = scene()->scgVisualObjectAt(mousePos);
        // if we not create pair yet and press on scg-object, then
        // start pair creation
        if (obj && !mPathItem)
        {
            mouseEvent->accept();
            mObjectAtFirstPoint = obj;

            mPathItem = new SCgPathItem(scene());

            mPathItem->pushPoint(mousePos);
            QPen pen;

            pen.setWidthF(2.f);
            pen.setCapStyle(Qt::RoundCap);
            pen.setStyle(Qt::DashDotLine);

            pen.setColor(Qt::red);
            mPathItem->setPen(pen);
            return;
        }

        if (obj && obj != mObjectAtFirstPoint->parentItem())
        {
            mouseEvent->accept();

            SCgVisualObject *begObj = mObjectAtFirstPoint;
            SCgVisualObject *endObj = obj;

            // do not create lines with equivalent begin end end object
            if (begObj != endObj && begObj)
            {
                SCgContour* c=0;
                // get parent contour
                SCgObject* parent = begObj->baseObject()->parentObject();
                if(parent && parent == endObj->baseObject()->parentObject())
                    if (parent->type() == SCgObject::Contour)
                        c = static_cast<SCgContour*>(parent);

                scene()->pushCommand(new SCgCommandCreatePair(scene(), mPathItem->points(),
                                                                    begObj->baseObject(),
                                                                    endObj->baseObject(), c));
            }

            delete mPathItem;

            return;
        } // if (obj && obj != mObjectAtFirstPoint->parentItem())
    } // if (mouseEvent->button() == Qt::LeftButton)

    mPassMouseReleaseEvent = true;
    if (mDecoratedMode)
        mDecoratedMode->mousePressEvent(mouseEvent, afterSceneEvent);
}

void SCgModePair::mouseReleaseEvent (QGraphicsSceneMouseEvent * mouseEvent , bool afterSceneEvent)
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

void SCgModePair::activate()
{
    if(mDecoratedMode)
        mDecoratedMode->activate();
}


void SCgModePair::deactivate()
{
    if (mPathItem)
        delete mPathItem;
    if(mDecoratedMode)
        mDecoratedMode->deactivate();
}
