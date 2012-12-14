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
#include "scgcontrol.h"

#include "scgplugin.h"

SCgControl::SCgControl(QObject *parent) :
    SCgObject(parent)
{
    setSize(QSizeF(50.f, 25.f));
}

SCgControl::~SCgControl()
{
}

QPointF SCgControl::calculateDotCoordinates(qreal dotPosition, const QPointF &point) const
{
    Q_UNUSED(dotPosition);

    QPointF wpos = position();
    QPolygonF polygon(QRectF(wpos - QPointF(size().width() / 2.f, size().height() / 2.f), size()));
    QPointF p, res;

    p = wpos;

    QPointF p1 = polygon.last();
    QPointF p2, intersectPoint;
    QLineF line, pair(point, p);
    qreal minLength = -1;

    //Find intersection point with minimal distance from @p from to contour
    for (int i = 0; i < polygon.size(); i++)
    {
        p2 = polygon.at(i);
        line.setPoints(p1,p2);
        QLineF::IntersectType intersectType = line.intersect(pair, &intersectPoint);
        if (intersectType == QLineF::BoundedIntersection)
        {
            pair.setP2(intersectPoint);
            if(minLength == -1 || pair.length() < minLength)
            {
                minLength = pair.length();
                res = intersectPoint;
            }
        }

        p1 = p2;
    }

    return res;
}

QPointF SCgControl::calculateDotCoordinatesByAngle(qreal slope, const QPointF &point) const
{
    //! TODO: maybe best implementation could take place here
    return calculateDotCoordinates(slope, point);
}

qreal SCgControl::calculateDotPosition(const QPointF &point) const
{
    Q_UNUSED(point);
    return -1.f;
}

SCgControl::ControlType SCgControl::controlType() const
{
    // get all interfaces we need to work
    UiRootInterface *root = SCgPlugin::rootInterface();
    ScHelperInterface *helper = root->scHelper();

    if (helper->checkInclusion(uri(), helper->keynode("/ui/command/noatom")))
        return NoAtom;

    if (helper->checkInclusion(uri(), helper->keynode("/ui/command/class")))
        return Class;
    //TODO: Extend
    return Unknown;
}

bool SCgControl::childCommands(ScUriVector &childs)
{
    childs.clear();

    // get all interfaces we need to work
    UiRootInterface *root = SCgPlugin::rootInterface();
    ScMemoryInterface *memory = root->scMemory();
    ScHelperInterface *helper = root->scHelper();

    ScUri _uri = uri();
    if (_uri.isEmpty()) SuiExcept(SuiExceptionInternalError,
                                   "ScUri of sc.g-control element is empty",
                                   "bool SCgControl::childCommands(ScUriVector &childs)");

    // get decomposition keynode
    ScUri decompUri = helper->keynode("/etc/decomposition*");
    if  (decompUri.isEmpty()) SuiExcept(SuiExceptionInternalError,
                                        "Can't find decomposition* keynode",
                                        "bool SCgControl::childCommands(ScUriVector &childs)");

    // trying to find child elements
    ScUriVector res;
    if (helper->searchOneShot(ScTemplate() << ScElementType(ScNode | ScConst)
                              << ScElementType(ScArcCommon | ScConst)
                              << _uri
                              << ScElementType(ScArcMain)
                              << decompUri, res))
    {
        // get all child commands
        ScSafeIterator it(memory, ScTemplate() << res[0] << ScElementType(ScArcMain) << ScElementType(ScNode));
        while (!it.is_over())
        {
            childs.append(it.value(2));
            it.next();
        }
    }

    return !childs.empty();
}

void SCgControl::initiated()
{
    ControlType tp = controlType();

    //! \todo: Extend
    switch(tp)
    {
    case NoAtom:
        initiatedNoAtom();
        break;
    };
}

void SCgControl::initiatedNoAtom()
{
    UiRootInterface *root = SCgPlugin::rootInterface();
    /*ScMemoryInterface *memory = */root->scMemory();
    ScHelperInterface *helper = root->scHelper();

    ScUriVector childs, res;
    ScUri uri, mainWindowUri;

    childCommands(childs);
    mainWindowUri = helper->keynode("/ui/main_window");
    foreach(uri, childs)
    {
        // check if command in main window
        helper->ensureExist(ScTemplate() << mainWindowUri << ScElementType(ScArcMain) << uri, res);
    }

}
