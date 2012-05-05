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

#ifndef SCGVISUALOBJECT_H
#define SCGVISUALOBJECT_H

#include <QObject>
#include <QGraphicsItem>

#include "objects/scgobjectobserver.h"

#include "scgprerequest.h"


class SCgVisualObject : public QObject, public QGraphicsItem,
                        public SCgObjectObserver
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

    friend class SCgPlugin;

public:
    // scg object types
    typedef enum
    {
        SCgNodeType = UserType + 2,
        SCgPairType,
        SCgBusType,
        SCgContourType,
        SCgControlType,
        SCgNoType
    } SCgObjectType;

public:
    virtual int type() const = 0;

    explicit SCgVisualObject(QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);
    virtual ~SCgVisualObject();

    //! Check if type is an scg-object type
    static bool isSCgVisualObjectType(int type);

    //! Check if type is an scg-pointObject type
    static bool isSCgVisualPointObjectType(int type);

public:

    /*! Method to update object position.
      It calls when object need to recalculate it position.
      */
    virtual void updatePosition() = 0;

    /*! Show/hide boudngin box
        \param value    Visibility flag value.
      */
    void setBoundingBoxVisible(bool value);
    //! Check if bounding box is visible
    bool isBoundingBoxVisible() const;

    /*! Resync whole object data. It updates whole data from sc.g-object
      * in visual object.
      */
    virtual void _reSync();

protected:
    //! @copydoc SCgObjectObserver::_update
    virtual void _update(UpdateEventType eventType, SCgObject *object);
    //! @copydoc SCgObjectObserver::_needSync
    virtual void _needSync();

protected:
    //! @copydoc QGraphicsItem::hoverEnterEvent
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    //! @copydoc QGraphicsItem::hoverLeaveEvent
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

    //! @copydoc QGraphicsItem::itemChange
    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    //! Synchronize with observed object if it need
    void sync();

    /*! Return observed object with index \p idx casted to \p ObjectType
      * @param idx Observed object index
      * @return Return pointer to specified observed object, casted to \p ObjectType.
      */
    template<class ObjectType>
    ObjectType* observedObjectT(quint32 idx) const
    {
        return qobject_cast<ObjectType*>(observedObject(idx));
    }

public:
    /*!
     * @return unique identifier of this object in current environment.
     */
    long id() const
    {
        return reinterpret_cast<long>(this);
    }

    long parentId() const
    {
        return ((SCgVisualObject*)this->parentItem())->id();
    }

    // work with scuri's
public:

protected:
    //! Main color
    QColor mColor;
    //! Bounding box drawing flag
    bool mIsBoundingBoxVisible;
    //! Text item
    QGraphicsTextItem *mTextItem;
    //! true, if parent about to change.
    bool mParentChanging;
};


#endif // SCGOBJECT_H
