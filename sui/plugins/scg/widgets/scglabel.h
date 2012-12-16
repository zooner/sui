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

#ifndef SCGLABEL_H
#define SCGLABEL_H

#include <QGraphicsProxyWidget>

class QLabel;
//------------------------------------------------------------------------------
class SCgLabel : public QGraphicsProxyWidget
{
	Q_OBJECT

public:
    explicit SCgLabel(QGraphicsItem *parent = 0, GraphicsItemFlags additionalFlags = 0);
    explicit SCgLabel(const QString &text, QGraphicsItem *parent = 0,
                      GraphicsItemFlags additionalFlags = 0);
	~SCgLabel();

    //! @copydoc QLabel::text
	QString text() const;
	//! @copydoc QLabel::pixmap
	const QPixmap * pixmap() const;
#ifndef QT_NO_PICTURE
    //! @copydoc QLabel::picture
    const QPicture * picture() const;
#endif
#ifndef QT_NO_MOVIE
    //! @copydoc QLabel::movie
    QMovie * movie() const;
#endif

    //! @copydoc QLabel::textFormat
    Qt::TextFormat textFormat() const;
	//! @copydoc QLabel::setTextFormat
    void setTextFormat(Qt::TextFormat textFormat);

	//! @copydoc QLabel::alignment
	Qt::Alignment alignment() const;
	//! @copydoc QLabel::setAlignment
    void setAlignment(Qt::Alignment alignment);

	//! @copydoc QLabel::setWordWrap
	void setWordWrap(bool on);
	//! @copydoc QLabel::wordWrap
	bool wordWrap() const;

	//! @copydoc QLabel::indent
	int indent() const;
	//! @copydoc QLabel::setIndent
    void setIndent(int indent);

	//! @copydoc QLabel::margin
	int margin() const;
	//! @copydoc QLabel::setMargin
    void setMargin(int margin);

	//! @copydoc QLabel::hasScaledContents
	bool hasScaledContents() const;
	//! @copydoc QLabel::setScaledContents
    void setScaledContents(bool scaledContents);
	//! @copydoc QLabel::sizeHint
	QSize sizeHint() const;
	//! @copydoc QLabel::minimumSizeHint
	QSize minimumSizeHint() const;
#ifndef QT_NO_SHORTCUT
    //! @copydoc QLabel::setBuddy
    void setBuddy(QWidget *buddy);
	//! @copydoc QLabel::buddy
	QWidget * buddy() const;
#endif
    //! @copydoc QLabel::heightForWidth
    int heightForWidth(int heightForWidth) const;

	//! @copydoc QLabel::openExternalLinks
	bool openExternalLinks() const;
	//! @copydoc QLabel::setOpenExternalLinks
	void setOpenExternalLinks(bool open);

	//! @copydoc QLabel::setTextInteractionFlags
	void setTextInteractionFlags(Qt::TextInteractionFlags flags);
	//! @copydoc QLabel::textInteractionFlags
	Qt::TextInteractionFlags textInteractionFlags() const;

	//! @copydoc QLabel::setSelection
    void setSelection(int start, int length);
	//! @copydoc QLabel::hasSelectedText
	bool hasSelectedText() const;
    //! @copydoc QLabel::selectedText
	QString selectedText() const;
	//! @copydoc QLabel::selectionStart
	int selectionStart() const;

public slots:
	//! @copydoc QLabel::setText
    void setText(const QString &text);
	//! @copydoc QLabel::setPixmap
    void setPixmap(const QPixmap &pixmap);
#ifndef QT_NO_PICTURE
    //! @copydoc QLabel::setPicture
    void setPicture(const QPicture &picture);
#endif
#ifndef QT_NO_MOVIE
    //! @copydoc QLabel::setMovie
    void setMovie(QMovie *movie);
#endif
    //! @copydoc QLabel::setNum
    void setNum(int num);
	//! @copydoc QLabel::setNum
    void setNum(double num);
	//! @copydoc QLabel::clear
	void clear();

signals:
	//! @copydoc QLabel::linkActivated
	void linkActivated(const QString &link);
	//! @copydoc QLabel::linkHovered
	void linkHovered(const QString &link);

protected:
    /*! Setup native widget and configure it
      * @param nativeWidget Pointer to native widget (QLabel)
      */
    void setNativeWidget(QLabel *nativeWidget);
    //! Return pointer to native widget
    QLabel * nativeWidget() const;
};
//------------------------------------------------------------------------------
#endif // SCGLABEL_H
