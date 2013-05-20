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

#include "scgprecompiled.h"
#include "scglabel.h"

#include <QLabel>
//------------------------------------------------------------------------------
SCgLabel::SCgLabel(QGraphicsItem *parent, GraphicsItemFlags additionalFlags)
	: QGraphicsProxyWidget(parent)
{
    setNativeWidget(new QLabel);
    setFlags(flags() | additionalFlags);
}
//------------------------------------------------------------------------------
SCgLabel::SCgLabel(const QString &text, QGraphicsItem *parent,
                   GraphicsItemFlags additionalFlags)
	: QGraphicsProxyWidget(parent)
{
    setNativeWidget(new QLabel(text));
    setFlags(flags() | additionalFlags);
}
//------------------------------------------------------------------------------
SCgLabel::~SCgLabel()
{
    /*
    QGraphicsProxyWidget shares ownership with QWidget, so if either of the
    two widgets are destroyed, the other widget will be automatically destroyed
    as well.
    */
}
//------------------------------------------------------------------------------
QString SCgLabel::text() const
{
    return nativeWidget()->text();
}
//------------------------------------------------------------------------------
const QPixmap * SCgLabel::pixmap() const
{
    return nativeWidget()->pixmap();
}
//------------------------------------------------------------------------------
#ifndef QT_NO_PICTURE
const QPicture * SCgLabel::picture() const
{
    return nativeWidget()->picture();
}
#endif
//------------------------------------------------------------------------------
#ifndef SQT_NO_MOVIE
QMovie * SCgLabel::movie() const
{
    return nativeWidget()->movie();
}
#endif
//------------------------------------------------------------------------------
Qt::TextFormat SCgLabel::textFormat() const
{
    return nativeWidget()->textFormat();
}
//------------------------------------------------------------------------------
void SCgLabel::setTextFormat(Qt::TextFormat textFormat)
{
    nativeWidget()->setTextFormat(textFormat);
}
//------------------------------------------------------------------------------
Qt::Alignment SCgLabel::alignment() const
{
    return nativeWidget()->alignment();
}
//------------------------------------------------------------------------------
void SCgLabel::setAlignment(Qt::Alignment alignment)
{
    nativeWidget()->setAlignment(alignment);
}
//------------------------------------------------------------------------------
void SCgLabel::setWordWrap(bool on)
{
    nativeWidget()->setWordWrap(on);
}
//------------------------------------------------------------------------------
bool SCgLabel::wordWrap() const
{
    return nativeWidget()->wordWrap();
}
//------------------------------------------------------------------------------
int SCgLabel::indent() const
{
    return nativeWidget()->indent();
}
//------------------------------------------------------------------------------
void SCgLabel::setIndent(int indent)
{
    nativeWidget()->setIndent(indent);
}
//------------------------------------------------------------------------------
int SCgLabel::margin() const
{
    return nativeWidget()->margin();
}
//------------------------------------------------------------------------------
void SCgLabel::setMargin(int margin)
{
    nativeWidget()->setMargin(margin);
}
//------------------------------------------------------------------------------
bool SCgLabel::hasScaledContents() const
{
    return nativeWidget()->hasScaledContents();
}
//------------------------------------------------------------------------------
void SCgLabel::setScaledContents(bool scaledContents)
{
    nativeWidget()->setScaledContents(scaledContents);
}
//------------------------------------------------------------------------------
QSize SCgLabel::sizeHint() const
{
    return nativeWidget()->sizeHint();
}
//------------------------------------------------------------------------------
QSize SCgLabel::minimumSizeHint() const
{
    return nativeWidget()->minimumSizeHint();
}
//------------------------------------------------------------------------------
#ifndef QT_NO_SHORTCUT
void SCgLabel::setBuddy(QWidget *buddy)
{
    return nativeWidget()->setBuddy(buddy);
}
//------------------------------------------------------------------------------
QWidget * SCgLabel::buddy() const
{
    return nativeWidget()->buddy();
}
#endif
//------------------------------------------------------------------------------
int SCgLabel::heightForWidth(int heightForWidth) const
{
    return nativeWidget()->heightForWidth(heightForWidth);
}
//------------------------------------------------------------------------------
bool SCgLabel::openExternalLinks() const
{
    return nativeWidget()->openExternalLinks();
}
//------------------------------------------------------------------------------
void SCgLabel::setOpenExternalLinks(bool open)
{
    nativeWidget()->setOpenExternalLinks(open);
}
//------------------------------------------------------------------------------
void SCgLabel::setTextInteractionFlags(Qt::TextInteractionFlags flags)
{
    nativeWidget()->setTextInteractionFlags(flags);
}
//------------------------------------------------------------------------------
Qt::TextInteractionFlags SCgLabel::textInteractionFlags() const
{
    return nativeWidget()->textInteractionFlags();
}
//------------------------------------------------------------------------------
void SCgLabel::setSelection(int start, int length)
{
    nativeWidget()->setSelection(start, length);
}
//------------------------------------------------------------------------------
bool SCgLabel::hasSelectedText() const
{
    return nativeWidget()->hasSelectedText();
}
//------------------------------------------------------------------------------
QString SCgLabel::selectedText() const
{
    return nativeWidget()->selectedText();
}
//------------------------------------------------------------------------------
int SCgLabel::selectionStart() const
{
    return nativeWidget()->selectionStart();
}
//------------------------------------------------------------------------------
void SCgLabel::setText(const QString &text)
{
    nativeWidget()->setText(text);
}
//------------------------------------------------------------------------------
void SCgLabel::setPixmap(const QPixmap &pixmap)
{
    nativeWidget()->setPixmap(pixmap);
}
//------------------------------------------------------------------------------
#ifndef QT_NO_PICTURE
void SCgLabel::setPicture(const QPicture &picture)
{
    return nativeWidget()->setPicture(picture);
}
#endif
//------------------------------------------------------------------------------
#ifndef QT_NO_MOVIE
void SCgLabel::setMovie(QMovie *movie)
{
    return nativeWidget()->setMovie(movie);
}
#endif
//------------------------------------------------------------------------------
void SCgLabel::setNum(int num)
{
    return nativeWidget()->setNum(num);
}
//------------------------------------------------------------------------------
void SCgLabel::setNum(double num)
{
    nativeWidget()->setNum(num);
}
//------------------------------------------------------------------------------
void SCgLabel::clear()
{
    nativeWidget()->clear();
}
//------------------------------------------------------------------------------
void SCgLabel::setNativeWidget(QLabel *nativeWidget)
{
    Q_ASSERT(nativeWidget != 0);
    setWidget(nativeWidget);

    connect(nativeWidget, SIGNAL(linkActivated(QString)), SIGNAL(linkActivated(QString)));
    connect(nativeWidget, SIGNAL(linkHovered(QString)), SIGNAL(linkHovered(QString)));

    //! TODO: configure widget pallete and style
}
//------------------------------------------------------------------------------
QLabel * SCgLabel::nativeWidget() const
{
    return static_cast<QLabel *>(widget());
}
//------------------------------------------------------------------------------
