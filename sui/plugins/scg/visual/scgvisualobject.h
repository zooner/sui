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

//    friend class SCgPlugin;
protected:
    //! use createVisual() instead. \note Do not use Qt's "parent-child" mehanism.
    explicit SCgVisualObject(QGraphicsScene *scene = 0);
    //explicit SCgVisualObject();

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
    virtual ~SCgVisualObject();

    //! Check if type is an scg-object type
    static bool isSCgVisualObjectType(int type);

    //! Check if type is an scg-pointObject type
    static bool isSCgVisualPointObjectType(int type);

    /*! Factory for visuals. Type depends on base object's type
     * \note Do not use Qt's "parent-child" mehanism.
     * \param base Base object for created instance
     * \param scene Scene visual is drawn on
     * \param parent Parent item
     * \return Visual instance of appropriate type, null If type can't be resolved.
     */
    static SCgVisualObject* createVisual(SCgObject* base,
                                         QGraphicsScene* scene);

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

    /*! Returns an SCgObject current instance is based on.
     * That means the object from which drawing information is taken.
     * Current instance observes changes from base object and reflect them in graphics representation.
     * If base object is not set, visual is not drawn.
     * \return base object
     * \see setBaseObject();
     * \see _update();
     */
    SCgObject* baseObject() const { return mBaseObject; }

    /*! Sets base object. Old base object is removed from observed and new is added.
     * If \p object is null, current visual has no source to take drawing information from and it is not drawn.
     * \see baseObject()
     */
    void setBaseObject(SCgObject* object);

protected:
    //! @copydoc SCgObjectObserver::_update
    virtual void _update(UpdateEventType eventType, SCgObject *object);
//    //! @copydoc SCgObjectObserver::_needSync
//    virtual void _needSync();

protected:
    //! @copydoc QGraphicsItem::hoverEnterEvent
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    //! @copydoc QGraphicsItem::hoverLeaveEvent
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

//    //! Synchronize with observed object if it need
//    void sync();

    /*! Return observed object with index \p idx casted to \p ObjectType
      * @param idx Observed object index
      * @return Return pointer to specified observed object, casted to \p ObjectType.
      */
    template<class ObjectType>
    ObjectType* observedObjectT(quint32 idx) const
    {
        return qobject_cast<ObjectType*>(observedObject(idx));
    }

    /*! Clones current instance of visual. It affects only visual representation.
     * No interaction with SCgObjects. Some visuals may clone theirs child items too.
     * \note You should care about absoulute position of cloned objects manualy. /
     * They retain only relative position, but do not set parent object.
     */
//    virtual SCgVisualObject* clone() const = 0;

    virtual void _onBaseObjectChanged();
public:
    /*!
     * @return unique identifier of this object in current environment.
     */
    long id() const
    {
        return reinterpret_cast<quintptr>(this);
    }

    long parentId() const
    {
        return ((SCgVisualObject*)this->parentItem())->id();
    }
protected:
    //! Main color
    QColor mColor;
    //! Bounding box drawing flag
    bool mIsBoundingBoxVisible;
    //! Text item
    QGraphicsTextItem *mTextItem;
    //! true, if parent about to change.
    bool mParentChanging;
    //! Main base for current visual instance
    SCgObject* mBaseObject;

    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
};


#endif // SCGOBJECT_H
