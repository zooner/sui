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

#include <QGraphicsSimpleTextItem>

#include "textsizableitem.h"
#include <QFontMetrics>


TextSizableItem::TextSizableItem(QString text, QGraphicsItem* parent):
    mText(text)
{
    mTextItem = new QGraphicsSimpleTextItem(text, parent);
    initialize();
}

TextSizableItem::TextSizableItem(QGraphicsSimpleTextItem* textItem):
    mTextItem(textItem)
{
    mText = textItem->text();
    initialize();
}

void TextSizableItem::initialize()
{
    mDefaultFont = mTextItem->font();
    QFontMetrics fm = QFontMetrics(mDefaultFont);
    mMaxHeight = fm.height();
    mMaxWidth = fm.width(mText);

    mTextItem->setToolTip(mText);
}

TextSizableItem::~TextSizableItem()
{
    delete mTextItem;
}

void TextSizableItem::setMaximumHeight(int height)
{
    if (mMaxHeight == height)
        return;

    mMaxHeight = height;
    QFontMetrics fm(mDefaultFont);

    if (mMaxHeight >= fm.height())
        mTextItem->setFont(mDefaultFont);
    else
    {
        QFont newFont = mDefaultFont;
        newFont.setPixelSize(mMaxHeight - 2);
        mTextItem->setFont(newFont);
    }

    //Changing height of the font may cause changing width of the text.
    recalculateDisplayedCharactersCount();
}

void TextSizableItem::setMaximumWidth(int width)
{
    if (mMaxWidth == width)
        return;

    mMaxWidth = width;

    recalculateDisplayedCharactersCount();
}

void TextSizableItem::recalculateDisplayedCharactersCount()
{
    QFontMetricsF fm(mTextItem->font());
    ///////////////////////////////////
    ////the fastest solution
    //qreal textWidth = fm.width(mText);
    //if (mMaxWidth >= textWidth)
    //{
    //    mTextItem->setText(mText);
    //    return;
    //}
    //
    //// average char length = textWidth / mText.length()
    //// so heuristic charCount = mMaxWidth/(average char length)
    //int charCount = mMaxWidth * mText.length() / textWidth - 5/*3 dots and some correction*/;
    //
    //mTextItem->setText(mText.mid(0, charCount) + "...");

    /////////////////////////////////
    //the more accurate solution
    if (mMaxWidth >= fm.width(mText))
    {
        //		mTextItem->setFont(mDefaultFont);
        mTextItem->setText(mText);
        return;
    }
    fm = QFontMetrics(mTextItem->font());

    int tmp = fm.width("...");

    if (tmp > mMaxWidth)
    {
        mTextItem->setText("");
        return;
    }

    int charCount = 0;
    foreach(const QChar& c, mText)
    {
        tmp+=fm.width(c);
        if (tmp >= mMaxWidth)
            break;
        ++charCount;
    }

    mTextItem->setText(mText.mid(0, charCount) + "...");
}

int TextSizableItem::maximumWidth() const
{
    return mMaxWidth;
}

int TextSizableItem::maximumHeight() const
{
    return mMaxHeight;
}

QString TextSizableItem::text() const
{
    return mText;
}

QSize TextSizableItem::prefferedSize() const
{
    QFontMetrics fm = QFontMetrics(mDefaultFont);
    return fm.size(Qt::TextSingleLine, mText);
}

QGraphicsItem* TextSizableItem::graphicsItem()
{
    return mTextItem;
}
