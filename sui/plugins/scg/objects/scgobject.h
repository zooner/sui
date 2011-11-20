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

#ifndef SCGOBJECT_H
#define SCGOBJECT_H

#include "scgprerequest.h"
#include "scgobjectobserver.h"
#include "interfaces/UiObjects.h"

#include <QObject>
#include <QVector3D>
#include <QColor>


/*! Base class for sc.g-object representation. All sc.g-object can be a one of this types:
  * \li sc.g-node - represent sc-node in SCg-code
  * \li sc.g-pair - represent sc-arc (edge) in SCg-code
  * \li sc.g-border - represent content of file referenced by sc-link
  * \li sc.g-bus - visual element, that allow to make sc.g-node contact zone more bigger
  * \li sc.g-contour - simplified visualization of sc-set
  * \li sc.g-control - visualization of sc.g-nodes, that represent commands
  * \chapter Coordinate system
  * All object use hierarchical coordinate system. That mean, if you set parent object \b X for an object \b Y,
  * then world position of object \b Y will be calculated by formula: \b X.pos + \b Y.pos
  */
class SCgObject : public QObject,
                public ScObjectInterface
{
    friend class SCgConstruction;

    Q_OBJECT
    Q_INTERFACES(ScObjectInterface)
protected:

    explicit SCgObject(QObject *parentObject = 0);
public:
    virtual ~SCgObject();

    typedef enum
    {
        Unknown = 0,
        Node,
        Pair,
        Contour,
        Bus,
        Control
    } ObjectType;

public:
    /*! Notify all observers for updates.
      */
    void _sync();

    //! Return object type. All types enumerated in SCgObject::ObjectType enum
    virtual int type() const = 0;

protected:
    /*! Function, that collect all needed updates
      * @param eventType Type of update event
      */
    void _notifyUpdate(SCgObjectObserver::UpdateEventType eventType);

    //! Reset all update flags to null
    void _resetUpdateFalgs();

    // -------------- Work with ScUri's -----------------------------
public:
    typedef QList<SCgObject*> SCgObjectList;

    /*! Get sc.g-objects by ScUri
      * @param uri ScUri of sc-element.
      * @return Return list of sc.g-objects, that assigned to specified \p uri.
      *         If there are no sc.g-objects assigned to specified \p uri, then
      *         return empty list.
      */
    static const SCgObjectList& objectsByScUri(const ScUri &uri);

    //! @copydoc ScObjectInterface::setUri
    void setUri(const ScUri &uri);

private:

    /*! Append this sc.g-object into ScUri mapping list
      * @param uri ScUri of sc.g-object
      */
    void _appendScgObjectIntoUriMap(const ScUri &uri);

    /*! Remove this sc.g-object from ScUri mapping list
      * @param uri ScUri of sc.g-object
      */
    void _removeSCgObjectFromUriMap(const ScUri &uri);

    typedef QMap<ScUri, SCgObjectList> ScUriToSCgObjectListMap;
    //! Map of ScUri's to sc.g-object assigments
    static ScUriToSCgObjectListMap mScUriToSCgObjects;

public:
    // -------------- Work with observers ---------------------------
    /*! Attach new observer to sc.g-object
      * @param observer Pointer to observer
      * @throw If \p observer is already attached to this sc.g-object,
      * then it throw exception
      */
    void attachObserver(SCgObjectObserver *observer);

    /*! Detach observer from sc.g-object
      * @param observer Pointer to observer, that need to be detached
      * @throw If \p observer isn't attached to this sc.g-object, then
      * it throw exception
      */
    void detachObserver(SCgObjectObserver *observer);

    /*! Check if observer attached to sc.g-object
      * @param observer Pointer to observer, that need to be checked
      * @return Return true, if \p observer already attached to this sc.g-object;
      * otherwise return false.
      */
    bool hasAttachedObserver(SCgObjectObserver *observer) const;

    /*! Calculate connection point coordinates for connected sc.g-pair.
      * @param dotPosition Dot position value.
      * @param point World coordinates of second point (fisrt point - is a connection point)
      * for line segment that connected to sc.g-object.
      * @param
      */
    virtual QPointF calculateDotCoordinates(qreal dotPosition, const QPointF &point) const = 0;

    /*! Claculate dot position by coordinates. That function make backward calculation
      * from ScgObject::calculateDotCoordinates.
      * @param point World coordinates of point
      * @return Return dot position value for thi object
      */
    virtual qreal calculateDotPosition(const QPointF &point) const = 0;

    /*! Set pointer to parent object
      * @param parent Pointer to parent object
      */
    void setParentObject(SCgObject *parentObject);

    /*! Return pointer to parent object
      */
    SCgObject* parentObject() const { return mParent; }

    /*! Set object position
      * @param pos New object position
      */
    void setPosition(const QPointF &pos);

    /*! Return object position
      * @return Return Object position
      */
    const QPointF& position() const { return mPosition; }

    /*! Set new size for an object
      * @param size New size
      */
    void setSize(const QPointF &size);

    //! Return object size
    const QPointF& size() const { return mSize; }

    /*! Set new foreground color
      * @param color New foreground color
      */
    void setColorForeground(const QColor &color);

    //! Return foreground color
    const QColor& colorForeground() const { return mColorForeground; }

    /*! Set new background color
      * @param color New background color
      */
    void setColorBackground(const QColor &color);

    //! Return background color
    const QColor& colorBackground() const { return mColorBackground; }

    /*! Set string identifier to object
      * @param idtf New string identifier
      */
    void setIdentifier(const QString &idtf);

    //! Return string identifier
    const QString& identifier() const { return mIdentifier; }

    //! Change object type
    void setObjectType(ScElementType _type);
    //! Return sc.g-object type
    ScElementType objectType() const { return mObjectType; }

    //! Return pointer to construction
    SCgConstruction* construction() const { return mConstruction; }

    //! Return object world coordinates
    QPointF worldPosition() const;


protected:
    //! Remove object from childs list
    void _removeChild(SCgObject *object);
    //! Append object into childs list
    void _appendChild(SCgObject *object);

protected:
    //! Pointer to construction that control this object
    SCgConstruction *mConstruction;

private:
    //! Observers list
    QList<SCgObjectObserver*> mObservers;
    //! List of child objects
    QList<SCgObject*> mChildObjects;
    //! Pointer to parent object
    SCgObject *mParent;
    //! Object position
    QPointF mPosition;
    //! Object size
    QPointF mSize;
    //! Foreground color
    QColor mColorForeground;
    //! Background color
    QColor mColorBackground;
    //! String identifier
    QString mIdentifier;
    //! Vector of flags for update
    char mUpdateFlags[SCgObjectObserver::UpdateEventCount];
    //! ScType contains information about sc.g-object type
    ScElementType mObjectType;


signals:

public slots:

};

#endif // SCGOBJECT_H
