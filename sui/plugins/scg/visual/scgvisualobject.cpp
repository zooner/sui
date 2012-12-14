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

#include "interfaces/commandstackcontrollerinterface.h"

#include <QCursor>
#include <QVector2D>
#include <QGraphicsTextItem>
#include <QGraphicsScene>
#include <QGraphicsSceneEvent>
#include <QApplication>
#include <QPainter>


SCgVisualObject::SCgVisualObject(QGraphicsScene *scene) :
        QGraphicsItem(0, scene),
        mIsBoundingBoxVisible(false),
        mTextItem(0),
        mParentChanging(false),
        mBaseObject(0)
{
    mColor = scg_cfg_get_value_color(scg_key_element_color_normal);

    setFlags(QGraphicsItem::ItemIsSelectable
            | QGraphicsItem::ItemIsFocusable
            | QGraphicsItem::ItemSendsGeometryChanges);
    //Do not set this flag. All position and geometry manipulations are hand made.
    setFlag(QGraphicsItem::ItemIsMovable, false);
    setAcceptHoverEvents(true);
}

SCgVisualObject *SCgVisualObject::createVisual(SCgObject* base,
                                               QGraphicsScene *scene)
{
    Q_ASSERT(base);

    SCgVisualObject* obj = 0;
    switch(base->type())
    {
    case SCgObject::Node:
        obj = new SCgVisualNode(scene);
        break;
    case SCgObject::Bus:
        obj = new SCgVisualBus(scene);
        break;
    case SCgObject::Pair:
        obj = new SCgVisualPair(scene);
        break;
    case SCgObject::Contour:
        obj = new SCgVisualContour(scene);
        break;
    case SCgObject::Control:
        obj = new SCgVisualControl(scene);
        break;
    }

    obj->setBaseObject(base);
    return obj;
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
    Q_UNUSED(option);
    Q_UNUSED(widget);

    if (mIsBoundingBoxVisible)
    {
        QPen pen(QBrush(Qt::red, Qt::SolidPattern), 1.f, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        painter->setPen(pen);

        painter->drawRect(boundingRect());
    }
}

void SCgVisualObject::_onBaseObjectChanged()
{
    setPos(mBaseObject->position());
}

//void SCgVisualObject::sync()
//{
//    if (isNeedSync()) mBaseObject->notifyObservers();
//    mNeedSync = false;
//}

QVariant SCgVisualObject::itemChange(GraphicsItemChange change, const QVariant &value)
{
    // item selection changed
    if (change == QGraphicsItem::ItemSelectedHasChanged)
    {
        if (mTextItem != 0)
            mTextItem->setDefaultTextColor(scg_cfg_get_value_color(isSelected() ? scg_key_element_font_color_selected : scg_key_element_font_color_normal));

        mColor = scg_cfg_get_value_color(isSelected() ? scg_key_element_color_selected : scg_key_element_color_normal);
    }

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

void SCgVisualObject::setBaseObject(SCgObject *object)
{
    if(mBaseObject)
        mBaseObject->detachObserver(this);

    mBaseObject = object;

    if(mBaseObject)
        mBaseObject->attachObserver(this);

    _onBaseObjectChanged();
}

//void SCgVisualObject::_needSync()
//{
//    SCgObjectObserver::_needSync();
//    update();
//}

void SCgVisualObject::_update(UpdateEventType eventType, SCgObject *object)
{
    switch (eventType)
    {
    case PositionChanged:
    {
        setPos(mapToParent(mapFromScene(object->position())));
        break;
    }
    case IdentifierChanged:
    {
        if (mTextItem == 0)
        {
            QFont font("Times New Roman [Arial]", 10, 10, false);
            font.setBold(true);
            font.setItalic(true);

            mTextItem = new QGraphicsTextItem(this);
            mTextItem->setFont(font);
        }

        mTextItem->setPlainText(object->identifier());
        break;
    }
    case ParentChanged:
    {
        //! \todo implement
        break;
    }
    }

    update();
}
