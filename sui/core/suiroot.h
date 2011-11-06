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

#ifndef SUIROOT_H
#define SUIROOT_H

#include "suiCore_global.h"
#include <QObject>
#include "interfaces/UiRoot.h"

class suiComponentsManager;
class suiPluginManager;
class suiScHelper;
class suiKpm;
class suiKnowBase;

class SUICORESHARED_EXPORT suiRoot : public QObject,
                                    public UiRootInterface
{
    Q_OBJECT
    Q_INTERFACES(UiRootInterface)
public:
    explicit suiRoot(QMainWindow *mainWindow, QObject *parent = 0);
    virtual ~suiRoot();
protected:
    //! Pointer to singleton instance
    static suiRoot *mInstance;
public:
    //! Return pointer to instance
    static suiRoot* getInstance();

public:
    //! @copydoc UiRootInterface::mediaPath
    const QString& mediaPath() const;
    //! @copydoc UiRootInterface::scMemory
    ScMemoryInterface* scMemory();
    //! @copydoc UiRootInterface::scHelper
    ScHelperInterface* scHelper();
    //! @copydoc UiRootInterface::scHelper(ScMemoryInterface*)
    ScHelperInterface* scHelper(ScMemoryInterface *memoryInterface);

    //! Return pointer to knwledge processing machine
    suiKpm* kpm();
    //! Return pointer to main sc window interface
    UiMainWindowInterface* mainScWindow();

    //! @copydoc UiRootInterface::currentLanguage
    ScUri currentLanguage() const;

    //! @copydoc UiRootInterface::mainWindowSize
    QSize mainWindowSize() const;
    //! @copydoc UiRootInterface::componentsManager
    UiComponentManagerInterface* componentsManager();
    //! @copydoc UiRootInterface::pluginManager
    UiPluginManagerInterface* pluginManager();
    //! @copydoc UiRootInterface::translateDataToSc
    bool translateDataToSc(const ScUri &uri);
    //! @copydoc UiRootInterface::translateScToData
    bool translateScToData(const ScUri &uri, const ScUri &link);

    //! @copydoc UiRootInterface::registerScMemoryFactory
    void registerScMemoryFactory(ScMemoryFactoryInterface *factory);
    //! @copydoc UiRootInterface::unregisterScMemoryFactory
    void unregisterScMemoryFactory(ScMemoryFactoryInterface *factory);

protected:
    QMainWindow *mMainWindow;
    //! Pointer to using components manager
    suiComponentsManager *mComponentsManager;
    //! Pointer to plugin manager
    suiPluginManager *mPluginManager;
    //! Pointer to current sc-memory interface
    ScMemoryInterface *mMemoryInterface;
    //! List of sc-memory factories
    QList<ScMemoryFactoryInterface*> mMemoryFactoriesList;
    //! Pointer to sc-helper implementation
    suiScHelper *mScHelper;
    //! Pointer to knowldge base control object
    suiKnowBase *mKnowBase;
    //! Pointer to knowledge processing machine
    suiKpm *mKpm;
    //! Pointer to main sc-window
    UiMainWindowInterface *mMainScWindow;
signals:

public slots:

};

#endif // SUIROOT_H
