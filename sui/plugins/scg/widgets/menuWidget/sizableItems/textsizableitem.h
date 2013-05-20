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

#ifndef TEXTSIZABLEITEM_H_
#define TEXTSIZABLEITEM_H_

#include "abstractsizableitem.h"

#include <QString>
#include <QFont>

class QGraphicsItem;
class QGraphicsSimpleTextItem;

class TextSizableItem: public AbstractSizableItem
{

public:
    TextSizableItem(QString text, QGraphicsItem* parent = 0);
    TextSizableItem(QGraphicsSimpleTextItem* textItem);
    virtual ~TextSizableItem();

    /**
     * Sets a value of height Item cannot exceed.
     */
    virtual void setMaximumHeight(int height);

    /**
     * Sets a value of width Item cannot exceed.
     */
    virtual void setMaximumWidth(int width);
    virtual int maximumWidth() const;
    virtual int maximumHeight() const;

    QString text() const;

    /*!
     * Returns optimal size for the whole content of item
     */
    virtual QSize prefferedSize() const;

    virtual QGraphicsItem* graphicsItem();

private:

    void recalculateDisplayedCharactersCount();

    void initialize();

    int mMaxHeight;
    int mMaxWidth;

    QFont mDefaultFont;

    QGraphicsSimpleTextItem* mTextItem;
    QString mText;

};
#endif // TEXTSIZABLEITEM_H_
