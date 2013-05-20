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

#ifndef ABSTRACTSIZABLEITEM_H_
#define ABSTRACTSIZABLEITEM_H_

#include <QSize>

class QGraphicsItem;

class AbstractSizableItem
{

public:
    AbstractSizableItem();
    virtual ~AbstractSizableItem();

    virtual void setMaximumHeight(int height) = 0;
    virtual void setMaximumWidth(int width) = 0;

    void setMaximumSize(int width, int height)
    {
        setMaximumWidth(width);
        setMaximumHeight(height);
    }

    void setMaximumSize(QSize size)
    {
        setMaximumSize(size.width(), size.height());
    }

    virtual int maximumWidth() const = 0;
    virtual int maximumHeight() const = 0;
    virtual QSize prefferedSize() const = 0;
    virtual QGraphicsItem* graphicsItem() = 0;

};
#endif // ABSTRACTSIZABLEITEM_H_
