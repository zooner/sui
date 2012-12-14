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
#include "scgvisualcontrol.h"
#include "scgconfig.h"

#include <QPainter>
#include <QVector2D>
#include <QGraphicsSceneMouseEvent>
#if ENABLE_VISUAL_EFFECTS_SUPPORT
#include <QGraphicsDropShadowEffect>
#endif

#define DRAG_MIN_LENGTH 5.f

SCgVisualControl::SCgVisualControl(QGraphicsScene *scene) :
    SCgVisualObject(scene),
    mDragLength(-1.f)
{
    mBackColor = scg_cfg_get_value_color(scg_key_control_backcolor_normal);
    mColor = scg_cfg_get_value_color(scg_key_control_color_normal);

#if ENABLE_VISUAL_EFFECTS_SUPPORT
    if (scg_cfg_get_value_uint(scg_key_effects_enabled) != 0)
    {
        QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect(this);
        effect->setOffset(3, 3);
        setGraphicsEffect(effect);
    }
#endif
}

SCgVisualControl::~SCgVisualControl()
{
}

QRectF SCgVisualControl::boundingRect() const
{
    QSizeF size = baseObject()->size();
    return QRectF(-size.width() / 2.f, -size.height() / 2.f, size.width(), size.height());
}

void SCgVisualControl::updatePosition()
{

}

void SCgVisualControl::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    //SCgAlphabet::paintControl(painter, this);
    QRectF bound = boundingRect().adjusted(2, 2, -2, -2);

    // draw shape
    QPen pen = QPen(QBrush(mColor, Qt::SolidPattern), 2, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin);
    QBrush brush = QBrush(mBackColor, Qt::SolidPattern);

    painter->setPen(pen);
    painter->setBrush(brush);

    painter->drawRect(bound);
}

void SCgVisualControl::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    if (!isSelected() && mTextItem)
    {
        mBackColor = scg_cfg_get_value_color(scg_key_control_backcolor_highlight);
        mColor = scg_cfg_get_value_color(scg_key_control_color_highlight);
        mTextItem->setDefaultTextColor(scg_cfg_get_value_color(scg_key_control_font_color));
    }

    QGraphicsItem::hoverEnterEvent(event);
}

void SCgVisualControl::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    mBackColor = scg_cfg_get_value_color(isSelected() ? scg_key_control_backcolor_selected : scg_key_control_backcolor_normal);
    mColor = scg_cfg_get_value_color(isSelected() ? scg_key_control_color_selected : scg_key_control_color_normal);
    mTextItem->setDefaultTextColor(scg_cfg_get_value_color(scg_key_control_font_color));

    QGraphicsItem::hoverLeaveEvent(event);
}

QVariant SCgVisualControl::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemSelectedHasChanged)
    {
        mBackColor = scg_cfg_get_value_color(isSelected() ? scg_key_control_backcolor_selected : scg_key_control_backcolor_normal);
        mColor = scg_cfg_get_value_color(isSelected() ? scg_key_control_color_selected : scg_key_control_color_normal);
        mTextItem->setDefaultTextColor(scg_cfg_get_value_color(scg_key_control_font_color));

        return QVariant();
    }

    return SCgVisualObject::itemChange(change, value);
}

QPainterPath SCgVisualControl::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());

    return path;
}

void SCgVisualControl::_update(SCgObjectObserver::UpdateEventType eventType, SCgObject *object)
{
    if (eventType == SCgObjectObserver::IdentifierChanged)
    {
        if (mTextItem == 0)
        {
            QFont font(scg_cfg_get_value_string(scg_key_control_font_name),
                       scg_cfg_get_value_uint(scg_key_control_font_size),
                       10, false);
            font.setBold(true);
            //font.setItalic(true);

            mTextItem = new QGraphicsTextItem(this);
            mTextItem->setFont(font);
            mTextItem->setDefaultTextColor(scg_cfg_get_value_color(scg_key_control_font_color));
        }

        mTextItem->setPlainText(object->identifier());
        QRectF textBound = mTextItem->boundingRect();
        baseObject()->setSize(QSizeF(textBound.width() + 10, textBound.height() + 10));
        mTextItem->setPos(-textBound.width() / 2.f, -textBound.height() / 2.f);

        return;
    }

    SCgVisualObject::_update(eventType, object);
}

void SCgVisualControl::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    mDragLength = 0.f;
    mLastDragPos = event->pos();

    SCgVisualObject::mousePressEvent(event);
}

void SCgVisualControl::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && mDragLength < DRAG_MIN_LENGTH)
    {
        SCgControl *control = observedObjectT<SCgControl>(0);
        Q_ASSERT(control != 0);

        control->initiated();
    }

    mDragLength = -1.f;

    SCgVisualObject::mouseReleaseEvent(event);
}

void SCgVisualControl::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (mDragLength >= 0)
    {
        QVector2D v(event->pos() - mLastDragPos);
        mLastDragPos = event->pos();

        mDragLength += v.length();
    }

    SCgVisualObject::mouseMoveEvent(event);
}
