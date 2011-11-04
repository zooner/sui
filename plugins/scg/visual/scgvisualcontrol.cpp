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
#if ENABLE_VISUAL_EFFECTS_SUPPORT
#include <QGraphicsDropShadowEffect>
#endif

SCgVisualControl::SCgVisualControl(QGraphicsItem *parent, QGraphicsScene *scene) :
    SCgVisualObject(parent, scene)
{
    mBackColor = scg_cfg_get_value_color(scg_key_control_backcolor_normal);

    setFlag(QGraphicsItem::ItemIsMovable, true);

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
    QPointF size = observedObject(0)->size();
    return QRectF(-size.x() / 2.f, -size.y() / 2.f, size.x(), size.y());
}

void SCgVisualControl::updatePosition()
{

}

void SCgVisualControl::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //SCgAlphabet::paintControl(painter, this);

    // synchronize with sc.g-object
    sync();

    QRectF bound = boundingRect().adjusted(2, 2, -2, -2);

    // draw shape
    QPen pen = QPen(QBrush(mColor, Qt::SolidPattern), 2, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin);
    QBrush brush = QBrush(QColor(255, 255, 255, 224), Qt::SolidPattern);

    painter->setPen(pen);
    painter->setBrush(brush);

    painter->drawRoundRect(bound, 35, 35);
}

void SCgVisualControl::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    if (!isSelected())
        mBackColor = scg_cfg_get_value_color(scg_key_control_backcolor_highlight);

    SCgVisualObject::hoverEnterEvent(event);
}

void SCgVisualControl::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    mBackColor = scg_cfg_get_value_color(isSelected() ? scg_key_control_backcolor_selected : scg_key_control_backcolor_normal);

    SCgVisualObject::hoverLeaveEvent(event);
}

QVariant SCgVisualControl::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemSelectedHasChanged)
        mBackColor = scg_cfg_get_value_color(isSelected() ? scg_key_control_backcolor_selected : scg_key_control_backcolor_normal);

    return SCgVisualObject::itemChange(change, value);
}

QPainterPath SCgVisualControl::shape() const
{
    //prepareGeometryChange();
    QPainterPath path;
    path.addRect(boundingRect());

    return path;
}

void SCgVisualControl::_update(SCgObjectObserver::UpdateEventType eventType, SCgObject *object)
{
    if (eventType == SCgObjectObserver::IdentifierChanged)
    {
        SCgVisualObject::_update(eventType, object);
        if (mTextItem != 0)
        {
            QRectF textBound = mTextItem->boundingRect();
            observedObject(0)->setSize(QPointF(textBound.width() + 10, textBound.height() + 10));
            mTextItem->setPos(-textBound.width() / 2.f, -textBound.height() / 2.f);
        }
        return;
    }

    SCgVisualObject::_update(eventType, object);
}
