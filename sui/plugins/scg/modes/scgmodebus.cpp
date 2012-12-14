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
#include "scgmodebus.h"

#include <QApplication>
#include <QVector2D>
#include <QMessageBox>

#include "commands/scgcommandcreatebus.h"

#include "scgpathitem.h"


SCgModeBus::SCgModeBus(SCgInputHandlerInterface* inputHandler, SCgModeInterface* childMode):
            SCgModeInterface(inputHandler, childMode),
            mNode(0),
            mPathItem(0),
            mPassMouseReleaseEvent(false)
{

}

SCgModeBus::~SCgModeBus()
{
    if (mPathItem)
        delete mPathItem;
}

void SCgModeBus::keyPressEvent ( QKeyEvent * keyEvent )
{
    if (mDecoratedMode)
        mDecoratedMode->keyPressEvent(keyEvent);
}

void SCgModeBus::keyReleaseEvent ( QKeyEvent * keyEvent )
{
    if (mDecoratedMode)
        mDecoratedMode->keyReleaseEvent(keyEvent);
}

void SCgModeBus::mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * mouseEvent )
{
    if (mDecoratedMode)
        mDecoratedMode->mouseDoubleClickEvent(mouseEvent);
}

void SCgModeBus::mouseMoveEvent (QGraphicsSceneMouseEvent * mouseEvent , bool afterSceneEvent)
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
        QVector2D vec(mouseEvent->scenePos() - mPathItem->points().last());

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

    if (mDecoratedMode)
        mDecoratedMode->mouseMoveEvent(mouseEvent, afterSceneEvent);
}

void SCgModeBus::mousePressEvent (QGraphicsSceneMouseEvent * mouseEvent , bool afterSceneEvent)
{
    if(afterSceneEvent)
    {
        if(mDecoratedMode)
            mDecoratedMode->mousePressEvent(mouseEvent, afterSceneEvent);
        return;
    }

    mouseEvent->accept();
    QPointF mousePos = mouseEvent->scenePos();

    if (mPathItem && mouseEvent->button() == Qt::LeftButton)
        mPathItem->pushPoint(mousePos);

    // right button
    if (mouseEvent->button() == Qt::RightButton)
    {
        if (mPathItem)
        {
            mPathItem->popPoint();
            // if there is no points
            if (mPathItem->points().empty())
                delete mPathItem;
            return;
        }
    }

    if (mouseEvent->button() == Qt::LeftButton)
    {
        if (!mPathItem)
        {
            SCgVisualObject *obj = scene()->scgVisualObjectAt(mousePos);
            mNode = (obj != 0 && obj->type() == SCgVisualObject::SCgNodeType) ? static_cast<SCgVisualNode*>(obj) : 0;
            if(mNode)
            {
                mPathItem = new SCgPathItem(scene());
                mPathItem->pushPoint(mNode->scenePos());

                QPen pen;

                pen.setColor(Qt::blue);
                pen.setWidthF(5.f);
                pen.setCapStyle(Qt::RoundCap);
                pen.setStyle(Qt::DashDotLine);

                mPathItem->setPen(pen);
                return;
            }

        }else
        {
            QVector<QPointF> points = mPathItem->points();
            // The last point in points is mousePos, so we should get previous
            QVector2D vec(points.at(points.size() - 2) - mousePos);

            Q_ASSERT(mNode && mNode->baseObject() && mNode->baseObject()->type() == SCgObject::Node);
            if (points.size() > 2 && vec.length() < 5.f)
            {
                points.pop_back();

//                SCgVisualContour* contour = 0;
                // get parent contour
//                QGraphicsItem* parent = mNode->parentItem();

//                if (parent && parent->type() == SCgVisualContour::Type)
//                    contour = static_cast<SCgVisualContour*>(parent);

                scene()->pushCommand(new SCgCommandCreateBus(scene(), static_cast<SCgNode*>(mNode->baseObject()),
                                                                   points, 0));
                delete mPathItem;

                return;
            }
        }
    }

    if(mDecoratedMode)
    {
        mDecoratedMode->mousePressEvent(mouseEvent, afterSceneEvent);
        mPassMouseReleaseEvent = true;
    }
}

void SCgModeBus::mouseReleaseEvent (QGraphicsSceneMouseEvent * mouseEvent , bool afterSceneEvent)
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

void SCgModeBus::activate()
{
    if(mDecoratedMode)
        mDecoratedMode->activate();
}


void SCgModeBus::deactivate()
{
    if (mPathItem)
        delete mPathItem;
    if(mDecoratedMode)
        mDecoratedMode->deactivate();
}
