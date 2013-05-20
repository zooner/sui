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

#include "sunmenurepresentation.h"
#include "defaultmenubehavior.h"
#include "sunmenuIiemview.h"
#include "sunmenulayer.h"

SunMenuRepresentation::SunMenuRepresentation(AbstractMenuBehavior* behavior /*=0*/) :
    mBehavior(0), mParentLayer(0), mResultGroup(NULL)
{
    mParentLayer = new SunMenuLayer(this);

    if(behavior == NULL)
    {
        behavior = new DefaultMenuBehavior(this);
    }

    QRadialGradient gradient(0, 0, behavior->maxMenuRadius());
    gradient.setColorAt(1, QColor::fromRgbF(0, 1, 0, 1));
    gradient.setColorAt(0, QColor::fromRgbF(0, 0, 0, 0));

    mDefaultMenuBrush = QBrush(gradient);

    setBehavior(behavior);
}

SunMenuRepresentation::~SunMenuRepresentation()
{
    if (mBehavior != 0)
        delete mBehavior;

    if (mParentLayer != 0)
        delete mParentLayer;
}

void SunMenuRepresentation::addRepresentedMenu(MenuItemModel* newMenu)
{
    mParentLayer->addMenuItem(newMenu);
    mResultGroup = NULL;
    recalculateMenuAngles();
}

SunMenuLayer* SunMenuRepresentation::parentLayer() const
{
    return mParentLayer;
}

QList<SunMenuItemView*> SunMenuRepresentation::representedMenus() const
{
    return mParentLayer->childMenuItems();
}

QGraphicsItem* SunMenuRepresentation::menuItem()
{
    QList<SunMenuItemView*> menus = representedMenus();
    if(menus.count() > 1)
    {
        if(mResultGroup == NULL)
        {
            mResultGroup = new QGraphicsItemGroup();
            mResultGroup->setZValue(-99999);
            mResultGroup->setHandlesChildEvents(false);
            foreach (QGraphicsItem* i, menus)
            {
                i->setZValue(9999);
                mResultGroup->addToGroup(i);
            }
        }
        return mResultGroup;
    }

    if(menus.isEmpty())
        return NULL;
    QGraphicsItem* par = menus.first();
    par->setZValue(9999);
    return par;
}

void SunMenuRepresentation::resetMenu()
{
    behavior()->reset();
}

void SunMenuRepresentation::setBehavior(AbstractMenuBehavior* behavior)
{
    mBehavior = behavior;
}

AbstractMenuBehavior* SunMenuRepresentation::behavior() const
{
    return mBehavior;
}

QBrush SunMenuRepresentation::brush() const
{
    return mDefaultMenuBrush;
}

void SunMenuRepresentation::setBrush(const QBrush &brush)
{
    mDefaultMenuBrush = brush;
    emit brushChanged(mDefaultMenuBrush);
}

qreal SunMenuRepresentation::innerRadius() const
{
    return mInnerRadius;
}

void SunMenuRepresentation::setInnerRadius(qreal radius)
{
    mInnerRadius = radius;
    mParentLayer->setInnerRadius(qRound(radius));
}

QList<SunMenuLayer*> SunMenuRepresentation::layers(bool onlyVisible /*= true*/) const
{
    QList<SunMenuLayer*> result;

    if (!onlyVisible || (mParentLayer->isVisible()&&!mParentLayer->isFolding()))
    {
        result.append(mParentLayer);

        foreach(SunMenuItemView* mc, representedMenus())
            result.append(mc->layers(onlyVisible));
    }

    return result;
}

qint32 SunMenuRepresentation::treeHeight(bool onlyVisible) const
{
    if (onlyVisible && !mParentLayer->isVisible())
        return 0;

    qint32 result = 0;
    foreach(SunMenuItemView* mc, representedMenus())
    {
        qint32 tmp = mc->treeHeight(onlyVisible);
        if (tmp > result)
            result = tmp;
    }
    return result;
}

bool SunMenuRepresentation::menuContainsPoint(const QPointF& scenePoint)
{
    QGraphicsItem* menu = menuItem();
    if(menu->scene() == NULL) return false;

    //qint32 height = treeHeight();
    //FIXME: rought estimation
    qint32 maxMenuRadius = behavior()->maxMenuRadius();

    return QLineF(menu->scenePos(), scenePoint).length() <= maxMenuRadius;
}

QPointF SunMenuRepresentation::scenePos()
{
    return menuItem()->scenePos();
}

void SunMenuRepresentation::assoiciateWith(QObject *object)
{
    mAssociatedObject = object;
}

QObject *SunMenuRepresentation::associatedObject() const
{
    return mAssociatedObject;
}

void SunMenuRepresentation::recalculateMenuAngles()
{
    if (representedMenus().isEmpty())
        return;

    qint32 leafCount = 0;
    foreach(SunMenuItemView* mc, representedMenus())
    {
        qint32 currLeafCount = mc->leafCount();
        if(currLeafCount == 0) currLeafCount =1;
        leafCount += currLeafCount;
    }

    qreal sweepLengthForLeafs = 360.0 / leafCount;
    qreal childStartAngle = 0;

    foreach(SunMenuItemView* m, representedMenus())
    {
        m->setStartAngle(childStartAngle);

        qint32 currLeafCount = m->leafCount();
        if (currLeafCount == 0)
        {
            m->setSweepLength(sweepLengthForLeafs);
            childStartAngle += sweepLengthForLeafs;
        }
        else
        {
            qreal tmp = currLeafCount * sweepLengthForLeafs;
            m->setSweepLength(tmp);
            childStartAngle += tmp;
        }
    }
}
