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
#include "scgmessagebox.h"

#include <QFlags>
//------------------------------------------------------------------------------
SCgMessageBox::SCgMessageBox(QGraphicsItem *parent)
	: QGraphicsProxyWidget(parent)
{
    setNativeWidget(new QMessageBox);
}
//------------------------------------------------------------------------------
SCgMessageBox::SCgMessageBox(Icon icon, const QString &title, const QString &text,
                             StandardButtons buttons, QGraphicsItem *parent,
                             GraphicsItemFlags additionalFlags)
    : QGraphicsProxyWidget(parent)
{
    setNativeWidget(new QMessageBox(convertToQIconType(icon), title, text, convertToQStandardButtonsType(buttons)));
    setFlags(flags() | additionalFlags);

    //! TRY: setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
}
//------------------------------------------------------------------------------
SCgMessageBox::SCgMessageBox(const QString &title, const QString &text, Icon icon,
                             int button0, int button1, int button2,
                             QGraphicsItem *parent, GraphicsItemFlags additionalFlags)
	: QGraphicsProxyWidget(parent)
{
    setNativeWidget(new QMessageBox(title, text, convertToQIconType(icon), button0, button1, button2));
    setFlags(flags() | additionalFlags);

    //! TRY: setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
}
//------------------------------------------------------------------------------
SCgMessageBox::~SCgMessageBox()
{
    /*
    QGraphicsProxyWidget shares ownership with QWidget, so if either of the
    two widgets are destroyed, the other widget will be automatically destroyed
    as well.
    */
}
//------------------------------------------------------------------------------
void SCgMessageBox::addButton(QAbstractButton *button, ButtonRole role)
{
    nativeWidget()->addButton(button, convertToQButtonRoleType(role));
}
//------------------------------------------------------------------------------
QPushButton * SCgMessageBox::addButton(const QString &text, ButtonRole role)
{
    return nativeWidget()->addButton(text, convertToQButtonRoleType(role));
}
//------------------------------------------------------------------------------
QPushButton * SCgMessageBox::addButton(Button button)
{
    return nativeWidget()->addButton(convertToQStandardButtonType(button));
}
//------------------------------------------------------------------------------
void SCgMessageBox::removeButton(QAbstractButton *button)
{
    nativeWidget()->removeButton(button);
}
//------------------------------------------------------------------------------
void SCgMessageBox::open(QObject *receiver, const char *member)
{
    return nativeWidget()->open(receiver, member);
}
//------------------------------------------------------------------------------
QList<QAbstractButton *> SCgMessageBox::buttons() const
{
    return nativeWidget()->buttons();
}
//------------------------------------------------------------------------------
SCgMessageBox::ButtonRole SCgMessageBox::buttonRole(QAbstractButton *button) const
{
    return convertToScgButtonRoleType(nativeWidget()->buttonRole(button));
}
//------------------------------------------------------------------------------
void SCgMessageBox::setStandardButtons(StandardButtons buttons)
{
    nativeWidget()->setStandardButtons(convertToQStandardButtonsType(buttons));
}
//------------------------------------------------------------------------------
SCgMessageBox::StandardButtons SCgMessageBox::standardButtons() const
{
    return convertToScgStandardButtonsType(nativeWidget()->standardButtons());
}
//------------------------------------------------------------------------------
SCgMessageBox::Button SCgMessageBox::standardButton(QAbstractButton *button) const
{
    return convertToScgStandardButtonType(nativeWidget()->standardButton(button));
}
//------------------------------------------------------------------------------
QAbstractButton * SCgMessageBox::button(Button which) const
{
    return nativeWidget()->button(convertToQStandardButtonType(which));
}
//------------------------------------------------------------------------------
QPushButton * SCgMessageBox::defaultButton() const
{
    return nativeWidget()->defaultButton();
}
//------------------------------------------------------------------------------
void SCgMessageBox::setDefaultButton(QPushButton *button)
{
    nativeWidget()->setDefaultButton(button);
}
//------------------------------------------------------------------------------
void SCgMessageBox::setDefaultButton(Button button)
{
    nativeWidget()->setDefaultButton(convertToQStandardButtonType(button));
}
//------------------------------------------------------------------------------
QAbstractButton * SCgMessageBox::escapeButton() const
{
    return nativeWidget()->escapeButton();
}
//------------------------------------------------------------------------------
void SCgMessageBox::setEscapeButton(QAbstractButton *button)
{
    nativeWidget()->setEscapeButton(button);
}
//------------------------------------------------------------------------------
void SCgMessageBox::setEscapeButton(Button button)
{
    nativeWidget()->setEscapeButton(convertToQStandardButtonType(button));
}
//------------------------------------------------------------------------------
QAbstractButton * SCgMessageBox::clickedButton() const
{
    return nativeWidget()->clickedButton();
}
//------------------------------------------------------------------------------
QString SCgMessageBox::text() const
{
    return nativeWidget()->text();
}
//------------------------------------------------------------------------------
void SCgMessageBox::setText(const QString &text)
{
    nativeWidget()->setText(text);
}
//------------------------------------------------------------------------------
SCgMessageBox::Icon SCgMessageBox::icon() const
{
    return convertToScgIconType(nativeWidget()->icon());
}
//------------------------------------------------------------------------------
void SCgMessageBox::setIcon(Icon icon)
{
    nativeWidget()->setIcon(convertToQIconType(icon));
}
//------------------------------------------------------------------------------
QPixmap SCgMessageBox::iconPixmap() const
{
    return nativeWidget()->iconPixmap();
}
//------------------------------------------------------------------------------
void SCgMessageBox::setIconPixmap(const QPixmap &pixmap)
{
    nativeWidget()->setIconPixmap(pixmap);
}
//------------------------------------------------------------------------------
Qt::TextFormat SCgMessageBox::textFormat() const
{
    return nativeWidget()->textFormat();
}
//------------------------------------------------------------------------------
void SCgMessageBox::setTextFormat(Qt::TextFormat format)
{
    nativeWidget()->setTextFormat(format);
}
//------------------------------------------------------------------------------
QSize SCgMessageBox::sizeHint() const
{
    return nativeWidget()->sizeHint();
}
//------------------------------------------------------------------------------
QString SCgMessageBox::buttonText(int button) const
{
    return nativeWidget()->buttonText(button);
}
//------------------------------------------------------------------------------
void SCgMessageBox::setButtonText(int button, const QString &text)
{
    nativeWidget()->setButtonText(button, text);
}
//------------------------------------------------------------------------------
QString SCgMessageBox::informativeText() const
{
    return nativeWidget()->informativeText();
}
//------------------------------------------------------------------------------
void SCgMessageBox::setInformativeText(const QString &text)
{
    nativeWidget()->setInformativeText(text);
}
//------------------------------------------------------------------------------
void SCgMessageBox::setWindowTitle(const QString &title)
{
    return nativeWidget()->setWindowTitle(title);
}
//------------------------------------------------------------------------------
void SCgMessageBox::setWindowModality(Qt::WindowModality windowModality)
{
    nativeWidget()->setWindowModality(windowModality);
}
//------------------------------------------------------------------------------
int SCgMessageBox::exec()
{
    return nativeWidget()->exec();
}
//------------------------------------------------------------------------------
void SCgMessageBox::setNativeWidget(QMessageBox *nativeWidget)
{
    Q_ASSERT(nativeWidget != 0);
    setWidget(nativeWidget);

    connect(nativeWidget, SIGNAL(buttonClicked(QAbstractButton *)), SIGNAL(buttonClicked(QAbstractButton *)));

    //! TODO: configure widget pallete and style
}
//------------------------------------------------------------------------------
QMessageBox * SCgMessageBox::nativeWidget() const
{
    return static_cast<QMessageBox *>(widget());
}
//------------------------------------------------------------------------------
QMessageBox::Icon SCgMessageBox::convertToQIconType(Icon icon)
{
    switch (icon) {
    case NoIcon:
        return QMessageBox::NoIcon;
    case Information:
        return QMessageBox::Information;
    case Warning:
        return QMessageBox::Warning;
    case Critical:
        return QMessageBox::Critical;
    case Question:
        return QMessageBox::Question;
    }
}
//------------------------------------------------------------------------------
SCgMessageBox::Icon SCgMessageBox::convertToScgIconType(QMessageBox::Icon icon)
{
    switch (icon) {
    case QMessageBox::NoIcon:
        return NoIcon;
    case QMessageBox::Information:
        return Information;
    case QMessageBox::Warning:
        return Warning;
    case QMessageBox::Critical:
        return Critical;
    case QMessageBox::Question:
        return Question;
    }
}
//------------------------------------------------------------------------------
QMessageBox::ButtonRole SCgMessageBox::convertToQButtonRoleType(ButtonRole buttonRole)
{
    switch (buttonRole) {
    case InvalidRole:
        return QMessageBox::InvalidRole;
    case AcceptRole:
        return QMessageBox::AcceptRole;
    case RejectRole:
        return QMessageBox::RejectRole;
    case DestructiveRole:
        return QMessageBox::DestructiveRole;
    case ActionRole:
        return QMessageBox::ActionRole;
    case HelpRole:
        return QMessageBox::HelpRole;
    case YesRole:
        return QMessageBox::YesRole;
    case NoRole:
        return QMessageBox::NoRole;
    case ResetRole:
        return QMessageBox::ResetRole;
    case ApplyRole:
        return QMessageBox::ApplyRole;

    case NRoles:
        return QMessageBox::NRoles;
    }
}
//------------------------------------------------------------------------------
SCgMessageBox::ButtonRole SCgMessageBox::convertToScgButtonRoleType(QMessageBox::ButtonRole buttonRole)
{
    switch (buttonRole) {
    case QMessageBox::InvalidRole:
        return InvalidRole;
    case QMessageBox::AcceptRole:
        return AcceptRole;
    case QMessageBox::RejectRole:
        return RejectRole;
    case QMessageBox::DestructiveRole:
        return DestructiveRole;
    case QMessageBox::ActionRole:
        return ActionRole;
    case QMessageBox::HelpRole:
        return HelpRole;
    case QMessageBox::YesRole:
        return YesRole;
    case QMessageBox::NoRole:
        return NoRole;
    case QMessageBox::ResetRole:
        return ResetRole;
    case QMessageBox::ApplyRole:
        return ApplyRole;

    case QMessageBox::NRoles:
        return NRoles;
    }
}
//------------------------------------------------------------------------------
QMessageBox::Button SCgMessageBox::convertToQStandardButtonType(Button button)
{
    switch (button) {
    case NoButton:
        return QMessageBox::NoButton;
    case Ok:
        return QMessageBox::Ok;
    case Save:
        return QMessageBox::Save;
    case SaveAll:
        return QMessageBox::SaveAll;
    case Open:
        return QMessageBox::Open;
    case Yes:
        return QMessageBox::Yes;
    case YesToAll:
        return QMessageBox::YesToAll;
    case No:
        return QMessageBox::No;
    case NoToAll:
        return QMessageBox::NoToAll;
    case Abort:
        return QMessageBox::Abort;
    case Retry:
        return QMessageBox::Retry;
    case Ignore:
        return QMessageBox::Ignore;
    case Close:
        return QMessageBox::Close;
    case Cancel:
        return QMessageBox::Cancel;
    case Discard:
        return QMessageBox::Discard;
    case Help:
        return QMessageBox::Help;
    case Apply:
        return QMessageBox::Apply;
    case Reset:
        return QMessageBox::Reset;
    case RestoreDefaults:
        return QMessageBox::RestoreDefaults;

    case Default:
        return QMessageBox::Default;
    case Escape:
        return QMessageBox::Escape;
    case FlagMask:
        return QMessageBox::FlagMask;
    case ButtonMask:
        return QMessageBox::ButtonMask;
    }
}
//------------------------------------------------------------------------------
SCgMessageBox::Button SCgMessageBox::convertToScgStandardButtonType(QMessageBox::Button button)
{
    switch (button) {
    case QMessageBox::NoButton:
        return NoButton;
    case QMessageBox::Ok:
        return Ok;
    case QMessageBox::Save:
        return Save;
    case QMessageBox::SaveAll:
        return SaveAll;
    case QMessageBox::Open:
        return Open;
    case QMessageBox::Yes:
        return Yes;
    case QMessageBox::YesToAll:
        return YesToAll;
    case QMessageBox::No:
        return No;
    case QMessageBox::NoToAll:
        return NoToAll;
    case QMessageBox::Abort:
        return Abort;
    case QMessageBox::Retry:
        return Retry;
    case QMessageBox::Ignore:
        return Ignore;
    case QMessageBox::Close:
        return Close;
    case QMessageBox::Cancel:
        return Cancel;
    case QMessageBox::Discard:
        return Discard;
    case QMessageBox::Help:
        return Help;
    case QMessageBox::Apply:
        return Apply;
    case QMessageBox::Reset:
        return Reset;
    case QMessageBox::RestoreDefaults:
        return RestoreDefaults;

    case QMessageBox::Default:
        return Default;
    case QMessageBox::Escape:
        return Escape;
    case QMessageBox::FlagMask:
        return FlagMask;
    case QMessageBox::ButtonMask:
        return ButtonMask;
    }
}
//------------------------------------------------------------------------------
QMessageBox::StandardButtons SCgMessageBox::convertToQStandardButtonsType(StandardButtons buttons)
{
    QMessageBox::StandardButtons qButtons;
    if (buttons.testFlag(NoButton)) {
        qButtons |= QMessageBox::NoButton;
    }
    if (buttons.testFlag(Ok)) {
        qButtons |= QMessageBox::Ok;
    }
    if (buttons.testFlag(Save)) {
        qButtons |= QMessageBox::Save;
    }
    if (buttons.testFlag(SaveAll)) {
        qButtons |= QMessageBox::SaveAll;
    }
    if (buttons.testFlag(Open)) {
        qButtons |= QMessageBox::Open;
    }
    if (buttons.testFlag(Yes)) {
        qButtons |= QMessageBox::Yes;
    }
    if (buttons.testFlag(YesToAll)) {
        qButtons |= QMessageBox::YesToAll;
    }
    if (buttons.testFlag(No)) {
        qButtons |= QMessageBox::No;
    }
    if (buttons.testFlag(NoToAll)) {
        qButtons |= QMessageBox::NoToAll;
    }
    if (buttons.testFlag(Abort)) {
        qButtons |= QMessageBox::Abort;
    }
    if (buttons.testFlag(Retry)) {
        qButtons |= QMessageBox::Retry;
    }
    if (buttons.testFlag(Ignore)) {
        qButtons |= QMessageBox::Ignore;
    }
    if (buttons.testFlag(Close)) {
        qButtons |= QMessageBox::Close;
    }
    if (buttons.testFlag(Cancel)) {
        qButtons |= QMessageBox::Cancel;
    }
    if (buttons.testFlag(Discard)) {
        qButtons |= QMessageBox::Discard;
    }
    if (buttons.testFlag(Help)) {
        qButtons |= QMessageBox::Help;
    }
    if (buttons.testFlag(Apply)) {
        qButtons |= QMessageBox::Apply;
    }
    if (buttons.testFlag(Reset)) {
        qButtons |= QMessageBox::Reset;
    }
    if (buttons.testFlag(RestoreDefaults)) {
        qButtons |= QMessageBox::RestoreDefaults;
    }

    if (buttons.testFlag(Default)) {
        qButtons |= QMessageBox::Default;
    }
    if (buttons.testFlag(Escape)) {
        qButtons |= QMessageBox::Escape;
    }
    if (buttons.testFlag(FlagMask)) {
        qButtons |= QMessageBox::FlagMask;
    }
    if (buttons.testFlag(ButtonMask)) {
        qButtons |= QMessageBox::ButtonMask;
    }


    return qButtons;
}
//------------------------------------------------------------------------------
SCgMessageBox::StandardButtons SCgMessageBox::convertToScgStandardButtonsType(QMessageBox::StandardButtons buttons)
{
    StandardButtons scgButtons;
    if (buttons.testFlag(QMessageBox::NoButton)) {
        scgButtons |= NoButton;
    }
    if (buttons.testFlag(QMessageBox::Ok)) {
        scgButtons |= Ok;
    }
    if (buttons.testFlag(QMessageBox::Save)) {
        scgButtons |= Save;
    }
    if (buttons.testFlag(QMessageBox::SaveAll)) {
        scgButtons |= SaveAll;
    }
    if (buttons.testFlag(QMessageBox::Open)) {
        scgButtons |= Open;
    }
    if (buttons.testFlag(QMessageBox::Yes)) {
        scgButtons |= Yes;
    }
    if (buttons.testFlag(QMessageBox::YesToAll)) {
        scgButtons |= YesToAll;
    }
    if (buttons.testFlag(QMessageBox::No)) {
        scgButtons |= No;
    }
    if (buttons.testFlag(QMessageBox::NoToAll)) {
        scgButtons |= NoToAll;
    }
    if (buttons.testFlag(QMessageBox::Abort)) {
        scgButtons |= Abort;
    }
    if (buttons.testFlag(QMessageBox::Retry)) {
        scgButtons |= Retry;
    }
    if (buttons.testFlag(QMessageBox::Ignore)) {
        scgButtons |= Ignore;
    }
    if (buttons.testFlag(QMessageBox::Close)) {
        scgButtons |= Close;
    }
    if (buttons.testFlag(QMessageBox::Cancel)) {
        scgButtons |= Cancel;
    }
    if (buttons.testFlag(QMessageBox::Discard)) {
        scgButtons |= Discard;
    }
    if (buttons.testFlag(QMessageBox::Help)) {
        scgButtons |= Help;
    }
    if (buttons.testFlag(QMessageBox::Apply)) {
        scgButtons |= Apply;
    }
    if (buttons.testFlag(QMessageBox::Reset)) {
        scgButtons |= Reset;
    }
    if (buttons.testFlag(QMessageBox::RestoreDefaults)) {
        scgButtons |= RestoreDefaults;
    }

    if (buttons.testFlag(QMessageBox::Default)) {
        scgButtons |= Default;
    }
    if (buttons.testFlag(QMessageBox::Escape)) {
        scgButtons |= Escape;
    }
    if (buttons.testFlag(QMessageBox::FlagMask)) {
        scgButtons |= FlagMask;
    }
    if (buttons.testFlag(QMessageBox::ButtonMask)) {
        scgButtons |= ButtonMask;
    }


    return scgButtons;
}
//------------------------------------------------------------------------------
