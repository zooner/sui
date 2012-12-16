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

#ifndef SCGGROUPBOX_H
#define SCGGROUPBOX_H

#include <QGraphicsProxyWidget>

class QGroupBox;
//------------------------------------------------------------------------------
class SCgGroupBox : public QGraphicsProxyWidget
{
	Q_OBJECT

public:
    explicit SCgGroupBox(QGraphicsItem *parent = 0);
    explicit SCgGroupBox(const QString &title, QGraphicsItem *parent = 0);
	~SCgGroupBox();

	//! @copydoc QGroupBox::title
	QString title() const;
	//! @copydoc QGroupBox::setTitle
	void setTitle(const QString &title);
	//! @copydoc QGroupBox::alignment
	Qt::Alignment alignment() const;
	//! @copydoc QGroupBox::setAlignment
	void setAlignment(int alignment);
	//! @copydoc QGroupBox::minimumSizeHint
	QSize minimumSizeHint() const;
	//! @copydoc QGroupBox::isFlat
	bool isFlat() const;
	//! @copydoc QGroupBox::setFlat
	void setFlat(bool flat);
	//! @copydoc QGroupBox::isCheckable
	bool isCheckable() const;
	//! @copydoc QGroupBox::setCheckable
	void setCheckable(bool checkable);
	//! @copydoc QGroupBox::isChecked
	bool isChecked() const;

public slots:
	//! @copydoc QGroupBox::setChecked
	void setChecked(bool checked);

signals:
    //! @copydoc QGroupBox::clicked
    void clicked(bool checked = false);
    //! @copydoc QGroupBox::toggled
    void toggled(bool);

protected:
    /*! Setup native widget and configure it
      * @param nativeWidget Pointer to native widget (QGroupBox)
      */
    void setNativeWidget(QGroupBox *nativeWidget);

    //! Return pointer to native widget
    QGroupBox * nativeWidget() const;
};
//------------------------------------------------------------------------------
#endif // SCGGROUPBOX_H
