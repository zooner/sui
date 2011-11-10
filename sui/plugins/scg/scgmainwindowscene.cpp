/*
-----------------------------------------------------------------------------
This source file is part of OSTIS (Open Semantic Technology for Intelligent Systems)
For the latest info, see http://www.ostis.net

Copyright (c) 2011 OSTIS

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
#include "scgmainwindowscene.h"

SCgMainWindowScene::SCgMainWindowScene(SCgInputHandlerInterface *inputHandler, QObject *parent) :
    SCgSceneBase(inputHandler, parent)
{
}

SCgMainWindowScene::~SCgMainWindowScene()
{
}

void SCgMainWindowScene::_update(SCgConstructionObserver::UpdateEventType eventType, QObject *object)
{
    switch (eventType)
    {
    case SCgConstructionObserver::ObjectCreated:
    case SCgConstructionObserver::ObjectAppended:
        _processEventObjectCreated(object);
        break;
    case SCgConstructionObserver::ObjectDeleted:
    case SCgConstructionObserver::ObjectRemoved:
        _processEventObjectDeleted(object);
        break;
    default:
        SuiExcept(SuiExceptionInternalError,
                  QString("Not supported event: %1").arg(eventType),
                  "void SCgSceneBase::_update(SCgConstructionObserver::UpdateEventType eventType, QObject *object)");
        break;
    }
}

void SCgMainWindowScene::_processEventObjectCreated(QObject *object)
{
    // trying to cast it to construction
    SCgConstruction *construction = qobject_cast<SCgConstruction*>(object);
    if (construction != 0)
    {
        construction->attachObserver(this);
        return;
    }

    // try to cast to sc.g-object
    SCgObject *scg_object = qobject_cast<SCgObject*>(object);
    if (scg_object == 0)  SuiExcept(SuiExceptionInvalidParameters,
                                    "Unsupported object type",
                                    "void SCgSceneBase::_processEventObjectCreated(QObject *object)");

    Q_ASSERT(mObjectToVisual.find(scg_object) == mObjectToVisual.end());

    // create visual object
    SCgVisualObject *vobject = 0;
    //! TODO: add typee function to sc.g-objects and replace qobject_cast with it
    if (qobject_cast<SCgNode*>(object) != 0)
        vobject = new SCgVisualNode(0, this);
    if (qobject_cast<SCgPair*>(object) != 0)
        vobject = new SCgVisualPair(0, this);
    if (qobject_cast<SCgContour*>(object) != 0)
        vobject = new SCgVisualContour(0, this);
    if (qobject_cast<SCgBus*>(object) != 0)
        vobject = new SCgVisualBus(0, this);
    if (qobject_cast<SCgControl*>(object))
        vobject = new SCgVisualControl(0, this);

    if (vobject == 0) SuiExcept(SuiExceptionInternalError,
                                "Unsupported sc.g-object type",
                                "void SCgSceneBase::_processEventObjectCreated(QObject *object)");

    scg_object->attachObserver(vobject);
    mObjectToVisual[scg_object] = vobject;
    vobject->_reSync();
}

void SCgMainWindowScene::_processEventObjectDeleted(QObject *object)
{
    // trying to cat to construction
    SCgConstruction *construction = qobject_cast<SCgConstruction*>(object);
    if (construction != 0)
    {
        construction->detachObserver(this);
        return;
    }

    // try to cast to sc.g-object
    SCgObject *scg_object = qobject_cast<SCgObject*>(object);
    if (scg_object == 0)    SuiExcept(SuiExceptionInvalidParameters,
                                      "Unsupported object type",
                                      "void SCgSceneBase::_processEventObjectDeleted(QObject *object)");

    QMap<SCgObject*, SCgVisualObject*>::iterator it = mObjectToVisual.find(scg_object);
    Q_ASSERT(it != mObjectToVisual.end());

    // delete visual object
    delete it.value();
    mObjectToVisual.remove(scg_object);
}

SCgObject* SCgMainWindowScene::scgObjectAt(const QPointF &point) const
{
    SCgVisualObject *object = scgVisualObjectAt(point);
    if (object != 0) return object->observedObject(0);
    return 0;
}

SCgVisualObject* SCgMainWindowScene::scgVisualObjectAt(const QPointF &point) const
{
    QList<QGraphicsItem*> itemList = items(point, Qt::IntersectsItemShape, Qt::DescendingOrder);

    foreach(QGraphicsItem* it, itemList)
        if (SCgVisualObject::isSCgVisualObjectType(it->type()))
            return static_cast<SCgVisualObject*>(it);

    return 0;
}
