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
#include "gwfobjectinforeader.h"

#include "visual/scgobjectsinfo.h"

#include <QScopedPointer>

GwfObjectInfoReader::GwfObjectInfoReader()
{
    createTypesMap();
}

GwfObjectInfoReader::~GwfObjectInfoReader()
{
    del();
}

void GwfObjectInfoReader::del()
{
    TypeToObjectsMap::iterator it = mObjectsInfo.begin();
    ObjectInfoList::iterator itList;

    for(;it != mObjectsInfo.end(); ++it)
    {
        for(itList = it.value().begin(); itList != it.value().end(); ++itList)
            delete *itList;
        it.value().clear();
    }
    mObjectsInfo.clear();
}

void GwfObjectInfoReader::createTypesMap()
{
    // initialize types mapping

    // nodes
    mGWFType2TypeAlias["node/const/not_define"] = "node/const/not_define";
    mGWFType2TypeAlias["node/const/general_node"] = "node/const/general_node";
    mGWFType2TypeAlias["node/const/predmet"] = "node/const/predmet";
    mGWFType2TypeAlias["node/const/nopredmet"] = "node/const/nopredmet";
    mGWFType2TypeAlias["node/const/symmetry"] = "node/const/symmetry";
    mGWFType2TypeAlias["node/const/asymmetry"] = "node/const/asymmetry";
    mGWFType2TypeAlias["node/const/attribute"] = "node/const/attribute";
    mGWFType2TypeAlias["node/const/relation"] = "node/const/relation";
    mGWFType2TypeAlias["node/const/atom"] = "node/const/atom";
    mGWFType2TypeAlias["node/const/group"] = "node/const/group";

    mGWFType2TypeAlias["node/var/not_define"] = "node/var/not_define";
    mGWFType2TypeAlias["node/var/general_node"] = "node/var/general_node";
    mGWFType2TypeAlias["node/var/predmet"] = "node/var/predmet";
    mGWFType2TypeAlias["node/var/nopredmet"] = "node/var/nopredmet";
    mGWFType2TypeAlias["node/var/symmetry"] = "node/var/symmetry";
    mGWFType2TypeAlias["node/var/asymmetry"] = "node/var/asymmetry";
    mGWFType2TypeAlias["node/var/attribute"] = "node/var/attribute";
    mGWFType2TypeAlias["node/var/relation"] = "node/var/relation";
    mGWFType2TypeAlias["node/var/atom"] = "node/var/atom";
    mGWFType2TypeAlias["node/var/group"] = "node/var/group";

    mGWFType2TypeAlias["node/meta/not_define"] = "node/meta/not_define";
    mGWFType2TypeAlias["node/meta/general_node"] = "node/meta/general_node";
    mGWFType2TypeAlias["node/meta/predmet"] = "node/meta/predmet";
    mGWFType2TypeAlias["node/meta/nopredmet"] = "node/meta/nopredmet";
    mGWFType2TypeAlias["node/meta/symmetry"] = "node/meta/symmetry";
    mGWFType2TypeAlias["node/meta/asymmetry"] = "node/meta/asymmetry";
    mGWFType2TypeAlias["node/meta/attribute"] = "node/meta/attribute";
    mGWFType2TypeAlias["node/meta/relation"] = "node/meta/relation";
    mGWFType2TypeAlias["node/meta/atom"] = "node/meta/atom";
    mGWFType2TypeAlias["node/meta/group"] = "node/meta/group";

    // pairs
    mGWFType2TypeAlias["arc/const/pos"] = "pair/const/pos/-/orient";
    mGWFType2TypeAlias["arc/var/pos"] = "pair/var/pos/-/orient";
    mGWFType2TypeAlias["arc/meta/pos"] = "pair/meta/pos/-/orient";

    mGWFType2TypeAlias["arc/const/neg"] = "pair/const/neg/-/orient";
    mGWFType2TypeAlias["arc/var/neg"] = "pair/var/neg/-/orient";
    mGWFType2TypeAlias["arc/meta/neg"] = "pair/meta/neg/-/orient";

    mGWFType2TypeAlias["arc/const/fuz"] = "pair/const/fuz/-/orient";
    mGWFType2TypeAlias["arc/var/fuz"] = "pair/var/fuz/-/orient";
    mGWFType2TypeAlias["arc/meta/fuz"] = "pair/meta/fuz/-/orient";

    mGWFType2TypeAlias["arc/const/pos/temp"] = "pair/const/pos/temp/orient";
    mGWFType2TypeAlias["arc/var/pos/temp"] = "pair/var/pos/temp/orient";
    mGWFType2TypeAlias["arc/meta/pos/temp"] = "pair/meta/pos/temp/orient";

    mGWFType2TypeAlias["arc/const/neg/temp"] = "pair/const/neg/temp/orient";
    mGWFType2TypeAlias["arc/var/neg/temp"] = "pair/var/neg/temp/orient";
    mGWFType2TypeAlias["arc/meta/neg/temp"] = "pair/meta/neg/temp/orient";

    mGWFType2TypeAlias["arc/const/fuz/temp"] = "pair/const/fuz/temp/orient";
    mGWFType2TypeAlias["arc/var/fuz/temp"] = "pair/var/fuz/temp/orient";
    mGWFType2TypeAlias["arc/meta/fuz/temp"] = "pair/meta/fuz/temp/orient";

    mGWFType2TypeAlias["pair/const/synonym"] = "pair/const/-/-/-";
    mGWFType2TypeAlias["pair/var/noorient"] = "pair/var/-/-/-";
    mGWFType2TypeAlias["pair/meta/noorient"] = "pair/meta/-/-/-";

    mGWFType2TypeAlias["pair/const/orient"] = "pair/const/-/-/orient";
    mGWFType2TypeAlias["pair/var/orient"] = "pair/var/-/-/orient";
    mGWFType2TypeAlias["pair/meta/orient"] = "pair/meta/-/-/orient";

    //deprecated. For supporting old format.
    mGWFType2TypeAlias["pair/rail/noorient"] = "pair/var/-/-/-";
    mGWFType2TypeAlias["pair/rail/orient"] = "pair/var/-/-/orient";
    mGWFType2TypeAlias["pair/rail2/noorient"] = "pair/meta/-/-/-";
    mGWFType2TypeAlias["pair/rail2/orient"] = "pair/meta/-/-/orient";
}

bool GwfObjectInfoReader::read(QIODevice *device)
{
    del();

    mLastError.clear();

    QDomDocument document;
    if (!device->open(QIODevice::ReadOnly))
    {
        mLastError = QString(QObject::tr("Can't open device for reading"));
        return false;
    }
    if (!document.setContent(device->readAll()))
    {
        mLastError = QString(QObject::tr("Can't parse xml"));
        device->close();
        return false;
    }


    QDomElement root = document.documentElement();

    if (root.tagName() != "GWF")
    {
        mLastError = QString(QObject::tr("Given document has unsupported format %1").arg(root.tagName()));
        device->close();
        return false;
    }
    else
        if (root.hasAttribute("version") && root.attribute("version") != "1.6")
        {
            mLastError = QString(QObject::tr("Version %1 of GWF files not supported.\n"
                                        "Just version 1.6 supported.")).arg(root.attribute("version"));
            device->close();
            return false;
        }

    // get static sector
    QDomElement staticSector = root.firstChildElement("staticSector");

    // parse nodes
    QDomElement element = staticSector.firstChildElement("node");
    while (!element.isNull())
    {
        if (!parseNode(element))
        {
            device->close();
            return false;
        }

        element = element.nextSiblingElement("node");
    }

    // parse arcs
    element = staticSector.firstChildElement("arc");
    while (!element.isNull())
    {
        if (!parsePair(element))
        {
            device->close();
            return false;
        }

        element = element.nextSiblingElement("arc");
    }

    // parse pairs
    element = staticSector.firstChildElement("pair");
    while (!element.isNull())
    {
        if (!parsePair(element))
        {
            device->close();
            return false;
        }

        element = element.nextSiblingElement("pair");
    }

    // parse buses
    element = staticSector.firstChildElement("bus");
    while (!element.isNull())
    {
        if (!parseBus(element))
        {
            device->close();
            return false;
        }

        element = element.nextSiblingElement("bus");
    }

    // parse contours
    element = staticSector.firstChildElement("contour");
    while (!element.isNull())
    {
        if (!parseContour(element))
        {
            device->close();
            return false;
        }

        element = element.nextSiblingElement("contour");
    }

    device->close();

    return true;
}

bool GwfObjectInfoReader::parseObject(const QDomElement &element, SCgObjectInfo* info)
{
    if(info->objectType() == SCgVisualObject::SCgPairType || info->objectType() == SCgVisualObject::SCgNodeType)
    {
        QString type;
        if (getAttributeString(element, "type", type))
        {
            GWFType2TypeAliasMap::iterator it = mGWFType2TypeAlias.find(type);
            if (it == mGWFType2TypeAlias.end())
            {
                errorUnknownElementType(element.tagName(), type);
                return false;
            }else
                info->setTypeAlias(it.value());
        }
        else
            return false;
    }

    QString v;
    if (!getAttributeString(element, "id", v))
        return false;
    info->setId(v);

    if (!getAttributeString(element, "parent", v))
        return false;
    info->setParentId(v);

    if (!getAttributeString(element, "idtf", v))
        return false;
    info->setIdtfValue(v);

    return true;
}

bool GwfObjectInfoReader::parseNode(const QDomElement &element)
{
    QScopedPointer<SCgNodeInfo> nodeInfo(new SCgNodeInfo(0));

    if(!parseObject(element, nodeInfo.data()))
        return false;

    qreal x, y;
    if (!getAttributeDouble(element, "x", x) || !getAttributeDouble(element, "y", y))
        return false;


    // get content element
    QDomElement contEl = element.firstChildElement("content");
    if (contEl.isNull())
    {
        errorHaventContent(element.tagName());
        return false;
    }

    // get content type
    int cType;
    if (!getAttributeInt(contEl, "type", cType))
        return false;
     nodeInfo->setContentType(cType);

    // get mime type
    QString mime;
    if (!getAttributeString(contEl, "mime_type", mime))
        return false;
    nodeInfo->setContentMimeType(mime);

    // set content to nodeInfo
    if (cType > 0 && cType < 5)
    {
        if (cType == 1 || cType == 2 || cType == 3)
            nodeInfo->setContentData(QVariant(contEl.firstChild().nodeValue()));
        else if (cType == 4)
        {
            // get file name
            QString fileName;
            getAttributeString(contEl, "file_name", fileName);
            nodeInfo->setContentFileName(fileName);
            QString cData = contEl.firstChild().nodeValue();
            QByteArray arr = QByteArray::fromBase64(cData.toLocal8Bit());
            nodeInfo->setContentData(QVariant(arr));
        }else
        {
            mLastError = QObject::tr("Content type '%1' doesn't supported for now").arg(cType);
            return false;
        }
    }else if (cType != 0)
    {
        mLastError = QObject::tr("Unknown content type '%1'").arg(cType);
        return false;
    }

    mObjectsInfo[SCgVisualObject::SCgNodeType].append(nodeInfo.take());
    return true;
}

bool GwfObjectInfoReader::parsePair(const QDomElement &element)
{
    QScopedPointer<SCgPairInfo> pairInfo(new SCgPairInfo(0));

    if(!parseObject(element, pairInfo.data()))
        return false;

    QString idb, ide;
    if (!getAttributeString(element, "id_b", idb) ||
        !getAttributeString(element, "id_e", ide))
        return false;
    pairInfo->setBeginObjectId(idb);
    pairInfo->setEndObjectId(ide);

    double db, de;
    if (!getAttributeDouble(element, "dotBBalance", db) ||
        !getAttributeDouble(element, "dotEBalance", de))
        return false;

    pairInfo->setBeginDot(db);
    pairInfo->setEndDot(de);

    QVector<QPointF> points;
    points.push_back(QPointF());
    if (!getElementPoints(element, points))
        return false;
    points.push_back(QPointF());

    pairInfo->setPoints(points);

    mObjectsInfo[SCgVisualObject::SCgPairType].append(pairInfo.take());
    return true;
}

bool GwfObjectInfoReader::parseBus(const QDomElement &element)
{
    QScopedPointer<SCgBusInfo> busInfo(new SCgBusInfo(0));

    if(!parseObject(element,busInfo.data()))
        return false;

    QString owner;
    if (!getAttributeString(element, "owner", owner))
        return false;
    busInfo->setOwnerId(owner);

    double bx, by;
    if (!getAttributeDouble(element, "b_x", bx) || !getAttributeDouble(element, "b_y", by))
        return false;
    double ex, ey;
    if (!getAttributeDouble(element, "e_x", ex) || !getAttributeDouble(element, "e_y", ey))
        return false;

    QVector<QPointF> points;
    points.append(QPointF(bx, by));
    if (!getElementPoints(element, points))
        return false;
    points.append(QPointF(ex, ey));
    busInfo->setPoints(points);

    mObjectsInfo[SCgVisualObject::SCgBusType].append(busInfo.take());
    return true;
}

bool GwfObjectInfoReader::parseContour(const QDomElement &element)
{
    QScopedPointer<SCgContourInfo> contourInfo(new SCgContourInfo(0));

    if(!parseObject(element,contourInfo.data()))
        return false;

    QVector<QPointF> points;
    if (!getElementPoints(element, points))
        return false;
    contourInfo->setPoints(points);

    mObjectsInfo[SCgVisualObject::SCgContourType].append(contourInfo.take());
    return true;
}

bool GwfObjectInfoReader::getAttributeString(const QDomElement &element, QString attribute, QString &result)
{
    if (element.hasAttribute(attribute))
    {
        result = element.attribute(attribute);
        return true;
    }

    errorHaventAttribute(element.tagName(), attribute);
    return false;
}

bool GwfObjectInfoReader::getAttributeDouble(const QDomElement &element, QString attribute, double &result)
{
    if (element.hasAttribute(attribute))
    {
        bool res;
        result = element.attribute(attribute).toDouble(&res);

        if (!res) return false;

        return true;
    }

    errorHaventAttribute(element.tagName(), attribute);
    return false;
}

bool GwfObjectInfoReader::getAttributeInt(const QDomElement &element, QString attribute, int &result)
{
    if (element.hasAttribute(attribute))
    {
        bool res;
        result = element.attribute(attribute).toInt(&res);

        if (!res) return false;

        return true;
    }
    errorHaventAttribute(element.tagName(), attribute);
    return false;
}

bool GwfObjectInfoReader::getElementPoints(const QDomElement &element, QVector<QPointF> &result)
{
    QDomElement points = element.firstChildElement("points");
    if (points.isNull())
    {
        mLastError = QObject::tr("There are no points data for element '%1'").arg(element.tagName());
        return false;
    }

    QDomElement point = points.firstChildElement("point");
    while (!point.isNull())
    {
        double x, y;
        if (!getAttributeDouble(point, "x", x) || !getAttributeDouble(point, "y", y))
            return false;
        result.push_back(QPointF(x, y));
        point = point.nextSiblingElement("point");
    }

    return true;
}

void GwfObjectInfoReader::errorHaventAttribute(QString element, QString attribute)
{
    mLastError = QObject::tr("'%1' element haven't '%2' attribute").arg(element).arg(attribute);
}

void GwfObjectInfoReader::errorFloatParse(QString element, QString attribute)
{
    mLastError = QObject::tr("invalid float value in attribute '%1' of element '%2'").arg(attribute).arg(element);
}

void GwfObjectInfoReader::errorHaventContent(QString element)
{
    mLastError = QObject::tr("node element '%1' haven't content tag").arg(element);
}

void GwfObjectInfoReader::errorUnknownElementType(QString element, QString type)
{
    mLastError = QObject::tr("type '%1' is unknown for element '%2'").arg(type).arg(element);
}
