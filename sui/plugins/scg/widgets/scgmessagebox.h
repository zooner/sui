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

#ifndef SCGMESSAGEBOX_H
#define SCGMESSAGEBOX_H

#include <QGraphicsProxyWidget>
#include <QMessageBox>
//------------------------------------------------------------------------------
class SCgMessageBox : public QGraphicsProxyWidget
{
	Q_OBJECT
    Q_FLAGS(StandardButton StandardButtons)

public:
    enum Icon {
        NoIcon = 0,
        Information = 1,
        Warning = 2,
        Critical = 3,
        Question = 4
    };

    enum ButtonRole {
        // keep this in sync with QDialogButtonBox::ButtonRole
        InvalidRole = -1,
        AcceptRole,
        RejectRole,
        DestructiveRole,
        ActionRole,
        HelpRole,
        YesRole,
        NoRole,
        ResetRole,
        ApplyRole,

        NRoles
    };

    enum StandardButton {
        // keep this in sync with QDialogButtonBox::StandardButton
        NoButton           = 0x00000000,
        Ok                 = 0x00000400,
        Save               = 0x00000800,
        SaveAll            = 0x00001000,
        Open               = 0x00002000,
        Yes                = 0x00004000,
        YesToAll           = 0x00008000,
        No                 = 0x00010000,
        NoToAll            = 0x00020000,
        Abort              = 0x00040000,
        Retry              = 0x00080000,
        Ignore             = 0x00100000,
        Close              = 0x00200000,
        Cancel             = 0x00400000,
        Discard            = 0x00800000,
        Help               = 0x01000000,
        Apply              = 0x02000000,
        Reset              = 0x04000000,
        RestoreDefaults    = 0x08000000,

        FirstButton        = Ok,                // internal
        LastButton         = RestoreDefaults,   // internal

        YesAll             = YesToAll,          // obsolete
        NoAll              = NoToAll,           // obsolete

        Default            = 0x00000100,        // obsolete
        Escape             = 0x00000200,        // obsolete
        FlagMask           = 0x00000300,        // obsolete
        ButtonMask         = ~FlagMask          // obsolete
    };

    typedef StandardButton Button;  // obsolete

    Q_DECLARE_FLAGS(StandardButtons, StandardButton)

    explicit SCgMessageBox(QGraphicsItem *parent = 0);
    SCgMessageBox(Icon icon, const QString &title, const QString &text,
                  StandardButtons buttons = NoButton, QGraphicsItem *parent = 0,
                  GraphicsItemFlags additionalFlags = 0);
    SCgMessageBox(const QString &title, const QString &text, Icon icon,
                  int button0, int button1, int button2,
                  QGraphicsItem *parent = 0, GraphicsItemFlags additionalFlags = 0);
	~SCgMessageBox();

	//! @copydoc QMessageBox::addButton
	void addButton(QAbstractButton *button, ButtonRole role);
	//! @copydoc QMessageBox::addButton
	QPushButton * addButton(const QString &text, ButtonRole role);
	//! @copydoc QMessageBox::addButton
    QPushButton * addButton(Button button);
	//! @copydoc QMessageBox::removeButton
	void removeButton(QAbstractButton *button);	
	//! @copydoc QMessageBox::open
    void open(QObject *receiver, const char *member);
	//! @copydoc QMessageBox::buttons
	QList<QAbstractButton * > buttons() const;
	//! @copydoc QMessageBox::buttonRole
	ButtonRole buttonRole(QAbstractButton *button) const;
	//! @copydoc QMessageBox::setStandardButtons
    void setStandardButtons(StandardButtons buttons);
	//! @copydoc QMessageBox::standardButtons
    StandardButtons standardButtons() const;
	//! @copydoc QMessageBox::standardButton
    Button standardButton(QAbstractButton *button) const;
	//! @copydoc QMessageBox::button
    QAbstractButton * button(Button which) const;
	//! @copydoc QMessageBox::defaultButton
	QPushButton * defaultButton() const;
	//! @copydoc QMessageBox::setDefaultButton
	void setDefaultButton(QPushButton *button);
	//! @copydoc QMessageBox::setDefaultButton
    void setDefaultButton(Button button);
	//! @copydoc QMessageBox::escapeButton
	QAbstractButton * escapeButton() const;
	//! @copydoc QMessageBox::setEscapeButton
	void setEscapeButton(QAbstractButton *button);
    //! @copydoc QMessageBox::setEscapeButton
    void setEscapeButton(Button button);
	//! @copydoc QMessageBox::clickedButton
	QAbstractButton * clickedButton() const;
	//! @copydoc QMessageBox::text
	QString text() const;
	//! @copydoc QMessageBox::setText
	void setText(const QString &text);
	//! @copydoc QMessageBox::icon
	Icon icon() const;
	//! @copydoc QMessageBox::setIcon
    void setIcon(Icon);
	//! @copydoc QMessageBox::iconPixmap
	QPixmap iconPixmap() const;
	//! @copydoc QMessageBox::setIconPixmap
	void setIconPixmap(const QPixmap &pixmap);
	//! @copydoc QMessageBox::textFormat
	Qt::TextFormat textFormat() const;
	//! @copydoc QMessageBox::setTextFormat
	void setTextFormat(Qt::TextFormat format);
	//! @copydoc QMessageBox::sizeHint
	QSize sizeHint() const;
    //! @copydoc QMessageBox::buttonText
    QString buttonText(int button) const;
	//! @copydoc QMessageBox::setButtonText
	void setButtonText(int button, const QString &text);
	//! @copydoc QMessageBox::informativeText
	QString informativeText() const;
	//! @copydoc QMessageBox::setInformativeText
	void setInformativeText(const QString &text);
    //! @copydoc QMessageBox::detailedText
    void setWindowTitle(const QString &title);
	//! @copydoc QMessageBox::setWindowModality
	void setWindowModality(Qt::WindowModality windowModality);

public slots:
	//! @copydoc QMessageBox::exec
	int exec();

signals:
	//! @copydoc QMessageBox::buttonClicked
	void buttonClicked(QAbstractButton *button);

protected:
    /*! Setup native widget and configure it
      * @param nativeWidget Pointer to native widget (QMessageBox)
      */
    void setNativeWidget(QMessageBox *nativeWidget);
    //! Return pointer to native widget
    QMessageBox * nativeWidget() const;

private:
    static QMessageBox::Icon convertToQIconType(Icon icon);
    static Icon convertToScgIconType(QMessageBox::Icon icon);
    static QMessageBox::ButtonRole convertToQButtonRoleType(ButtonRole buttonRole);
    static ButtonRole convertToScgButtonRoleType(QMessageBox::ButtonRole buttonRole);
    static QMessageBox::Button convertToQStandardButtonType(Button button);
    static Button convertToScgStandardButtonType(QMessageBox::Button button);
    static QMessageBox::StandardButtons convertToQStandardButtonsType(StandardButtons buttons);
    static StandardButtons convertToScgStandardButtonsType(QMessageBox::StandardButtons buttons);
};

Q_DECLARE_OPERATORS_FOR_FLAGS(SCgMessageBox::StandardButtons)
//------------------------------------------------------------------------------
#endif // SCGMESSAGEBOX_H
