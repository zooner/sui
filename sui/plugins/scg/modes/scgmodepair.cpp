/*
 * scgmodeselect.cpp
 *
 *  Created on: 14.07.2011
 *      Author: ZooNer
 */

#include "scgprecompiled.h"
#include "scgmodepair.h"

#include "commands/scgcommandcreatepair.h"

#include "scgpathitem.h"

SCgModePair::SCgModePair(SCgInputHandlerInterface* inputHandler):
                SCgModeInterface(inputHandler),
                mPathItem(0),
                mObjectAtFirstPoint(0)
{

}

SCgModePair::~SCgModePair()
{
    if (mPathItem)
        delete mPathItem;
}

void SCgModePair::keyPressEvent ( QKeyEvent * keyEvent )
{

}

void SCgModePair::keyReleaseEvent ( QKeyEvent * keyEvent )
{

}

void SCgModePair::mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * mouseEvent )
{

}

void SCgModePair::mouseMoveEvent ( QGraphicsSceneMouseEvent * mouseEvent )
{
    mouseEvent->accept();

    if(mPathItem)
    {
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
    }
}

void SCgModePair::mousePressEvent ( QGraphicsSceneMouseEvent * mouseEvent )
{
    mouseEvent->accept();

    if (mPathItem)
    {
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
            mObjectAtFirstPoint = obj;

            mPathItem = new SCgPathItem(scene());

            //if(mObjectAtFirstPoint->type() == SCgVisualObject::SCgNodeType || mObjectAtFirstPoint->type() == SCgVisualObject::SCgContourType )
            mPathItem->pushPoint(mousePos);//mObjectAtFirstPoint->scenePos());
//            else
//                mPathItem->pushPoint(mObjectAtFirstPoint->cross(mouseEvent->scenePos(), mObjectAtFirstPoint->dotPos(mouseEvent->scenePos()) ));

            QPen pen;

            pen.setWidthF(2.f);
            pen.setCapStyle(Qt::RoundCap);
            pen.setStyle(Qt::DashDotLine);

            pen.setColor(Qt::red);
            mPathItem->setPen(pen);
        }
        else
        if (obj && obj != mObjectAtFirstPoint->parentItem())
        {
            SCgVisualObject *begObj = mObjectAtFirstPoint;
            SCgVisualObject *endObj = obj;

            // do not create lines with equivalent begin end end object
            if (begObj != endObj && begObj)// && !begObj->isDead())
            {
                SCgContour* c=0;
                // get parent contour
//                QGraphicsItem* parent = begObj->parentItem();
//                if(parent && parent == endObj->parentItem())
//                    if (parent->type() == SCgVisualObject::SCgContourType)
//                        c = static_cast<SCgVisualContour*>(parent)->observedObject();


                scene()->appendUndoCommand(new SCgCommandCreatePair(scene(), mPathItem->points(),
                                                                    begObj->observedObject(0),
                                                                    endObj->observedObject(0), c));
            }

            delete mPathItem;
        } // if (obj)
    }
}

void SCgModePair::mouseReleaseEvent ( QGraphicsSceneMouseEvent * mouseEvent )
{

}

void SCgModePair::activate()
{

}


void SCgModePair::deactivate()
{
    if (mPathItem)
        delete mPathItem;
}
