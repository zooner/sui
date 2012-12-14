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

    Q_ASSERT(!mObjectToVisual.contains(scg_object));

    // create visual object. looks strange (this, this) but may be some time CommandStackControllerInterface
    // will be implemented in separate class
    SCgVisualObject *vobject = SCgVisualObject::createVisual(scg_object, this);
    if(!vobject)
    {
        SuiExcept(SuiExceptionInternalError,
                  "Unsupported sc.g-object type",
                  "void SCgSceneBase::_processEventObjectCreated(QObject *object)");
    }

    mObjectToVisual[scg_object] = vobject;
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
    return object ? object->baseObject() : 0;
}

SCgVisualObject* SCgMainWindowScene::scgVisualObjectAt(const QPointF &point) const
{
    QList<QGraphicsItem*> itemList = items(point, Qt::IntersectsItemShape, Qt::DescendingOrder);

    foreach(QGraphicsItem* it, itemList)
        if (SCgVisualObject::isSCgVisualObjectType(it->type()))
            return static_cast<SCgVisualObject*>(it);

    return 0;
}
