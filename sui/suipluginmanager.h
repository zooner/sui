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

#ifndef SUIPLUGINMANAGER_H
#define SUIPLUGINMANAGER_H

#include <QObject>
#include <QMap>


#include "interfaces/UiPlugins.h"

class QPluginLoader;

class suiPluginManager : public QObject,
                         public UiPluginManagerInterface
{
    Q_OBJECT
    Q_INTERFACES(UiPluginManagerInterface)
public:
    explicit suiPluginManager(QObject *parent = 0);
    virtual ~suiPluginManager();

    //! @copydoc UiPluginManagerInterface::loadPlugin
    void loadPlugin(const QString &fileName);
    //! @copydoc UiPluginManagerInterface::unloadPlugin
    void unloadPlugin(const QString &fileName);
    //! @copydoc UiPluginManagerInterface::loadPluginsFromDir
    void loadPluginsFromDir(const QString &dirPath, bool subdirs);
    //! @copydoc UiPluginManagerInterface::unloadAllPlugins
    void unloadAllPlugins();

    //! Get all available in plugin interfaces and register them in system
    void processLoadPlugin(UiPluginInterface *pluginInterface);
    //! Get all available in plugin interfaces and unregister them
    void processUnloadPlugin(UiPluginInterface *pluginInterface);


protected:
    //! Map of all loaders that used to load plugins
    QMap<QString, QPluginLoader*> mPluginLoaders;

signals:

public slots:

};

#endif // SUIPLUGINMANAGER_H
