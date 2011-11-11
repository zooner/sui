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

#ifndef SCGTEXTEDIT_H
#define SCGTEXTEDIT_H

#include <QGraphicsProxyWidget>

class QTextEdit;

class SCgTextEdit : public QGraphicsProxyWidget
{
    Q_OBJECT
public:
    explicit SCgTextEdit(QGraphicsItem *parent = 0);
    virtual ~SCgTextEdit();

    //! @copydoc QTextEdit::toPlainText
    QString toPlainText() const;

    //! @copydoc QTextEdit::toHtml
    QString toHtml() const;

protected:
    /*! Setup native widget and configure it
      * @param nativeWidget Pointer to native widget (QTextEdit)
      */
    void setNativeWidget(QTextEdit *nativeWidget);

    //! Return pointer to native widget
    QTextEdit* nativeWidget() const;

signals:
    //! @copydoc QTextEdit::selectionChanged
    void selectionChanged();
    //! @copydoc QTextEdit::textChanged
    void textChanged();

public slots:
    //! @copydoc QTextEdit::append
    void append(const QString &text);
    //! @copydoc QTextEdit::clear
    void clear();
    //! @copydoc QTextEdit::copy
    void copy();
    //! @copydoc QTextEdit::cut
    void cut();
    //! @copydoc QTextEdit::insertHtml
    void insertHtml(const QString &text);
    //! @copydoc QTextEdit::insertPlainText
    void insertPlainText(const QString &text);
    //! @copydoc QTextEdit::paste
    void paste();
    //! @copydoc QTextEdit::redo
    void redo();
    //! @copydoc QTextEdit::selectAll
    void selectAll();
    //! @copydoc QTextEdit::setAlignment
    void setAlignment(Qt::Alignment a);
    //! @copydoc QTextEdit::setHtml
    void setHtml(const QString & text);
    //! @copydoc QTextEdit::setPlainText
    void setPlainText(const QString & text);
    //! @copydoc QTextEdit::setText
    void setText(const QString & text);
    //! @copydoc QTextEdit::undo
    void undo();
};

#endif // SCGTEXTEDIT_H
