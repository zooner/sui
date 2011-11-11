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
#include "scgtextedit.h"

#include <QGraphicsProxyWidget>
#include <QTextEdit>

SCgTextEdit::SCgTextEdit(QGraphicsItem *parent) :
    QGraphicsProxyWidget(parent)
{
    setNativeWidget(new QTextEdit());
}

SCgTextEdit::~SCgTextEdit()
{
}


QString SCgTextEdit::toPlainText() const
{
    return static_cast<QTextEdit*>(widget())->toPlainText();
}

QString SCgTextEdit::toHtml() const
{
    return static_cast<QTextEdit*>(widget())->toHtml();
}

void SCgTextEdit::setNativeWidget(QTextEdit *nativeWidget)
{
    Q_ASSERT(nativeWidget != 0);
    setWidget(nativeWidget);

    connect(nativeWidget, SIGNAL(selectionChanged()), this, SIGNAL(selectionChanged()));
    connect(nativeWidget, SIGNAL(textChanged()), this, SIGNAL(textChanged()));

    //! TODO: configure widget pallete and style
}

QTextEdit* SCgTextEdit::nativeWidget() const
{
    return static_cast<QTextEdit*>(widget());
}

void SCgTextEdit::append(const QString &text)
{
    static_cast<QTextEdit*>(widget())->append(text);
}

void SCgTextEdit::clear()
{
    static_cast<QTextEdit*>(widget())->clear();
}

void SCgTextEdit::copy()
{
    static_cast<QTextEdit*>(widget())->copy();
}

void SCgTextEdit::cut()
{
    static_cast<QTextEdit*>(widget())->cut();
}

void SCgTextEdit::insertHtml(const QString &text)
{
    static_cast<QTextEdit*>(widget())->insertHtml(text);
}

void SCgTextEdit::insertPlainText(const QString &text)
{
    static_cast<QTextEdit*>(widget())->insertPlainText(text);
}

void SCgTextEdit::paste()
{
    static_cast<QTextEdit*>(widget())->paste();
}

void SCgTextEdit::redo()
{
    static_cast<QTextEdit*>(widget())->redo();
}

void SCgTextEdit::selectAll()
{
    static_cast<QTextEdit*>(widget())->selectAll();
}

void SCgTextEdit::setAlignment(Qt::Alignment a)
{
    static_cast<QTextEdit*>(widget())->setAlignment(a);
}

void SCgTextEdit::setHtml(const QString & text)
{
    static_cast<QTextEdit*>(widget())->setHtml(text);
}

void SCgTextEdit::setPlainText(const QString & text)
{
    static_cast<QTextEdit*>(widget())->setPlainText(text);
}

void SCgTextEdit::setText(const QString & text)
{
    static_cast<QTextEdit*>(widget())->setText(text);
}

void SCgTextEdit::undo()
{
    static_cast<QTextEdit*>(widget())->undo();
}
