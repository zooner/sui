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
#include "scgcommandcreatecontour.h"

SCgCommandCreateContour::SCgCommandCreateContour(SCgSceneBase *scene,
                                                 const QList<QGraphicsItem *> &childs,
                                                 const QVector<QPointF> &points,
                                                 SCgContour *parentContour,
                                                 QUndoCommand *parent) :
    SCgBaseCommand(scene, 0, parent),
    mPoints(points),
    mChildObjects(childs),
    mParentContour(parentContour)
{
    setText(QObject::tr("Create contour"));
}

SCgCommandCreateContour::~SCgCommandCreateContour()
{
//    if (mObject)
//        delete mObject;
}

void SCgCommandCreateContour::contourDestroyed()
{
    mObject = 0;
}

void SCgCommandCreateContour::redo()
{
    SCgBaseCommand::redo();

    if (mObject == 0)
    {
        SCgContour *contour = mScene->construction()->createContour();
        mObject = contour;

        QPolygonF polygon(mPoints);
        QPointF center = polygon.boundingRect().center();

        contour->setPosition(center);
        QPointF pt;
        foreach (pt, mPoints)
            contour->appendPoint(pt - center);

        connect(mObject, SIGNAL(destroyed()), this, SLOT(contourDestroyed()));
    }else
        mScene->construction()->appendObject(mObject);
}

void SCgCommandCreateContour::undo()
{
    Q_ASSERT_X(mObject != 0,
               "void SCgCommandCreateContour::undo()",
               "Contour doesn't exists");

    mScene->construction()->removeObject(mObject);

    //! TODO: make work with child objects

    SCgBaseCommand::undo();
}
