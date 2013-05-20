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

#include "sunmenuIiemview.h"
#include "sunmenulayer.h"
#include "menuitemmodel.h"
#include "sunmenurepresentation.h"
#include "abstractmenubehavior.h"

#include <qmath.h>
#include <QGraphicsPathItem>
#include <QAction>

SunMenuItemView::SunMenuItemView(SunMenuLayer* parentLayer,
                                   MenuItemModel* itemModel, SunMenuItemView* parent) :
    mItemModel(itemModel), mParentLayer(parentLayer), mParentItemView(parent)
{
    initialize();
}

SunMenuItemView::~SunMenuItemView()
{

}

void SunMenuItemView::initialize()
{
    Q_ASSERT_X(mItemModel != 0 && mItemModel->displayedItem() != 0,
               "MenuItemView::initialize()",
               "You should pass a valid MenuItemModel pointer");

    Q_ASSERT_X(mParentLayer != 0, "MenuItemView::initialize()",
               "Parent layer for item MUST be specified.");

    connect(representation(),SIGNAL(brushChanged(const QBrush&)), this, SLOT(updateBrush(const QBrush&)));
    updateBrush(representation()->brush());

    setAcceptHoverEvents(true);
    setParent(mItemModel);
    setParentItem(mParentItemView);

    // Cache useless in this situation because we don't use transformation and menu doesn't change it's position.
    //It's increases memory usage and greatly reduces the animation performance.
    setCacheMode(QGraphicsItem::NoCache);
    //	setFlag(QGraphicsItem::ItemStacksBehindParent, true);

    if (mItemModel->displayedItem()->graphicsItem())
        mItemModel->displayedItem()->graphicsItem()->setParentItem(this);

    connect(mItemModel, SIGNAL(childAdded(MenuItemModel*)), this,
            SLOT(childItemAdded(MenuItemModel*)));

    mSubLayer = 0;

    mStartAngle = 0;
    mSweepLength = 0;
    mWidth = 0;
    mInnerRadius = 0;

    if (!mItemModel->childMenus().isEmpty())
    {
        foreach(MenuItemModel* mc, mItemModel->childMenus())
            addChildItem(mc);
    }

    updateShape();
    recalculateChildMenusAngles();
}

AbstractMenuBehavior* SunMenuItemView::behavior() const
{
    return representation()->behavior();
}

void SunMenuItemView::createSubLayer()
{
    Q_ASSERT_X(mSubLayer == 0, "SunMenuItemView::createSubLayer()",
               "Sub layer mustn't be initialized");

    mSubLayer = new SunMenuLayer(mParentLayer->representation(), this);
    mSubLayer->hide();
}

void SunMenuItemView::childItemAdded(MenuItemModel* newMenu)
{
    MenuItemModel* parent = static_cast<MenuItemModel*>(sender());
    Q_ASSERT(parent == mItemModel);

    addChildItem(newMenu);

    recalculateChildMenusAngles();
}

void SunMenuItemView::updateBrush(const QBrush &brush)
{
    setBrush(brush);
}

void SunMenuItemView::addChildItem(MenuItemModel* newMenu)
{
    if (!mSubLayer)
        createSubLayer();

    mSubLayer->addMenuItem(newMenu);
}

SunMenuRepresentation* SunMenuItemView::representation() const
{
    return mParentLayer->representation();
}

qreal SunMenuItemView::startAngle() const
{
    return mStartAngle;
}

qreal SunMenuItemView::sweepLength() const
{
    return mSweepLength;
}

void SunMenuItemView::setStartAngle(qreal value)
{
    if (qAbs(mStartAngle - value) < 0.0001)
        return;

    mStartAngle = value;
    recalculateChildMenusAngles();
    updateShape();
}

void SunMenuItemView::setSweepLength(qreal value)
{
    if (qAbs(mSweepLength - value) < 0.0001)
        return;

    mSweepLength = value;
    recalculateChildMenusAngles();
    updateShape();
}

void SunMenuItemView::setInnerRadius(qint32 value)
{
    if (mInnerRadius == value)
        return;

    if (constantParameter() != SunMenuLayer::ConstantWidth)
        mWidth += (mInnerRadius - value);

    mInnerRadius = value;

    updateShape();

    if (mSubLayer)
        mSubLayer->setInnerRadius(mInnerRadius + mWidth);
}

void SunMenuItemView::setWidth(qint32 value)
{
    if (mWidth == value)
        return;

    mWidth = value;
    updateShape();

    if (mSubLayer)
        mSubLayer->setInnerRadius(mInnerRadius + mWidth);
}

qint32 SunMenuItemView::width() const
{
    return mWidth;
}

qint32 SunMenuItemView::innerRadius() const
{
    return mInnerRadius;
}

SunMenuItemView* SunMenuItemView::parentMenu() const
{
    return mParentItemView;
}

SunMenuLayer* SunMenuItemView::parentLayer() const
{
    return mParentLayer;
}

SunMenuLayer* SunMenuItemView::subLayer() const
{
    return mSubLayer;
}

SunMenuLayer::ConstantParameterEnum SunMenuItemView::constantParameter() const
{
    return mParentLayer->constantParameter();
}

QList<SunMenuItemView*> SunMenuItemView::childMenus() const
{
    if (mSubLayer)
        return mSubLayer->childMenuItems();

    return QList<SunMenuItemView*>();
}

qint32 SunMenuItemView::leafCount() const
{
    Q_ASSERT(mItemModel != 0);

    return mItemModel->leafCount();
}

void SunMenuItemView::updateShape()
{
    QPainterPath newPath;

    qreal tmp = qAbs(sweepLength());
    if (width() != 0 && tmp > 0.001)
    {
        qint32 innerRad = innerRadius();
        qint32 outerRadius = innerRad + width();
        QRectF r = QRect(-outerRadius, -outerRadius, outerRadius * 2,
                         outerRadius * 2);

        if (innerRad == 0 && qAbs(sweepLength() - 360) < 0.0001)
        {
            newPath.addEllipse(r);
        }
        else
        {
            newPath.arcMoveTo(r, startAngle());
            newPath.arcTo(r, startAngle(), sweepLength());

            if(innerRad == 0)
            {
                newPath.lineTo(0,0);
            }else
            {
                r = QRect(-innerRad, -innerRad, innerRad * 2, innerRad * 2);
                newPath.arcTo(r, startAngle() + sweepLength(), -sweepLength());
            }
            newPath.closeSubpath();
        }
    }
    //
    setPath(newPath);
    reinitializeDisplayedItemPosition();
}

AbstractSizableItem* SunMenuItemView::displayedItem() const
{
    Q_ASSERT(mItemModel != 0);

    return mItemModel->displayedItem();
}

void SunMenuItemView::reinitializeDisplayedItemPosition()
{
    qint32 maxWidth = width();
    qint32 maxHeight;
    QGraphicsItem* gi = displayedItem()->graphicsItem();

    //default
    gi->resetTransform();

    // Calculate maxHeight as smaller chord(only for small sweepLengths)
    if (sweepLength() <= 90)
    {
        qreal biggerChord = 2 * (innerRadius() + maxWidth)
                * /*qAbs*/(qSin((M_PI / 180) * sweepLength() / 2));
        qreal smallerChord = 2 * innerRadius()
                * /*qAbs*/(qSin((M_PI / 180) * sweepLength() / 2));
        maxHeight = (0.2 * smallerChord + 1.4 * biggerChord) / 2;
    }
    else
        maxHeight = displayedItem()->maximumHeight();

    //hide item if it too small
    if (maxWidth < 10 || maxHeight < 5)
    {
        gi->hide();
        return;
    }

    QRectF graphicsItemRect;

    if (sweepLength() == 360 && innerRadius() == 0)
    {
        displayedItem()->setMaximumSize(2 * maxWidth /*diameter*/, maxHeight);
        graphicsItemRect = gi->boundingRect();
        gi->setPos(-graphicsItemRect.width() / 2,
                   -graphicsItemRect.height() / 2);

        gi->show();
        return;
    }

    displayedItem()->setMaximumSize(maxWidth - 10, maxHeight);
    graphicsItemRect = gi->boundingRect();

    /////////////////////////////////////////////////////////////////////////////////
    //positioning mDisplayedItem (rotation and coordinates).
    qreal rotationAngle = startAngle() + sweepLength() / 2;

    // Getting distance and angle (polar coordinates) + some centering adjustments
    // We assume that (0,0) item's coordinate is it's top left corner
    //(like QGraphicsSimpleTextItem and QGraphicsProxyWidget).
    qreal angle, distance;
    if (rotationAngle >= 270 || rotationAngle <= 90)
    {
        distance = innerRadius() + maxWidth / 2 - graphicsItemRect.width() / 2;
        angle = rotationAngle
                + (180 / M_PI)
                * qAtan(graphicsItemRect.height() / (2 * distance));
    }
    else
    {
        distance = innerRadius() + maxWidth / 2 + graphicsItemRect.width() / 2;
        angle = rotationAngle
                - (180 / M_PI)
                * qAtan(graphicsItemRect.height() / (2 * distance));

        rotationAngle -= 180;
    }

    gi->setPos(distance * qCos((M_PI / 180) * angle),
               -distance * qSin((M_PI / 180) * angle));
    gi->setRotation(-rotationAngle); //minus - because this function rotates clockwise.

    gi->show();
    ///////////////////////////////////////////////////////////////////////////////////
}

void SunMenuItemView::recalculateChildMenusAngles()
{
    Q_ASSERT(mItemModel != 0);

    qint32 leafCount = mItemModel->leafCount();
    if (leafCount == 0)
        return;

    qreal sweepLengthForLeafs = sweepLength() / leafCount;
    qreal childStartAngle = startAngle();

    foreach(SunMenuItemView* m, childMenus())
    {
        m->setStartAngle(childStartAngle);

        if (m->mItemModel->leafCount() == 0)
        {
            m->setSweepLength(sweepLengthForLeafs);
            childStartAngle += sweepLengthForLeafs;
        }
        else
        {
            qreal tmp = m->mItemModel->leafCount() * sweepLengthForLeafs;
            m->setSweepLength(tmp);
            childStartAngle += tmp;
        }
    }
}

qint32 SunMenuItemView::depthLevel() const
{
    if (!mParentItemView)
        return 0;
    return mParentItemView->depthLevel() + 1;
}

qint32 SunMenuItemView::treeHeight(bool onlyVisible) const
{
    if (!mSubLayer || (onlyVisible && !mSubLayer->isVisible()))
        return 1;

    qint32 result = 0;

    foreach(SunMenuItemView* mc, mSubLayer->childMenuItems())
    {
        qint32 tmp = mc->treeHeight(onlyVisible) + 1;
        if (tmp > result)
            result = tmp;
    }

    return result;
}

QList<SunMenuLayer*> SunMenuItemView::layers(bool onlyVisible) const
{
    QList<SunMenuLayer*> result;
    if (mSubLayer && (!onlyVisible || (mSubLayer->isVisible() && !mSubLayer->isFolding())))
    {
        result.append(mSubLayer);
        foreach(SunMenuItemView* mc, mSubLayer->childMenuItems())
            result.append(mc->layers(onlyVisible));
    }

    return result;
}

void SunMenuItemView::trigger() const
{
    Q_ASSERT(mItemModel != 0);

    mItemModel->action()->trigger();
}

void SunMenuItemView::hideSublayer() const
{
    if (!mSubLayer)
        return;

    mSubLayer->hide();
    foreach(SunMenuItemView* mc, mSubLayer->childMenuItems())
    {
        mc->hideSublayer();
    }
}

void SunMenuItemView::showSublayer() const
{
    if (!mSubLayer)
        return;

    mSubLayer->show();
}

void SunMenuItemView::focusInEvent(QFocusEvent * event)
{
    if (behavior() == 0)
        return;

    behavior()->focusInEvent(this, event);
}
void SunMenuItemView::focusOutEvent(QFocusEvent * event)
{
    if (behavior() == 0)
        return;

    behavior()->focusOutEvent(this, event);
}
void SunMenuItemView::hoverEnterEvent(QGraphicsSceneHoverEvent * event)
{
    if (behavior() == 0)
        return;

    behavior()->hoverEnterEvent(this, event);
}

void SunMenuItemView::hoverLeaveEvent(QGraphicsSceneHoverEvent * event)
{
    if (behavior() == 0)
        return;

    behavior()->hoverLeaveEvent(this, event);
}

void SunMenuItemView::hoverMoveEvent(QGraphicsSceneHoverEvent * event)
{
    if (behavior() == 0)
        return;

    behavior()->hoverMoveEvent(this, event);
}
void SunMenuItemView::keyPressEvent(QKeyEvent * event)
{
    if (behavior() == 0)
        return;

    behavior()->keyPressEvent(this, event);
}
void SunMenuItemView::keyReleaseEvent(QKeyEvent * event)
{
    if (behavior() == 0)
        return;

    behavior()->keyReleaseEvent(this, event);
}
void SunMenuItemView::mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event)
{
    if (behavior() == 0)
        return;

    behavior()->mouseDoubleClickEvent(this, event);
}

void SunMenuItemView::mouseMoveEvent(QGraphicsSceneMouseEvent * event)
{
    if (behavior() == 0)
        return;

    behavior()->mouseMoveEvent(this, event);
}
void SunMenuItemView::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
    if (behavior() == 0)
        return;

    behavior()->mousePressEvent(this, event);
}
void SunMenuItemView::mouseReleaseEvent(QGraphicsSceneMouseEvent * event)
{
    if (behavior() == 0)
        return;

    behavior()->mouseReleaseEvent(this, event);
}

