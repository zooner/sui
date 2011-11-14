/*
 * scgmodeselect.cpp
 *
 *  Created on: 14.07.2011
 *      Author: ZooNer
 */

#include "scgprecompiled.h"
#include "scgmodecontour.h"

#include <QVector2D>


#include "commands/scgcommandcreatecontour.h"

#include "scgpathitem.h"


SCgModeContour::SCgModeContour(SCgInputHandlerInterface* inputHandler):
                SCgModeInterface(inputHandler),
                mPathItem(0),
                mParentContour(0)
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

void SCgModeContour::keyPressEvent ( QKeyEvent * keyEvent )
{

}

void SCgModeContour::keyReleaseEvent ( QKeyEvent * keyEvent )
{

}

void SCgModeContour::mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * mouseEvent )
{

}

void SCgModeContour::mouseMoveEvent ( QGraphicsSceneMouseEvent * mouseEvent )
{
    mouseEvent->accept();

    if(mPathItem)
    {
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
    }
}

void SCgModeContour::mousePressEvent ( QGraphicsSceneMouseEvent * mouseEvent )
{
    mouseEvent->accept();

    if (mouseEvent->button() == Qt::LeftButton)
    {
       QPointF mousePos = mouseEvent->scenePos();

        if (!mPathItem)
        {
//            SCgVisualObject* obj = scene()->scgObjectAt(mousePos);
//            if(obj)
//            {
//                if(obj->type() == SCgVisualObject::SCgContourType)
//                    mParentContour = static_cast<SCgVisualContour*>(obj);
//                else
//                {
//                    QGraphicsItem* it = obj->parentItem();
//                    if (it && it->type() == SCgVisualObject::SCgContourType)
//                        mParentContour = static_cast<SCgVisualContour*>(it);
//                }
//            }

            mPathItem = new SCgPathItem(scene(), true);
            mPathItem->pushPoint(mousePos);

            QPen pen;

            pen.setColor(Qt::green);
            pen.setCapStyle(Qt::RoundCap);
            pen.setStyle(Qt::DashLine);
            pen.setWidthF(2.f);

            mPathItem->setPen(pen);
            return;
        }else
        {
            QVector<QPointF> points = mPathItem->points();
            QVector2D vec(points.at(0) - mousePos);

            if (vec.length() < 5.f && points.size() > 2)
            {
                // get child items
                QList<QGraphicsItem*> childs = selectItemsForContour();

                scene()->appendUndoCommand(new SCgCommandCreateContour(scene(), childs, points, 0));

                mParentContour = 0;
                delete mPathItem;
            }
        }
    }

    QPointF mousePos = mouseEvent->scenePos();
    if (mPathItem && mouseEvent->button() == Qt::LeftButton)
        mPathItem->pushPoint(mousePos);
    // right button
    if (mouseEvent->button() == Qt::RightButton)
    {
        if (mPathItem)
        {
            mPathItem->popPoint();
            if (mPathItem->points().empty())
                delete mPathItem;
        }
    }
}

void SCgModeContour::mouseReleaseEvent ( QGraphicsSceneMouseEvent * mouseEvent )
{

}


void SCgModeContour::activate()
{

}


void SCgModeContour::deactivate()
{
    if (mPathItem)
        delete mPathItem;
}
