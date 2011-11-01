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

#ifndef PLUGINS_H
#define PLUGINS_H

#include <QtPlugin>

class UiRootInterface;

// ----- Interfaces -----
class UiPluginInterface
{
public:
    virtual ~UiPluginInterface() {}

    //! Returns plugin name
    virtual const QString& name() const = 0;
    //! Returns plugin version
    virtual const QString& version() const = 0;
    /*! Return list of all interfaces that realized in that plugin
      * @attention All interfaces need to be a QObject, and created with plugin interface as a parent object
      */
    virtual const QList<QObject*>& interfaces() const = 0;
    /*! Initialize plugin
      * @param root Pointer to root object
      */
    virtual void initialize(UiRootInterface *root) = 0;

    //! Shutdown plugin
    virtual void shutdown() = 0;
};

class UiPluginManagerInterface
{
public:
    virtual ~UiPluginManagerInterface() { }

    /*! Load plugin from specified file
      * @param fileName Name of plugin file for loading
      * @see UiPluginManagerInterface::unloadPlugin, UiPluginManagerInterface::loadPluginsFromDir
      */
    virtual void loadPlugin(const QString &fileName) = 0;

    /*! Unload specified plugin
      * @param fileName Plugin file name
      * @see UiPluginManagerInterface::loadPlugin, UiPluginManagerInterface::loadPluginsFromDir
      */
    virtual void unloadPlugin(const QString &fileName) = 0;

    /*! Unload all plugins
      */
    virtual void unloadAllPlugins() = 0;

    /*! Load plugins from specified directory
      * @param dirPath Path to plugins dircetory
      * @param subdirs Flag to load plugins from subdirectories
      * @see UiPluginManagerInterface::loadPlugin, UiPluginManagerInterface::unloadPlugin
      */
    virtual void loadPluginsFromDir(const QString &dirPath, bool subdirs) = 0;
};


Q_DECLARE_INTERFACE(UiPluginInterface,
                    "com.OSTIS.ui.UiPluginInterface/1.0")
Q_DECLARE_INTERFACE(UiPluginManagerInterface,
                    "com.OSTIS.ui.UiPluginManagerInterface/1.0")

#endif // PLUGINS_H
