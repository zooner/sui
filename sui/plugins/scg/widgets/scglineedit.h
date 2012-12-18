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

#ifndef SCGLINEEDIT_H
#define SCGLINEEDIT_H

#include <QGraphicsProxyWidget>
#include <QLineEdit>


class QValidator;
class QCompleter;
//------------------------------------------------------------------------------
class SCgLineEdit : public QGraphicsProxyWidget
{
	Q_OBJECT

public:
    enum EchoMode {
        Normal,
        NoEcho,
        Password,
        PasswordEchoOnEdit
    };

    explicit SCgLineEdit(QGraphicsItem *parent = 0);
    explicit SCgLineEdit(const QString &contents, QGraphicsItem *parent = 0);
	~SCgLineEdit();

	//! @copydoc QLineEdit::text
	QString text() const;
	//! @copydoc QLineEdit::displayText
	QString displayText() const;
	//! @copydoc QLineEdit::placeholderText
	QString placeholderText() const;
	//! @copydoc QLineEdit::setPlaceholderText
    void setPlaceholderText(const QString &placeholderText);
	//! @copydoc QLineEdit::maxLength
	int maxLength() const;
	//! @copydoc QLineEdit::setMaxLength
    void setMaxLength(int maxLength);
	//! @copydoc QLineEdit::setFrame
    void setFrame(bool b);
	//! @copydoc QLineEdit::hasFrame
	bool hasFrame() const;
	//! @copydoc QLineEdit::echoMode
	EchoMode echoMode() const;
	//! @copydoc QLineEdit::setEchoMode
    void setEchoMode(EchoMode echoMode);
	//! @copydoc QLineEdit::isReadOnly
	bool isReadOnly() const;
	//! @copydoc QLineEdit::setReadOnly
    void setReadOnly(bool b);
#ifndef QT_NO_VALIDATOR
    //! @copydoc QLineEdit::setValidator
    void setValidator(const QValidator *validator);
	//! @copydoc QLineEdit::validator
	const QValidator * validator() const;
#endif
#ifndef QT_NO_COMPLETER
    //! @copydoc QLineEdit::setCompleter
    void setCompleter(QCompleter *completer);
	//! @copydoc QLineEdit::completer
	QCompleter * completer() const;
#endif

    //! @copydoc QLineEdit::sizeHint
    QSize sizeHint() const;
	//! @copydoc QLineEdit::minimumSizeHint
	QSize minimumSizeHint() const;
	//! @copydoc QLineEdit::cursorPosition
	int cursorPosition() const;
	//! @copydoc QLineEdit::setCursorPosition
    void setCursorPosition(int cursorPosition);
	//! @copydoc QLineEdit::cursorPositionAt
	int cursorPositionAt(const QPoint &pos);
	//! @copydoc QLineEdit::setAlignment
	void setAlignment(Qt::Alignment flag);
	//! @copydoc QLineEdit::alignment
	Qt::Alignment alignment() const;
	//! @copydoc QLineEdit::cursorForward
	void cursorForward(bool mark, int steps = 1);
	//! @copydoc QLineEdit::cursorBackward
	void cursorBackward(bool mark, int steps = 1);
	//! @copydoc QLineEdit::cursorWordForward
	void cursorWordForward(bool mark);
	//! @copydoc QLineEdit::cursorWordBackward
	void cursorWordBackward(bool mark);
	//! @copydoc QLineEdit::backspace
	void backspace();
	//! @copydoc QLineEdit::del
	void del();
	//! @copydoc QLineEdit::home
	void home(bool mark);
	//! @copydoc QLineEdit::end
	void end(bool mark);
	//! @copydoc QLineEdit::isModified
	bool isModified() const;
	//! @copydoc QLineEdit::setModified
    void setModified(bool b);
	//! @copydoc QLineEdit::setSelection
    void setSelection(int start, int length);
	//! @copydoc QLineEdit::hasSelectedText
	bool hasSelectedText() const;
	//! @copydoc QLineEdit::selectedText
	QString selectedText() const;
	//! @copydoc QLineEdit::selectionStart
	int selectionStart() const;
	//! @copydoc QLineEdit::isUndoAvailable
	bool isUndoAvailable() const;
	//! @copydoc QLineEdit::isRedoAvailable
	bool isRedoAvailable() const;
	//! @copydoc QLineEdit::setDragEnabled
	void setDragEnabled(bool b);
	//! @copydoc QLineEdit::dragEnabled
	bool dragEnabled() const;
	//! @copydoc QLineEdit::setCursorMoveStyle
	void setCursorMoveStyle(Qt::CursorMoveStyle style);
	//! @copydoc QLineEdit::cursorMoveStyle
	Qt::CursorMoveStyle cursorMoveStyle() const;
	//! @copydoc QLineEdit::inputMask
	QString inputMask() const;
	//! @copydoc QLineEdit::setInputMask
	void setInputMask(const QString &inputMask);
	//! @copydoc QLineEdit::hasAcceptableInput
	bool hasAcceptableInput() const;
	//! @copydoc QLineEdit::setTextMargins
	void setTextMargins(int left, int top, int right, int bottom);
	//! @copydoc QLineEdit::setTextMargins
	void setTextMargins(const QMargins &margins);
	//! @copydoc QLineEdit::getTextMargins
	void getTextMargins(int *left, int *top, int *right, int *bottom) const;
	//! @copydoc QLineEdit::textMargins
	QMargins textMargins() const;
	//! @copydoc QLineEdit::deselect
	void deselect();
	//! @copydoc QLineEdit::insert
    void insert(const QString & newText);
#ifndef QT_NO_CONTEXTMENU
    //! @copydoc QLineEdit::createStandardContextMenu
    QMenu * createStandardContextMenu();
#endif
    //! @copydoc QLineEdit::inputMethodQuery
    QVariant inputMethodQuery(Qt::InputMethodQuery property) const;
	//! @copydoc QLineEdit::event
	bool event(QEvent *);

public slots:
	//! @copydoc QLineEdit::setText
    void setText(const QString & text);
	//! @copydoc QLineEdit::clear
	void clear();
	//! @copydoc QLineEdit::selectAll
	void selectAll();
	//! @copydoc QLineEdit::undo
	void undo();
	//! @copydoc QLineEdit::redo
	void redo();
	//! @copydoc QLineEdit::cut
#ifndef QT_NO_CLIPBOARD
    void cut();
	//! @copydoc QLineEdit::copy
	void copy() const;
	//! @copydoc QLineEdit::paste
	void paste();
#endif

signals:
	//! @copydoc QLineEdit::textChanged
    void textChanged(const QString & text);
	//! @copydoc QLineEdit::textEdited
	void textEdited(const QString &);
	//! @copydoc QLineEdit::cursorPositionChanged
	void cursorPositionChanged(int, int);
	//! @copydoc QLineEdit::returnPressed
	void returnPressed();
	//! @copydoc QLineEdit::editingFinished
	void editingFinished();
	//! @copydoc QLineEdit::selectionChanged
	void selectionChanged();

protected:
    /*! Setup native widget and configure it
      * @param nativeWidget Pointer to native widget (QLineEdit)
      */
    void setNativeWidget(QLineEdit *nativeWidget);
    //! Return pointer to native widget
    QLineEdit * nativeWidget() const;

private:
    static QLineEdit::EchoMode convertToQEchoModeType(EchoMode echoMode);
    static EchoMode convertToScgEchoModeType(QLineEdit::EchoMode echoMode);
};
//------------------------------------------------------------------------------
#endif // SCGLINEEDIT_H
