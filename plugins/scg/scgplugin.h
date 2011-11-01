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

#ifndef SCGPLUGIN_H
#define SCGPLUGIN_H

#include "interfaces/UiPlugins.h"

class SCgPlugin : public QObject,
                    public UiPluginInterface
{
    Q_OBJECT
    Q_INTERFACES(UiPluginInterface)

public:
    explicit SCgPlugin();
    virtual ~SCgPlugin();

    //! Get pointer to root inteface
    static UiRootInterface* rootInterface();

private:
    //! Pointer to root interface
    static UiRootInterface *mRootInterface;

protected:
    //! @copydoc UiPluginInterface::name
    const QString& name() const;
    //! @copydoc UiPluginInterface::version
    const QString& version() const;
    //! @copydoc UiPluginInterface::interfaces
    const QList<QObject*>& interfaces() const;
    //! @copydoc UiPluginInterface::initialize
    void initialize(UiRootInterface *root);
    //! @copydoc UiPluginInterface::shutdown
    void shutdown();

private:
    //! List of interfaces that provides plugin
    QList<QObject*> mInterfaces;
};


#endif // SCGPLUGIN_H
