/*
 * SCgLinePathItem.cpp
 *
 *  Created on: 18.07.2011
 *      Author: ZooNer
 */
#include "scgprecompiled.h"
#include "scgpathitem.h"

#include <QGraphicsScene>

SCgPathItem::SCgPathItem(QGraphicsScene* scene, bool closed, QObject* parent):
                                                QObject(parent),
                                                mClosingLine(0),
                                                mIsClosed(closed)
{
    scene->addItem(&mPath);
    scene->addItem(&mLastLine);

    mPath.setZValue(999);
    mLastLine.setZValue(999);

    if(mIsClosed)
    {
        mClosingLine = new QGraphicsLineItem();

        scene->addItem(mClosingLine);
        mClosingLine->setZValue(999);
        mClosingLine->setAcceptedMouseButtons(Qt::NoButton);
    }

    mPath.setCacheMode(QGraphicsItem::DeviceCoordinateCache);

    mLastLine.setAcceptedMouseButtons(Qt::NoButton);
    mPath.setAcceptedMouseButtons(Qt::NoButton);
}

SCgPathItem::~SCgPathItem()
{
    if (mIsClosed)
        delete mClosingLine;
}

void SCgPathItem::clear()
{
    mPoints.clear();
    mPath.setPath(QPainterPath());
}

void SCgPathItem::setPen(const QPen& pen)
{
    mPath.setPen(pen);
    mLastLine.setPen(pen);
    if(mClosingLine)
        mClosingLine->setPen(pen);

    //we need to redraw old path.
    updatePath();
}

void SCgPathItem::updatePath()
{
    QPainterPath path;

    if (mPoints.isEmpty())
    {
        mPath.setPath(QPainterPath());
        return;
    }

    path.moveTo(mPoints.first());
    for (int idx = 1; idx != mPoints.size(); ++idx)
        path.lineTo(mPoints.at(idx));


    //Draw path in parent coordinates
    if (mPath.parentItem())
        path = mPath.parentItem()->mapFromScene(path);

//    mPath->setPen(mPen);
    mPath.setPath(path);
}

void SCgPathItem::updateLastLine(QPointF mousePos)
{
    if (mPoints.isEmpty())
        return;
//    mLastLine.setPen(mPath.pen());
    QPointF last = mPoints.last();

    if(mLastLine.parentItem() != 0)
    {
        last = mLastLine.parentItem()->mapFromScene(last);
        mousePos = mLastLine.parentItem()->mapFromScene(mousePos);
    }

    mLastLine.setLine(QLineF(last, mousePos));

    if (mIsClosed)
    {
        Q_ASSERT(mClosingLine);

        QPointF first = mPoints.first();
        if(mClosingLine->parentItem() != 0)
            first = mClosingLine->parentItem()->mapFromScene(first);
        mClosingLine->setLine(QLineF(first,mousePos));
    }
}

void SCgPathItem::pushPoint(const QPointF& point)
{
    mPoints.append(point);
    updatePath();
    updateLastLine(point);
}

void SCgPathItem::popPoint()
{
    if (mPoints.isEmpty())
        return;

    mPoints.pop_back();
    updatePath();
    updateLastLine(mLastLine.line().p2());
}

void SCgPathItem::update(const QPointF& lastPoint)
{
    updateLastLine(lastPoint);
}
