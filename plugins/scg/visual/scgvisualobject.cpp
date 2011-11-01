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
#include "scgvisualobject.h"

#include "scgvisualnode.h"
#include "scgvisualpair.h"
#include "scgvisualcontour.h"

#include "scgconfig.h"

#include <QCursor>
#include <QVector2D>
#include <QGraphicsTextItem>
#include <QGraphicsScene>
#include <QApplication>
#include <QPainter>


SCgVisualObject::SCgVisualObject(QGraphicsItem *parent, QGraphicsScene *scene) :
        QGraphicsItem(parent, scene),
        mIsBoundingBoxVisible(false),
        mTextItem(0),
        mParentChanging(false)
{
    mColor = scg_cfg_get_value_color(scg_key_element_color_normal);

    setFlags(QGraphicsItem::ItemIsSelectable
    		| QGraphicsItem::ItemIsFocusable
    		| QGraphicsItem::ItemSendsGeometryChanges);
    setAcceptHoverEvents(true);
}

SCgVisualObject::~SCgVisualObject()
{
    if (mTextItem)  delete mTextItem;
}

bool SCgVisualObject::isSCgVisualObjectType(int type)
{
    return (type >= (int)SCgVisualObject::SCgNodeType && type < (int)SCgVisualObject::SCgNoType);
}

bool SCgVisualObject::isSCgVisualPointObjectType(int type)
{
    return (type > (int)SCgVisualObject::SCgNodeType && type <= (int)SCgVisualObject::SCgContourType);
}

void SCgVisualObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (mIsBoundingBoxVisible)
    {
        QPen pen(QBrush(Qt::red, Qt::SolidPattern), 1.f, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        painter->setPen(pen);

        painter->drawRect(boundingRect());
    }
}

void SCgVisualObject::sync()
{
    if (isNeedSync()) observedObject(0)->_sync();
    mNeedSync = false;
}

QVariant SCgVisualObject::itemChange(GraphicsItemChange change, const QVariant &value)
{
    // item selection changed
    if (change == QGraphicsItem::ItemSelectedHasChanged)
    {
        if (mTextItem != 0)
            mTextItem->setDefaultTextColor(scg_cfg_get_value_color(isSelected() ? scg_key_element_font_color_selected : scg_key_element_font_color_normal));

        mColor = scg_cfg_get_value_color(isSelected() ? scg_key_element_color_selected : scg_key_element_color_normal);
    }

    if (change == QGraphicsItem::ItemPositionHasChanged)
        observedObject(0)->setPosition(value.toPointF());

    // move to correct position automaticly
//    if (change == QGraphicsItem::ItemParentChange && scene())
//    {
//        // we need to set this flag to prevent processing ItemPositionHasChanged,
//        // because item position at this moment not actual
//        mParentChanging = true;
//        QGraphicsItem* newParent = value.value<QGraphicsItem*>();
//        if(newParent)
//            setPos(newParent->mapFromScene(scenePos()));
//        else
//            setPos(scenePos());
//    }

//    if (change == QGraphicsItem::ItemParentHasChanged)
//    {
//        // now item position has valid value
//        mParentChanging = false;
//    }

//    // Change stacking order
//    if (scene() && change == QGraphicsItem::ItemSelectedHasChanged
//                && isSelected() && scene()->selectedItems().size() == 1)
//    {
//        QGraphicsItem* top = this;
//        QList<QGraphicsItem*> lst = scene()->items();
//        foreach(QGraphicsItem* it, lst)
//        {
//            if(it != this &&
//               it->type() == type() &&
//               it->parentItem() == parentItem())
//            {
//                it->stackBefore(top);
//                top = it;
//            }
//        }
//    }


    return QGraphicsItem::itemChange(change, value);
}

void SCgVisualObject::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    if (!isSelected())
    {
        mColor = scg_cfg_get_value_color(scg_key_element_color_highlight);
        if (mTextItem != 0)
            mTextItem->setDefaultTextColor(scg_cfg_get_value_color(scg_key_element_font_color_highlight));
    }

    QGraphicsItem::hoverEnterEvent(event);
}

void SCgVisualObject::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    mColor = scg_cfg_get_value_color(isSelected() ? scg_key_element_color_selected : scg_key_element_color_normal);
    if (mTextItem != 0)
        mTextItem->setDefaultTextColor(scg_cfg_get_value_color(isSelected() ? scg_key_element_font_color_selected : scg_key_element_font_color_normal));

    QGraphicsItem::hoverLeaveEvent(event);
}

void SCgVisualObject::setBoundingBoxVisible(bool value)
{
    mIsBoundingBoxVisible = value;
}

bool SCgVisualObject::isBoundingBoxVisible() const
{
    return mIsBoundingBoxVisible;
}

void SCgVisualObject::_reSync()
{
    SCgObject *object = mObservedObjects.first();

    setPos(object->position());
}

void SCgVisualObject::_needSync()
{
    SCgObjectObserver::_needSync();
    update();
}

void SCgVisualObject::_update(UpdateEventType eventType, SCgObject *object)
{
    if (eventType == PositionChanged)
         setPos(object->position());

    update();
}
