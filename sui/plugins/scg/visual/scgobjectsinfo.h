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

#ifndef SCGOBJECTINFO_H_
#define SCGOBJECTINFO_H_

/*!
 * This file contains implicitly shared classes for storing SCgObjects information.
 */

#include <QObject>
#include "scgprerequest.h"

class SCgObjectInfo
{
public:
    explicit SCgObjectInfo(const SCgVisualObject* obj);
    virtual ~SCgObjectInfo();


    /*! Get object type.
     * @return Return type of described SCgObject. For example: SCgObject::SCgNodeType
     */
    virtual int objectType() const;

    /*! Get type alias
      * @return Return string that represent object type
      */
    virtual const QString& typeAlias() const;
    /*! Setup new type alias
      * @param alias New type alias
      */
    virtual void setTypeAlias(const QString &alias);

    /*! Get string identifier
      * @return Return string identifier value
      */
    virtual const QString& idtfValue() const;
    /*! Setup new string identifier
      * @param idtf New string identifier value
      */
    virtual void setIdtfValue(const QString &idtf);

    /*! Get color
      * @return Return object color
      */
    virtual const QColor& shapeColor() const;
    /*! Setup new object color
      * @param color New object color
      */
    virtual void setShapeColor(const QColor &color);

    /*! Get local id
      * @return Retrun object local id
      */
    virtual const QString& id() const;
    /*! Setup new local object id
      * @param id New local object id
      */
    virtual void setId(const QString &id);

    /*! Get local id of parent object
      * @return Return id of parent object
      */
    virtual const QString& parentId() const;
    /*! Setup new parent local id
      * @param id New parent local id
      */
    virtual void setParentId(const QString &id);

protected:
    //! SCgObject type alias
    QString mTypeAlias;
    //! String identifier value
    QString mIdtfValue;
    //! Object color
    QColor mShapeColor;
    //! Local object id
    QString mId;
    //! Local id of parent object
    QString mParentId;
};


class SCgNodeInfo: public SCgObjectInfo
{

public:
    explicit SCgNodeInfo(const SCgVisualNode* obj);
    virtual ~SCgNodeInfo();

    virtual int objectType() const;

    //! Return node position in scene
    const QPointF& pos() const;
    //! Setup new node position
    void setPos(const QPointF &pos);
    //! Check if node have attached bus
    bool haveBus() const;
    //! Setup new bus flag
    void setHaveBus(bool flag);
    //! Return content code type
    int contentType() const;
    //! Setup new content type
    void setContentType(int ctype);
    //! Return content mime type
    const QString& contentMimeType() const;
    //! Setup new content mime type
    void setContentMimeType(const QString &mime);
    //! Return content file name
    const QString& contentFilename() const;
    //! Setup new conten file name
    void setContentFileName(const QString &fileName);
    //! Return content data
    const QVariant& contentData() const;
    //! Setup new content data
    void setContentData(const QVariant &data);


private:
    //! Node position in scene
    QPointF mPos;
    //! Flag of attached bus
    bool mHaveBus;
    /*! Number Code that represent content type
      * 0 - empty, 1 - int, 2 - real, 3 - string, 4 - binary
      */
    int mContentType;
    //! Mime type of content
    QString mContentMimeType;
    //! Content file name
    QString mContentFilename;
    //! Content data
    QVariant mContentData;
};


class SCgPairInfo: public SCgObjectInfo
{

public:
    explicit SCgPairInfo(const SCgVisualPair* obj);
    virtual ~SCgPairInfo();

    virtual int objectType() const;

    //! Return line points
    const QVector<QPointF>& points() const;
    //! Setup new line points
    void setPoints(QVector<QPointF> &points);

    //! Return local id of begin object
    const QString& beginObjectId() const;
    //! Setup new begin object local id
    void setBeginObjectId(const QString &id);

    //! Return local id of end object
    const QString& endObjectId() const;
    //! Setup new end object local id
    void setEndObjectId(const QString &id);

    //! Get begin dot position
    double beginDot() const;
    //! Setup new position for the begin dot
    void setBeginDot(double pos);

    //! Return end dot position
    double endDot() const;
    //! Setup new position for the end dot
    void setEndDot(double pos);

private:
    //! Line points
    QVector<QPointF> mPoints;
    //! Local id of begin object
    QString mBeginObjectId;
    //! Local id of end object
    QString mEndObjectId;
    //! Begin dot position on line
    double mBeginDot;
    //! End dot position on line
    double mEndDot;
};



class SCgContourInfo: public SCgObjectInfo
{

public:
    explicit SCgContourInfo(const SCgVisualContour* obj);

    virtual ~SCgContourInfo();

    virtual int objectType() const;

    //! Return contour points
    const QVector<QPointF>& points() const;
    //! Setup new contour points
    void setPoints(const QVector<QPointF> &points);

private:
    //! Contour points
    QVector<QPointF> mPoints;
};



class SCgBusInfo: public SCgObjectInfo
{

public:
    explicit SCgBusInfo(const SCgVisualBus* obj);
    virtual ~SCgBusInfo();

    virtual int objectType() const;

    //! Return bus points
    const QVector<QPointF>& points() const;
    //! Setup new points for bus
    void setPoints(const QVector<QPointF> &points);

    //! Return local id of bus owner
    const QString& ownerId() const;
    //! Setup new owner local id
    void setOwnerId(const QString &id);

private:
    //! Bus points
    QVector<QPointF> mPoints;
    //! Owner local id
    QString mOwnerId;
};

#endif /* SCGOBJECTINFO_H_ */
