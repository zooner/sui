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
#include "scgobjectsinfo.h"

SCgObjectInfo::SCgObjectInfo(const SCgVisualObject* obj)
{
    //! \todo: implement
    Q_UNUSED(obj);
}

SCgObjectInfo::~SCgObjectInfo()
{
}

int SCgObjectInfo::objectType() const
{
    return SCgVisualObject::Type;
}

const QString& SCgObjectInfo::typeAlias() const
{
    return mTypeAlias;
}
void SCgObjectInfo::setTypeAlias(const QString &alias)
{
    mTypeAlias = alias;
}

const QString& SCgObjectInfo::idtfValue() const
{
    return mIdtfValue;
}
void SCgObjectInfo::setIdtfValue(const QString &idtf)
{
    mIdtfValue = idtf;
}

const QColor& SCgObjectInfo::shapeColor() const
{
    return mShapeColor;
}
void SCgObjectInfo::setShapeColor(const QColor &color)
{
    mShapeColor = color;
}

const QString& SCgObjectInfo::id() const
{
    return mId;
}
void SCgObjectInfo::setId(const QString &id)
{
    mId = id;
}

const QString& SCgObjectInfo::parentId() const
{
    return mParentId;
}
void SCgObjectInfo::setParentId(const QString &id)
{
    mParentId = id;
}


//-----------------------------
SCgNodeInfo::SCgNodeInfo(const SCgVisualNode* obj) :
    SCgObjectInfo(obj)
{
}

SCgNodeInfo::~SCgNodeInfo()
{
}

int SCgNodeInfo::objectType() const
{
    return SCgVisualObject::SCgNodeType;
}

const QPointF& SCgNodeInfo::pos() const
{
    return mPos;
}

void SCgNodeInfo::setPos(const QPointF &pos)
{
    mPos = pos;
}

bool SCgNodeInfo::haveBus() const
{
    return mHaveBus;
}

void SCgNodeInfo::setHaveBus(bool flag)
{
    mHaveBus = flag;
}

int SCgNodeInfo::contentType() const
{
    return mContentType;
}

void SCgNodeInfo::setContentType(int ctype)
{
    mContentType = ctype;
}

const QString& SCgNodeInfo::contentMimeType() const
{
    return mContentMimeType;
}

void SCgNodeInfo::setContentMimeType(const QString &mime)
{
    mContentMimeType = mime;
}

const QString& SCgNodeInfo::contentFilename() const
{
    return mContentFilename;
}

void SCgNodeInfo::setContentFileName(const QString &fileName)
{
    mContentFilename = fileName;
}

const QVariant& SCgNodeInfo::contentData() const
{
    return mContentData;
}

void SCgNodeInfo::setContentData(const QVariant &data)
{
    mContentData = data;
}


//---------------------------
SCgPairInfo::SCgPairInfo(const SCgVisualPair* obj) :
    SCgObjectInfo(obj),
    mBeginDot(0.0),
    mEndDot(0.0)
{
}

SCgPairInfo::~SCgPairInfo()
{

}

int SCgPairInfo::objectType() const
{
    return SCgVisualObject::SCgPairType;
}

const QVector<QPointF>& SCgPairInfo::points() const
{
    return mPoints;
}

void SCgPairInfo::setPoints(QVector<QPointF> &points)
{
    mPoints = points;
}

const QString& SCgPairInfo::beginObjectId() const
{
    return mBeginObjectId;
}

void SCgPairInfo::setBeginObjectId(const QString &id)
{
    mBeginObjectId = id;
}

const QString& SCgPairInfo::endObjectId() const
{
    return mEndObjectId;
}

void SCgPairInfo::setEndObjectId(const QString &id)
{
    mEndObjectId = id;
}

double SCgPairInfo::beginDot() const
{
    return mBeginDot;
}

void SCgPairInfo::setBeginDot(double pos)
{
    mBeginDot = pos;
}

double SCgPairInfo::endDot() const
{
    return mEndDot;
}

void SCgPairInfo::setEndDot(double pos)
{
    mEndDot = pos;
}

//--------------------------
SCgContourInfo::SCgContourInfo(const SCgVisualContour* obj) :
    SCgObjectInfo(obj)
{
}

SCgContourInfo::~SCgContourInfo()
{
}

int SCgContourInfo::objectType() const
{
    return SCgVisualObject::SCgContourType;
}

const QVector<QPointF>& SCgContourInfo::points() const
{
    return mPoints;
}

void SCgContourInfo::setPoints(const QVector<QPointF> &points)
{
    mPoints = points;
}

//-------------------------
SCgBusInfo::SCgBusInfo(const SCgVisualBus* obj) :
    SCgObjectInfo(obj)
{
}

SCgBusInfo::~SCgBusInfo()
{

}

int SCgBusInfo::objectType() const
{
    return SCgVisualObject::SCgBusType;
}

const QVector<QPointF>& SCgBusInfo::points() const
{
    return mPoints;
}

void SCgBusInfo::setPoints(const QVector<QPointF> &points)
{
    mPoints = points;
}

const QString& SCgBusInfo::ownerId() const
{
    return mOwnerId;
}

void SCgBusInfo::setOwnerId(const QString &id)
{
    mOwnerId = id;
}
