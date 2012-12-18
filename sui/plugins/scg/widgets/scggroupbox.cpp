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
#include "scggroupbox.h"

#include <QGroupBox>
//------------------------------------------------------------------------------
SCgGroupBox::SCgGroupBox(QGraphicsItem *parent)
	: QGraphicsProxyWidget(parent)
{
    setNativeWidget(new QGroupBox);
}
//------------------------------------------------------------------------------
SCgGroupBox::SCgGroupBox(const QString &title, QGraphicsItem *parent)
	: QGraphicsProxyWidget(parent)
{
    setNativeWidget(new QGroupBox(title));
}
//------------------------------------------------------------------------------
SCgGroupBox::~SCgGroupBox()
{
    /*
    QGraphicsProxyWidget shares ownership with QWidget, so if either of the
    two widgets are destroyed, the other widget will be automatically destroyed
    as well.
    */
}
//------------------------------------------------------------------------------
QString SCgGroupBox::title() const
{
    return nativeWidget()->title();
}
//------------------------------------------------------------------------------
void SCgGroupBox::setTitle(const QString &title)
{
    nativeWidget()->setTitle(title);
}
//------------------------------------------------------------------------------
Qt::Alignment SCgGroupBox::alignment() const
{
    return nativeWidget()->alignment();
}
//------------------------------------------------------------------------------
void SCgGroupBox::setAlignment(int alignment)
{
    nativeWidget()->setAlignment(alignment);
}
//------------------------------------------------------------------------------
QSize SCgGroupBox::minimumSizeHint() const
{
    return nativeWidget()->minimumSizeHint();
}
//------------------------------------------------------------------------------
bool SCgGroupBox::isFlat() const
{
    return nativeWidget()->isFlat();
}
//------------------------------------------------------------------------------
void SCgGroupBox::setFlat(bool flat)
{
    nativeWidget()->setFlat(flat);
}
//------------------------------------------------------------------------------
bool SCgGroupBox::isCheckable() const
{
    return nativeWidget()->isCheckable();
}
//------------------------------------------------------------------------------
void SCgGroupBox::setCheckable(bool checkable)
{
    nativeWidget()->setCheckable(checkable);
}
//------------------------------------------------------------------------------
bool SCgGroupBox::isChecked() const
{
    return nativeWidget()->isChecked();
}
//------------------------------------------------------------------------------
void SCgGroupBox::setChecked(bool checked)
{
    nativeWidget()->setChecked(checked);
}
//------------------------------------------------------------------------------
void SCgGroupBox::setNativeWidget(QGroupBox *nativeWidget)
{
    Q_ASSERT(nativeWidget != 0);
    setWidget(nativeWidget);

    connect(nativeWidget, SIGNAL(clicked()), SIGNAL(clicked()));
    connect(nativeWidget, SIGNAL(toggled(bool)), SIGNAL(toggled(bool)));

    //! TODO: configure widget pallete and style
}
//------------------------------------------------------------------------------
QGroupBox * SCgGroupBox::nativeWidget() const
{
    return static_cast<QGroupBox *>(widget());
}
//------------------------------------------------------------------------------
