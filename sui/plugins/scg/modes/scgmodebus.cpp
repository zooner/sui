/*
 * scgmodeselect.cpp
 *
 *  Created on: 14.07.2011
 *      Author: ZooNer
 */

#include "scgprecompiled.h"
#include "scgmodebus.h"

#include <QApplication>
#include <QVector2D>
#include <QMessageBox>

#include "commands/scgcommandcreatebus.h"

#include "scgpathitem.h"


SCgModeBus::SCgModeBus(SCgInputHandlerInterface* inputHandler):
            SCgModeInterface(inputHandler),
            mNode(0),
            mPathItem(0)
{

}

SCgModeBus::~SCgModeBus()
{
    if (mPathItem)
        delete mPathItem;
}

void SCgModeBus::keyPressEvent ( QKeyEvent * keyEvent )
{

}

void SCgModeBus::keyReleaseEvent ( QKeyEvent * keyEvent )
{

}

void SCgModeBus::mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * mouseEvent )
{

}

void SCgModeBus::mouseMoveEvent ( QGraphicsSceneMouseEvent * mouseEvent )
{
    mouseEvent->accept();

    if(mPathItem)
    {
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
    }
}

void SCgModeBus::mousePressEvent ( QGraphicsSceneMouseEvent * mouseEvent )
{
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
        }
    }

    if (mouseEvent->button() == Qt::LeftButton)
    {
        if (!mPathItem)
        {
            SCgVisualObject *obj = scene()->scgVisualObjectAt(mousePos);
            mNode = (obj != 0 && obj->type() == SCgVisualObject::SCgNodeType) ? static_cast<SCgVisualNode*>(obj) : 0;

//            if (mNode != 0 && mNode->bus())
//                QMessageBox::information(0, qAppName(), QObject::tr("Node can't have more than one bus!"));
//            else
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
                }


        }else
        {
            QVector<QPointF> points = mPathItem->points();
            // The last point in points is mousePos, so we should get previous
            QVector2D vec(points.at(points.size() - 2) - mousePos);

            Q_ASSERT(mNode);
            if (points.size() > 2 && vec.length() < 5.f)
            {
                points.pop_back();

//                SCgVisualContour* contour = 0;
                // get parent contour
//                QGraphicsItem* parent = mNode->parentItem();

//                if (parent && parent->type() == SCgVisualContour::Type)
//                    contour = static_cast<SCgVisualContour*>(parent);

                scene()->appendUndoCommand(new SCgCommandCreateBus(scene(), qobject_cast<SCgNode*>(mNode->observedObject(0)),
                                                                   points, 0));
                delete mPathItem;
            }
        }
    }
}

void SCgModeBus::mouseReleaseEvent ( QGraphicsSceneMouseEvent * mouseEvent )
{

}

void SCgModeBus::activate()
{

}


void SCgModeBus::deactivate()
{
    if (mPathItem)
        delete mPathItem;
}
