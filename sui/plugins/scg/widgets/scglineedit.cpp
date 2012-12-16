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
#include "scglineedit.h"
//------------------------------------------------------------------------------
SCgLineEdit::SCgLineEdit(QGraphicsItem *parent)
	: QGraphicsProxyWidget(parent)
{
    setNativeWidget(new QLineEdit);
}
//------------------------------------------------------------------------------
SCgLineEdit::SCgLineEdit(const QString &contents, QGraphicsItem *parent)
	: QGraphicsProxyWidget(parent)
{
    setNativeWidget(new QLineEdit(contents));
}
//------------------------------------------------------------------------------
SCgLineEdit::~SCgLineEdit()
{
    /*
    QGraphicsProxyWidget shares ownership with QWidget, so if either of the
    two widgets are destroyed, the other widget will be automatically destroyed
    as well.
    */
}
//------------------------------------------------------------------------------
QString SCgLineEdit::text() const
{
    return nativeWidget()->text();
}
//------------------------------------------------------------------------------
QString SCgLineEdit::displayText() const
{
    return nativeWidget()->displayText();
}
//------------------------------------------------------------------------------
QString SCgLineEdit::placeholderText() const
{
    return nativeWidget()->placeholderText();
}
//------------------------------------------------------------------------------
void SCgLineEdit::setPlaceholderText(const QString &placeholderText)
{
    nativeWidget()->setPlaceholderText(placeholderText);
}
//------------------------------------------------------------------------------
int SCgLineEdit::maxLength() const
{
    return nativeWidget()->maxLength();
}
//------------------------------------------------------------------------------
void SCgLineEdit::setMaxLength(int maxLength)
{
    nativeWidget()->setMaxLength(maxLength);
}
//------------------------------------------------------------------------------
void SCgLineEdit::setFrame(bool b)
{
    nativeWidget()->setFrame(b);
}
//------------------------------------------------------------------------------
bool SCgLineEdit::hasFrame() const
{
    return nativeWidget()->hasFrame();
}
//------------------------------------------------------------------------------
SCgLineEdit::EchoMode SCgLineEdit::echoMode() const
{
    return convertToScgEchoModeType(nativeWidget()->echoMode());
}
//------------------------------------------------------------------------------
void SCgLineEdit::setEchoMode(EchoMode echoMode)
{
    nativeWidget()->setEchoMode(convertToQEchoModeType(echoMode));
}
//------------------------------------------------------------------------------
bool SCgLineEdit::isReadOnly() const
{
    return nativeWidget()->isReadOnly();
}
//------------------------------------------------------------------------------
void SCgLineEdit::setReadOnly(bool b)
{
    nativeWidget()->setReadOnly(b);
}
//------------------------------------------------------------------------------
#ifndef QT_NO_VALIDATOR
void SCgLineEdit::setValidator(const QValidator *validator)
{
    return nativeWidget()->setValidator(validator);
}
//------------------------------------------------------------------------------
const QValidator * SCgLineEdit::validator() const
{
    return nativeWidget()->validator();
}
#endif
//------------------------------------------------------------------------------
#ifndef QT_NO_COMPLETER
void SCgLineEdit::setCompleter(QCompleter *completer)
{
    return nativeWidget()->setCompleter(completer);
}
//------------------------------------------------------------------------------
QCompleter * SCgLineEdit::completer() const
{
    return nativeWidget()->completer();
}
#endif
//------------------------------------------------------------------------------
QSize SCgLineEdit::sizeHint() const
{
    return nativeWidget()->sizeHint();
}
//------------------------------------------------------------------------------
QSize SCgLineEdit::minimumSizeHint() const
{
    return nativeWidget()->minimumSizeHint();
}
//------------------------------------------------------------------------------
int SCgLineEdit::cursorPosition() const
{
    return nativeWidget()->cursorPosition();
}
//------------------------------------------------------------------------------
void SCgLineEdit::setCursorPosition(int cursorPosition)
{
    nativeWidget()->setCursorPosition(cursorPosition);
}
//------------------------------------------------------------------------------
int SCgLineEdit::cursorPositionAt(const QPoint &pos)
{
    return nativeWidget()->cursorPositionAt(pos);
}
//------------------------------------------------------------------------------
void SCgLineEdit::setAlignment(Qt::Alignment flag)
{
    nativeWidget()->setAlignment(flag);
}
//------------------------------------------------------------------------------
Qt::Alignment SCgLineEdit::alignment() const
{
    return nativeWidget()->alignment();
}
//------------------------------------------------------------------------------
void SCgLineEdit::cursorForward(bool mark, int steps)
{
    nativeWidget()->cursorForward(mark, steps);
}
//------------------------------------------------------------------------------
void SCgLineEdit::cursorBackward(bool mark, int steps)
{
    nativeWidget()->cursorBackward(mark, steps);
}
//------------------------------------------------------------------------------
void SCgLineEdit::cursorWordForward(bool mark)
{
    nativeWidget()->cursorWordForward(mark);
}
//------------------------------------------------------------------------------
void SCgLineEdit::cursorWordBackward(bool mark)
{
    nativeWidget()->cursorWordBackward(mark);
}
//------------------------------------------------------------------------------
void SCgLineEdit::backspace()
{
    nativeWidget()->backspace();
}
//------------------------------------------------------------------------------
void SCgLineEdit::del()
{
    nativeWidget()->del();
}
//------------------------------------------------------------------------------
void SCgLineEdit::home(bool mark)
{
    nativeWidget()->home(mark);
}
//------------------------------------------------------------------------------
void SCgLineEdit::end(bool mark)
{
    nativeWidget()->end(mark);
}
//------------------------------------------------------------------------------
bool SCgLineEdit::isModified() const
{
    return nativeWidget()->isModified();
}
//------------------------------------------------------------------------------
void SCgLineEdit::setModified(bool b)
{
    nativeWidget()->setModified(b);
}
//------------------------------------------------------------------------------
void SCgLineEdit::setSelection(int start, int length)
{
    nativeWidget()->setSelection(start, length);
}
//------------------------------------------------------------------------------
bool SCgLineEdit::hasSelectedText() const
{
    return nativeWidget()->hasSelectedText();
}
//------------------------------------------------------------------------------
QString SCgLineEdit::selectedText() const
{
    return nativeWidget()->selectedText();
}
//------------------------------------------------------------------------------
int SCgLineEdit::selectionStart() const
{
    return nativeWidget()->selectionStart();
}
//------------------------------------------------------------------------------
bool SCgLineEdit::isUndoAvailable() const
{
    return nativeWidget()->isUndoAvailable();
}
//------------------------------------------------------------------------------
bool SCgLineEdit::isRedoAvailable() const
{
    return nativeWidget()->isRedoAvailable();
}
//------------------------------------------------------------------------------
void SCgLineEdit::setDragEnabled(bool b)
{
    nativeWidget()->setDragEnabled(b);
}
//------------------------------------------------------------------------------
bool SCgLineEdit::dragEnabled() const
{
    return nativeWidget()->dragEnabled();
}
//------------------------------------------------------------------------------
void SCgLineEdit::setCursorMoveStyle(Qt::CursorMoveStyle style)
{
    nativeWidget()->setCursorMoveStyle(style);
}
//------------------------------------------------------------------------------
Qt::CursorMoveStyle SCgLineEdit::cursorMoveStyle() const
{
    return nativeWidget()->cursorMoveStyle();
}
//------------------------------------------------------------------------------
QString SCgLineEdit::inputMask() const
{
    return nativeWidget()->inputMask();
}
//------------------------------------------------------------------------------
void SCgLineEdit::setInputMask(const QString &inputMask)
{
    nativeWidget()->setInputMask(inputMask);
}
//------------------------------------------------------------------------------
bool SCgLineEdit::hasAcceptableInput() const
{
    return nativeWidget()->hasAcceptableInput();
}
//------------------------------------------------------------------------------
void SCgLineEdit::setTextMargins(int left, int top, int right, int bottom)
{
    nativeWidget()->setTextMargins(left, top, right, bottom);
}
//------------------------------------------------------------------------------
void SCgLineEdit::setTextMargins(const QMargins &margins)
{
    nativeWidget()->setTextMargins(margins);
}
//------------------------------------------------------------------------------
void SCgLineEdit::getTextMargins(int *left, int *top, int *right, int *bottom) const
{
    nativeWidget()->getTextMargins(left, top, right, bottom);
}
//------------------------------------------------------------------------------
QMargins SCgLineEdit::textMargins() const
{
    return nativeWidget()->textMargins();
}
//------------------------------------------------------------------------------
void SCgLineEdit::deselect()
{
    nativeWidget()->deselect();
}
//------------------------------------------------------------------------------
void SCgLineEdit::insert(const QString &newText)
{
    nativeWidget()->insert(newText);
}
//------------------------------------------------------------------------------
#ifndef QT_NO_CONTEXTMENU
QMenu * SCgLineEdit::createStandardContextMenu()
{
    return nativeWidget()->createStandardContextMenu();
}
#endif
//------------------------------------------------------------------------------
QVariant SCgLineEdit::inputMethodQuery(Qt::InputMethodQuery property) const
{
    return nativeWidget()->inputMethodQuery(property);
}
//------------------------------------------------------------------------------
bool SCgLineEdit::event(QEvent *e)
{
    return nativeWidget()->event(e);
}
//------------------------------------------------------------------------------
void SCgLineEdit::setText(const QString &text)
{
    nativeWidget()->setText(text);
}
//------------------------------------------------------------------------------
void SCgLineEdit::clear()
{
    nativeWidget()->clear();
}
//------------------------------------------------------------------------------
void SCgLineEdit::selectAll()
{
    nativeWidget()->selectAll();
}
//------------------------------------------------------------------------------
void SCgLineEdit::undo()
{
    nativeWidget()->undo();
}
//------------------------------------------------------------------------------
void SCgLineEdit::redo()
{
    nativeWidget()->redo();
}
//------------------------------------------------------------------------------
#ifndef QT_NO_CLIPBOARD
void SCgLineEdit::cut()
{
    return nativeWidget()->cut();
}
//------------------------------------------------------------------------------
void SCgLineEdit::copy() const
{
    nativeWidget()->copy();
}
//------------------------------------------------------------------------------
void SCgLineEdit::paste()
{
    nativeWidget()->paste();
}
#endif
//------------------------------------------------------------------------------
void SCgLineEdit::setNativeWidget(QLineEdit *nativeWidget)
{
    Q_ASSERT(nativeWidget != 0);
    setWidget(nativeWidget);

    connect(nativeWidget, SIGNAL(textChanged(QString)), SIGNAL(textChanged(QString)));
    connect(nativeWidget, SIGNAL(textEdited(QString)), SIGNAL(textEdited(QString)));
    connect(nativeWidget, SIGNAL(cursorPositionChanged(int,int)), SIGNAL(cursorPositionChanged(int,int)));
    connect(nativeWidget, SIGNAL(returnPressed()), SIGNAL(returnPressed()));
    connect(nativeWidget, SIGNAL(editingFinished()), SIGNAL(editingFinished()));
    connect(nativeWidget, SIGNAL(selectionChanged()), SIGNAL(selectionChanged()));

    //! TODO: configure widget pallete and style
}
//------------------------------------------------------------------------------
QLineEdit * SCgLineEdit::nativeWidget() const
{
    return static_cast<QLineEdit *>(widget());
}
//------------------------------------------------------------------------------
QLineEdit::EchoMode SCgLineEdit::convertToQEchoModeType(EchoMode echoMode)
{
    switch (echoMode) {
    case Normal:
        return QLineEdit::Normal;
    case NoEcho:
        return QLineEdit::NoEcho;
    case Password:
        return QLineEdit::Password;
    case PasswordEchoOnEdit:
        return QLineEdit::PasswordEchoOnEdit;
    }
}
//------------------------------------------------------------------------------
SCgLineEdit::EchoMode SCgLineEdit::convertToScgEchoModeType(QLineEdit::EchoMode echoMode)
{
    switch (echoMode) {
    case QLineEdit::Normal:
        return Normal;
    case QLineEdit::NoEcho:
        return NoEcho;
    case QLineEdit::Password:
        return Password;
    case QLineEdit::PasswordEchoOnEdit:
        return PasswordEchoOnEdit;
    }
}
//------------------------------------------------------------------------------
