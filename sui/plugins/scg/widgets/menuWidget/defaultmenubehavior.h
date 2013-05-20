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

#ifndef DEFAULTMENUBEHAVIOR_H_
#define DEFAULTMENUBEHAVIOR_H_

#include "abstractmenubehavior.h"

class SunMenuRepresentation;
class SunMenuLayer;
class QAbstractAnimation;
class QPropertyAnimation;

struct AnimationDefinitionsAndConstraints
{
public:
    qint32 maxPrefferedWidthForFocusedLayer;
    qint32 widthForNotFocusedLayers;
    bool isOuterRadiusNeedToBeFixed;
};

class DefaultMenuBehavior: public AbstractMenuBehavior
{
public:
    explicit DefaultMenuBehavior(SunMenuRepresentation* representation,
                                 qint32 minWidth = 10, qint32 maxRadius = 100,
                                 qint32 defaultWidth = 20);
    virtual ~DefaultMenuBehavior();

    virtual void focusInEvent(SunMenuItemView* eventReciever,
                              QFocusEvent* event);
    virtual void focusOutEvent(SunMenuItemView* eventReciever,
                               QFocusEvent* event);

    virtual void hoverEnterEvent(SunMenuItemView* eventReciever,
                                 QGraphicsSceneHoverEvent* event);
    virtual void hoverLeaveEvent(SunMenuItemView* eventReciever,
                                 QGraphicsSceneHoverEvent* event);
    virtual void hoverMoveEvent(SunMenuItemView* eventReciever,
                                QGraphicsSceneHoverEvent* event);

    virtual void keyPressEvent(SunMenuItemView* eventReciever,
                               QKeyEvent* event);
    virtual void keyReleaseEvent(SunMenuItemView* eventReciever,
                                 QKeyEvent* event);

    virtual void mouseDoubleClickEvent(SunMenuItemView* eventReciever,
                                       QGraphicsSceneMouseEvent* event);
    virtual void mouseMoveEvent(SunMenuItemView* eventReciever,
                                QGraphicsSceneMouseEvent* event);
    virtual void mousePressEvent(SunMenuItemView* eventReciever,
                                 QGraphicsSceneMouseEvent* event);
    virtual void mouseReleaseEvent(SunMenuItemView* eventReciever,
                                   QGraphicsSceneMouseEvent* event);

    virtual int maxMenuRadius() const;
    virtual void reset();

    void setMaxRadius(qint32 value);
    qint32 maxRadius() const;

    void setDefaultRadius(qint32 defaultWidth);
    qint32 defaultWidth() const;

    void setMinRadius(qint32 minWidth);
    qint32 minWidth() const;

    SunMenuRepresentation* representation() const;
private:
    qint32 mMaxRadius;
    qint32 mMinWidth;
    qint32 mDefaultWidth;

    QPointer<SunMenuRepresentation> mRepresentation;
    QPointer<QAbstractAnimation> mCurrentAnimation;

    SunMenuItemView* mItemViewClicked;
    SunMenuItemView* mItemUnderMouse;

    QPropertyAnimation* createAnimation(QObject* what, const QVariant& endValue,
                                        const char* property = "width") const;
    QPropertyAnimation* createAnimation(QObject* what,
                                        const QVariant& startValue, const QVariant& endValue,
                                        const char* property = "width") const;

    AnimationDefinitionsAndConstraints getAnimationDefinitionsAndConstraints(SunMenuItemView *focusedItem);
};

#endif /* DEFAULTMENUBEHAVIOR_H_ */
