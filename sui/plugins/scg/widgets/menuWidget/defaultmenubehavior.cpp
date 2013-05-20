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

#include "defaultmenubehavior.h"
#include "sunmenuIiemview.h"
#include "sunmenulayer.h"
#include "sunmenurepresentation.h"
#include "sizableItems/abstractsizableitem.h"

#include <QPropertyAnimation>

DefaultMenuBehavior::DefaultMenuBehavior(SunMenuRepresentation* parentMenu,
                                         qint32 minRadius, qint32 maxRadius, qint32 defaultRadius) :
    mMaxRadius(maxRadius), mMinWidth(minRadius),
    mDefaultWidth(defaultRadius), mRepresentation(parentMenu),
    mItemViewClicked(0), mItemUnderMouse(0)
{
    if (mRepresentation)
    {
        mRepresentation->setBehavior(this);
        SunMenuLayer* l = mRepresentation->parentLayer();
        if (l)
            l->setWidth(mDefaultWidth);
    }
}

DefaultMenuBehavior::~DefaultMenuBehavior()
{
    if (mRepresentation)
        mRepresentation->setBehavior(0);

    if (mCurrentAnimation)
        delete mCurrentAnimation;
}

QPropertyAnimation* DefaultMenuBehavior::createAnimation(QObject* target,
                                                         const QVariant& endValue, const char* property /* = "width"*/) const
{
    QPropertyAnimation *animation = new QPropertyAnimation(target, property);
    animation->setDuration(600);
    animation->setEndValue(endValue);
    animation->setEasingCurve(QEasingCurve::OutCubic);

    return animation;
}

QPropertyAnimation* DefaultMenuBehavior::createAnimation(QObject* target,
                                                         const QVariant& startValue, const QVariant& endValue,
                                                         const char* property /* = "width"*/) const
{
    QPropertyAnimation *animation = new QPropertyAnimation(target, property);
    animation->setDuration(600);
    animation->setStartValue(startValue);
    animation->setEndValue(endValue);
    animation->setEasingCurve(QEasingCurve::OutCubic);

    return animation;
}

void DefaultMenuBehavior::focusInEvent(SunMenuItemView* eventReciever,
                                       QFocusEvent* event)
{
    Q_UNUSED(eventReciever);
    Q_UNUSED(event);
}

void DefaultMenuBehavior::focusOutEvent(SunMenuItemView* eventReciever,
                                        QFocusEvent* event)
{
    Q_UNUSED(eventReciever);
    Q_UNUSED(event);
}

void DefaultMenuBehavior::hoverEnterEvent(SunMenuItemView* eventReciever,
                                          QGraphicsSceneHoverEvent* event)
{
    Q_UNUSED(eventReciever);
    Q_UNUSED(event);
}

void DefaultMenuBehavior::hoverLeaveEvent(SunMenuItemView* eventReciever,
                                          QGraphicsSceneHoverEvent* event)
{
    mItemUnderMouse = 0;

    QList<QGraphicsItem*> underMouse = eventReciever->scene()->items(event->scenePos());
    bool isMenuItemUnderMouse = false;
    foreach (QGraphicsItem* i, underMouse)
    {
        if(i->type() == SunMenuItemView::Type)
        {
            isMenuItemUnderMouse = true;
            break;
        }
    }

    // mouse has left the menu
    if (!isMenuItemUnderMouse && eventReciever->parentLayer() == mRepresentation->parentLayer())
    {
        if (mCurrentAnimation)
            delete mCurrentAnimation;

        QParallelAnimationGroup* gr = new QParallelAnimationGroup();
        foreach(SunMenuLayer* lay, mRepresentation->layers())
            gr->addAnimation(createAnimation(lay, mDefaultWidth));
        mCurrentAnimation = gr;

        mCurrentAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    }
}

AnimationDefinitionsAndConstraints DefaultMenuBehavior::getAnimationDefinitionsAndConstraints(SunMenuItemView* focusedItem)
{
    qint32 maxPrefferedWidth = defaultWidth() * 1.5;
    qint32 maxPrefferedHeight = 0;
    qreal sweepTmp = 90;
    SunMenuLayer* layer = focusedItem->parentLayer();

    foreach(SunMenuItemView* mc, layer->childMenuItems())
    {
        QSize prefferedSize = mc->displayedItem()->prefferedSize();
        if (prefferedSize.width() > maxPrefferedWidth)
            maxPrefferedWidth = prefferedSize.width();

        if (prefferedSize.height() > maxPrefferedHeight)
            maxPrefferedHeight = prefferedSize.height();

        if (mc->sweepLength() < sweepTmp)
            sweepTmp = mc->sweepLength();
    }

    //if(mLayerUnderMouse == mRepresentation->parentLayer())
    //    maxPrefferedWidth /= 2;

    if (sweepTmp < 90)
    {
        maxPrefferedHeight /= 1.6;
        qint32 tmp = maxPrefferedHeight
                / (qSin((M_PI / 180) * sweepTmp / 2))
                - focusedItem->innerRadius();

        if (tmp > maxPrefferedWidth)
            maxPrefferedWidth = tmp;
    }

    qint32 visibletreeHeight = representation()->treeHeight();

    if (maxRadius() < maxPrefferedWidth)
        maxPrefferedWidth = maxRadius();

    qint32 widthForOthers = (maxRadius() - maxPrefferedWidth) / visibletreeHeight;
    if (widthForOthers < minWidth())
    {
        maxPrefferedWidth = maxRadius() - minWidth() * visibletreeHeight;
        widthForOthers = minWidth();
    }
    else
    {
        qreal scale = defaultWidth() / widthForOthers;
        if (scale < 2.2)
            scale = 2.2;

        widthForOthers = defaultWidth() / scale;
    }

    qint32 outerRadius = focusedItem->outerRadius();

    bool fixOuter = (focusedItem->depthLevel() * widthForOthers
                     + maxPrefferedWidth) < outerRadius;

    if (fixOuter)
        maxPrefferedWidth = outerRadius
                - focusedItem->depthLevel() * widthForOthers;

    AnimationDefinitionsAndConstraints retVal;
    retVal.isOuterRadiusNeedToBeFixed = fixOuter;
    retVal.maxPrefferedWidthForFocusedLayer = maxPrefferedWidth;
    retVal.widthForNotFocusedLayers = widthForOthers;
    return retVal;
}

void DefaultMenuBehavior::hoverMoveEvent(SunMenuItemView* eventReciever,
                                         QGraphicsSceneHoverEvent* event)
{
    Q_UNUSED(event);

    if (mItemUnderMouse != eventReciever)
    {
        if (mCurrentAnimation)
            delete mCurrentAnimation;

        mItemUnderMouse = eventReciever;

        AnimationDefinitionsAndConstraints constraints = getAnimationDefinitionsAndConstraints(eventReciever);

        SunMenuLayer* nextLayer = eventReciever->childMenus().isEmpty()
                                  ? 0
                                  : eventReciever->childMenus().first()->parentLayer();

        QParallelAnimationGroup* gr = new QParallelAnimationGroup();
        foreach(SunMenuLayer* lay, mRepresentation->layers())
        {
            lay->setConstantParameter(SunMenuLayer::ConstantWidth);

            if (lay == mItemUnderMouse->parentLayer())
            {
                if(constraints.isOuterRadiusNeedToBeFixed)
                    lay->setConstantParameter(SunMenuLayer::ConstantOuterRadius);
                else
                    gr->addAnimation(createAnimation(lay, constraints.maxPrefferedWidthForFocusedLayer));
            }
            else if(lay == nextLayer)
            {
                gr->addAnimation(createAnimation(lay, constraints.widthForNotFocusedLayers * 2));
            }
            else
            {
                gr->addAnimation(createAnimation(lay, constraints.widthForNotFocusedLayers));
            }
        }

        mCurrentAnimation = gr;
        mCurrentAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    }
}

void DefaultMenuBehavior::keyPressEvent(SunMenuItemView* eventReciever,
                                        QKeyEvent* event)
{
    Q_UNUSED(eventReciever);
    Q_UNUSED(event);
}

void DefaultMenuBehavior::keyReleaseEvent(SunMenuItemView* eventReciever,
                                          QKeyEvent* event)
{
    Q_UNUSED(eventReciever);
    Q_UNUSED(event);
}

void DefaultMenuBehavior::mouseDoubleClickEvent(SunMenuItemView* eventReciever,
                                                QGraphicsSceneMouseEvent* event)
{
    Q_UNUSED(eventReciever);
    Q_UNUSED(event);
}

void DefaultMenuBehavior::mouseMoveEvent(SunMenuItemView* eventReciever,
                                         QGraphicsSceneMouseEvent* event)
{
    Q_UNUSED(eventReciever);
    Q_UNUSED(event);
}

void DefaultMenuBehavior::mousePressEvent(SunMenuItemView* eventReciever,
                                          QGraphicsSceneMouseEvent* event)
{
    Q_UNUSED(event);

    mItemViewClicked = eventReciever;
}

void DefaultMenuBehavior::mouseReleaseEvent(SunMenuItemView* eventReciever,
                                            QGraphicsSceneMouseEvent* event)
{
    Q_UNUSED(event);

    if (mItemViewClicked == eventReciever)
    {
        Q_ASSERT(eventReciever);
        eventReciever->trigger();

        SunMenuLayer* subLayer = eventReciever->subLayer();
        if (subLayer)
        {
            if (mCurrentAnimation)
                delete mCurrentAnimation;

            if (subLayer->isVisible() && !subLayer->isFolding())
            {
                foreach (SunMenuItemView* c, subLayer->childMenuItems())
                {
                    c->hideSublayer();
                }
                QPropertyAnimation* a = createAnimation(subLayer, 0);
                a->connect(a, SIGNAL(finished()), eventReciever, SLOT(hideSublayer()));
                a->start(QAbstractAnimation::DeleteWhenStopped);
                // DO NOT SET mCurrentAnimation HERE as the animation must be done anyway
                //mCurrentAnimation = a;
                subLayer->setFolding(true);
            }
            else
            {
                AnimationDefinitionsAndConstraints cs = getAnimationDefinitionsAndConstraints(eventReciever);
                QPropertyAnimation* a = createAnimation(subLayer, 0, cs.widthForNotFocusedLayers*2);
                a->start(QAbstractAnimation::DeleteWhenStopped);
                eventReciever->showSublayer();
                mCurrentAnimation = a;
                subLayer->setFolding(false);
            }
        }
    }
}

int DefaultMenuBehavior::maxMenuRadius() const
{
    return maxRadius();
}

void DefaultMenuBehavior::reset()
{
    if(mCurrentAnimation)
        delete mCurrentAnimation;

    mItemViewClicked = mItemUnderMouse = NULL;

    foreach (SunMenuItemView* item, mRepresentation->representedMenus())
    {
        item->hideSublayer();
    }

    foreach(SunMenuLayer* lay, mRepresentation->layers())
        lay->setWidth(mDefaultWidth);
}

qint32 DefaultMenuBehavior::defaultWidth() const
{
    return mDefaultWidth;
}

qint32 DefaultMenuBehavior::maxRadius() const
{
    return mMaxRadius;
}

qint32 DefaultMenuBehavior::minWidth() const
{
    return mMinWidth;
}

SunMenuRepresentation* DefaultMenuBehavior::representation() const
{
    return mRepresentation;
}

void DefaultMenuBehavior::setDefaultRadius(qint32 value)
{
    if (mDefaultWidth == value)
        return;

    mDefaultWidth = value;
}

void DefaultMenuBehavior::setMinRadius(qint32 value)
{
    if (mMinWidth == value)
        return;

    mMinWidth = value;
}

void DefaultMenuBehavior::setMaxRadius(qint32 value)
{
    if (mMaxRadius == value)
        return;

    mMaxRadius = value;
}
