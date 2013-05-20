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

#ifndef SUNMENUIIEMVIEW_H_
#define SUNMENUIIEMVIEW_H_

#include <QObject>
#include <QGraphicsPathItem>
#include <QPen>
#include "sunmenulayer.h"

class MenuItemModel;
class SunMenuLayer;
class AbstractSizableItem;
class AbstractMenuBehavior;
class SunMenuRepresentation;

class SunMenuItemView: public QObject, public QGraphicsPathItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

    friend class SunMenuLayer;

    Q_PROPERTY(qint32 innerRadius READ innerRadius /*WRITE setInnerRadius NOTIFY innerRadiusChanged*/)
    Q_PROPERTY(qint32 width READ width /*WRITE setWidth NOTIFY widthChanged*/)
    Q_PROPERTY(qreal startAngle READ startAngle WRITE setStartAngle /*NOTIFY startAngleChanged*/)
    Q_PROPERTY(qint32 sweepLength READ sweepLength WRITE setSweepLength /*NOTIFY sweepLengthChanged*/)

    MenuItemModel* mItemModel;

    qreal mStartAngle;
    qreal mSweepLength;

    qint32 mInnerRadius;
    qint32 mWidth;

    SunMenuLayer* mParentLayer;
    SunMenuLayer* mSubLayer;

    SunMenuItemView* mParentItemView;
    //	SunMenuRepresentation* mRepresentation;

    SunMenuItemView(SunMenuLayer* parentLayer, MenuItemModel* itemModel, SunMenuItemView* parent = 0);

public:
    enum { Type = UserType + 900 };

    int type() const
    {
        // Enable the use of qgraphicsitem_cast with this item.
        return Type;
    }

    virtual ~SunMenuItemView();

    qint32 leafCount() const;

    qint32 innerRadius() const;
    qint32 width() const;
    void setInnerRadius(qint32 value);
    void setWidth(qint32 value);
    qint32 outerRadius() const
    {
        return innerRadius() + width();
    }

    qreal startAngle() const;
    qreal sweepLength() const;
    void setStartAngle(qreal value);
    void setSweepLength(qreal value);

    SunMenuLayer::ConstantParameterEnum constantParameter() const;

    AbstractSizableItem* displayedItem() const;

    SunMenuItemView* parentMenu() const;

    SunMenuLayer* subLayer() const;
    SunMenuLayer* parentLayer() const;

    QList<SunMenuItemView* > childMenus() const;

    qint32 depthLevel() const;
    qint32 treeHeight(bool onlyVisible = true) const;
    QList<SunMenuLayer*> layers(bool onlyVisible = true) const;

    SunMenuRepresentation* representation() const;

public slots:
    void trigger() const;

    void hideSublayer() const;
    void showSublayer() const;

protected:
    void focusInEvent(QFocusEvent * event);
    void focusOutEvent(QFocusEvent * event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent * event);
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);

    //signals:
    //	void innerRadiusChanged();
    //	void widthChanged();
    //	void startAngleChanged();
    //	void sweepLengthChanged();

private slots:
    void childItemAdded(MenuItemModel* newMenu);
    void updateBrush(const QBrush& brush);

private:
    //	void setConstantParameter(ConstantParameterEnum constantParameter);

    void addChildItem(MenuItemModel* newChild);
    AbstractMenuBehavior* behavior() const;
    void updateShape();
    void createSubLayer();

    void initialize();

    void reinitializeDisplayedItemPosition();
    void recalculateChildMenusAngles();
};

#endif /* SUNMENUIIEMVIEW_H_ */
