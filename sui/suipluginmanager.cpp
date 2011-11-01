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

#include "suiprecompiled.h"
#include "suipluginmanager.h"

#include <QDir>

#include "interfaces/UiComponents.h"
#include "suiroot.h"

suiPluginManager::suiPluginManager(QObject *parent) :
    QObject(parent)
{
}

suiPluginManager::~suiPluginManager()
{
    unloadAllPlugins();
}

void suiPluginManager::loadPlugin(const QString &fileName)
{
    qDebug() << "Load plugin: " << fileName;

    if (mPluginLoaders.find(fileName) != mPluginLoaders.end())
        SuiExcept(SuiExceptionDuplicateItem,
                  QString("Plugin '%1' already loaded").arg(fileName),
                  "void suiPluginManager::loadPlugin(const QString &fileName)");

    QPluginLoader *loader = new QPluginLoader(fileName, this);

    if (!loader->load())
    {
        qDebug() << loader->errorString();
        SuiExcept(SuiExceptionInternalError,
                  QString("Can't load plugin '%1'").arg(fileName),
                  "void suiPluginManager::loadPlugin(const QString &fileName)");
    }

    // process instances
    UiPluginInterface *plugInterface = qobject_cast<UiPluginInterface*>(loader->instance());
    if (plugInterface != 0)
    {
        mPluginLoaders[fileName] = loader;
        processLoadPlugin(plugInterface);
    }else
        SuiExcept(SuiExceptionInternalError,
                  QString("There are no plugin interface in '%1'").arg(fileName),
                  "void suiPluginManager::loadPlugin(const QString &fileName)");
}

void suiPluginManager::unloadPlugin(const QString &fileName)
{
    qDebug() << "Unload plugin: " << fileName;

    if (mPluginLoaders.find(fileName) == mPluginLoaders.end())
        SuiExcept(SuiExceptionItemNotFound,
                  QString("Plugin '%1' doesn't loaded").arg(fileName),
                  "void suiPluginManager::unloadPlugin(const QString &fileName)");

    QMap<QString, QPluginLoader*>::iterator it = mPluginLoaders.find(fileName);
    QPluginLoader *loader = it.value();

    UiPluginInterface *plugInterface = qobject_cast<UiPluginInterface*>(loader->instance());
    if (!plugInterface) SuiExcept(SuiExceptionInternalError,
                                  QString("There are no plugin interface in '%1'").arg(fileName),
                                  "void suiPluginManager::unloadPlugin(const QString &fileName)");
    processUnloadPlugin(plugInterface);

    mPluginLoaders.erase(it);
    if (!loader->unload())  SuiExcept(SuiExceptionInternalError,
                                      QString("Can't unload plugin '%1'").arg(fileName),
                                      "void suiPluginManager::unloadPlugin(const QString &fileName)");
    delete loader;
}

void suiPluginManager::loadPluginsFromDir(const QString &dirPath, bool subdirs)
{
    if (!QDir(dirPath).exists()) SuiExcept(SuiExceptionFileNotFound,
                                           QString("Directory '%1' doesn't exist").arg(dirPath),
                                           "void suiPluginManager::loadPluginsFromDir(const QString &dirPath)");
    QDir pluginsDir(dirPath);

    QDirIterator dirIt(pluginsDir, subdirs ? QDirIterator::Subdirectories : QDirIterator::NoIteratorFlags);

    while (dirIt.hasNext())
    {
        QString fileName = dirIt.next();
        QFileInfo fionfo(fileName);

        // skip non file objetcs
        if (!fionfo.isFile()) continue;

        try
        {
            loadPlugin(fileName);
        }catch (...)
        {
            qDebug() << "Can't load plugin from " << pluginsDir.absoluteFilePath(fileName);
        }
    }
}

void suiPluginManager::unloadAllPlugins()
{
    QList<QString> plugNames = mPluginLoaders.keys();
    QString fileName;
    foreach(fileName, plugNames)
        unloadPlugin(fileName);
}

void suiPluginManager::processLoadPlugin(UiPluginInterface *pluginInterface)
{
    // iterate all interfaces in plugin and register them in managers
    Q_ASSERT(pluginInterface != 0);

    pluginInterface->initialize(suiRoot::getInstance());

    const QList<QObject*> &interfaces = pluginInterface->interfaces();
    QObject *_interface;
    foreach(_interface, interfaces)
    {
        // components factory
        UiComponentFactoryInterface *factory = qobject_cast<UiComponentFactoryInterface*>(_interface);
        if (factory != 0)
        {
            suiRoot::getInstance()->componentsManager()->registerFactory(factory);
            continue;
        }

        // sc-memory factory
        ScMemoryFactoryInterface *sc_factory = qobject_cast<ScMemoryFactoryInterface*>(_interface);
        if (sc_factory != 0)
        {
            suiRoot::getInstance()->registerScMemoryFactory(sc_factory);
            continue;
        }

        // interface can't be handled
        qWarning() << "Can't prosess interface: " << _interface;
    }
}

void suiPluginManager::processUnloadPlugin(UiPluginInterface *pluginInterface)
{
    // iterate all interfaces in plugin and unregister them in managers
    Q_ASSERT(pluginInterface);
    const QList<QObject*> &interfaces = pluginInterface->interfaces();
    QObject *_interface;
    foreach(_interface, interfaces)
    {
        // components fatory
        UiComponentFactoryInterface *factory = qobject_cast<UiComponentFactoryInterface*>(_interface);
        if (factory != 0)
        {
            suiRoot::getInstance()->componentsManager()->unregisterFactory(factory);
            continue;
        }

        // sc-memory factory
        ScMemoryFactoryInterface *sc_factory = qobject_cast<ScMemoryFactoryInterface*>(_interface);
        if (sc_factory != 0)
        {
            suiRoot::getInstance()->unregisterScMemoryFactory(sc_factory);
            continue;
        }

        // interface can't be handled
        qWarning() << "Can't process interface: " << _interface;
    }

    pluginInterface->shutdown();
}
