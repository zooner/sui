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
#include "suiroot.h"
#include <QMainWindow>
#include "suicomponentsmanager.h"
#include "suipluginmanager.h"
#include "suischelper.h"
#include "suiknowbase.h"
#include "suikpm.h"


suiRoot* suiRoot::mInstance = 0;

suiRoot* suiRoot::getInstance()
{
    Q_ASSERT(mInstance != 0);
    return mInstance;
}

suiRoot::suiRoot(QMainWindow *mainWindow, QObject *parent) :
    QObject(parent),
    mMainWindow(mainWindow),
    mComponentsManager(0),
    mPluginManager(0),
    mMemoryInterface(0),
    mScHelper(0),
    mKnowBase(0),
    mKpm(0),
    mMainScWindow(0)
{
    Q_ASSERT(mInstance == 0);
    mInstance = this;

    mComponentsManager = new suiComponentsManager(this);
    mPluginManager = new suiPluginManager(this);

    // load plugins
    QDir pluginsDir(qApp->applicationDirPath());
#if defined(Q_OS_WIN)
    pluginsDir.cdUp();
    pluginsDir.cd("plugins");
#elif defined(Q_OS_LINUX)
    pluginsDir.cd("plugins");
#endif    
    // load sc plugins
    mPluginManager->loadPluginsFromDir(pluginsDir.absoluteFilePath("sc"), false);
    scMemory()->initialize("./kb");

    // create knowledge base control class
    mKnowBase = new suiKnowBase(this);
    mKnowBase->initialize();
    // load ui plugins
    mPluginManager->loadPluginsFromDir(pluginsDir.absoluteFilePath("ui"), true);
    // load sources
    //mKnowBase->loadSources(QStringList());// << "../repo/sources");

    // create main window
    UiComponentFactoryInterfaceList res;
    Q_ASSERT(mComponentsManager->factoriesList(UiComponentMainWindow, res));
    mMainScWindow = qobject_cast<UiMainWindowInterface*>(res.front()->createInstance());
    mMainScWindow->setUri(mScHelper->keynode("/ui/main_window"));

    mMainWindow->setCentralWidget(mMainScWindow->widget());

    // initialize knowledge processing machine
    mKpm = new suiKpm(this);
    mKpm->initialize();


//    // show main menu on main window
//    ScUri main_menu = scHelper()->keynode("/ui/main_menu");
//    ScUri decomp = scHelper()->keynode("/etc/decomposition*");

//    // get set of child items for main menu
//    ScUriVector v;
//    if (scHelper()->searchOneShot(ScTemplate() << ScElementType(ScNode | ScConst)
//                              << ScElementType(ScArcCommon | ScConst)
//                              << main_menu
//                              << ScElementType(ScArcMain)
//                              << decomp, v))
//    {
//        ScUriList objects;
//        ScTemplate templ;
//        templ << v[0] << ScElementType(ScArcMain) << ScElementType(ScNode | ScConst);
//        ScSafeIterator it(scMemory(), templ);
//        while (!it.is_over())
//        {
//            objects << it.value(2);
//            it.next();
//        }

//        mMainScWindow->showObjects(objects);
//    }
}

suiRoot::~suiRoot()
{
    delete mMainScWindow;

    mKpm->shutdown();
    delete mKpm;

    mKnowBase->shutdown();
    delete mKnowBase;

    scMemory()->shutdown();

    delete mScHelper;
    delete mPluginManager;
    delete mComponentsManager;

    mInstance = 0;
}

const QString& suiRoot::mediaPath() const
{
    static QString path("./");
    return path;
}

ScMemoryInterface* suiRoot::scMemory()
{
    if (mMemoryInterface != 0)  return mMemoryInterface;
    // iterate all factories and trying to create sc-memory instance
    ScMemoryFactoryInterface *factory = 0;
    foreach (factory, mMemoryFactoriesList)
    {
        mMemoryInterface = factory->createInstance();
        if (mMemoryInterface != 0)  break;
    }

    return mMemoryInterface;
}

ScHelperInterface* suiRoot::scHelper()
{
    if (!mScHelper)
        mScHelper = new suiScHelper(scMemory(), this);

    return mScHelper;
}

ScHelperInterface* suiRoot::scHelper(ScMemoryInterface *memoryInterface)
{
    return new suiScHelper(memoryInterface, this);
}

suiKpm* suiRoot::kpm()
{
    return mKpm;
}

UiMainWindowInterface* suiRoot::mainScWindow()
{
    return mMainScWindow;
}

const ScUri& suiRoot::currentLanguage() const
{
    //! FIXME: get current language from memory
    return mScHelper->keynode("/language/english");
}

QSize suiRoot::mainWindowSize() const
{
    return mMainWindow->size();
}

UiComponentManagerInterface* suiRoot::componentsManager()
{
    return mComponentsManager;
}

UiPluginManagerInterface* suiRoot::pluginManager()
{
    return mPluginManager;
}

bool suiRoot::translateDataToSc(const ScUri &uri)
{
    Q_ASSERT(!uri.isEmpty());

    // check of specified uri is an sc-link
    // FIXME: uncomment when sc-core will support sc-links
    /*if (!(mMemoryInterface->get_el_type(uri) & ScLink)) SuiExcept(SuiExceptionInvalidParameters,
                                                                  QString("Uri='%1' isn't sc-link").arg(uri.value()),
                                                                  "bool suiRoot::translateDataToSc(const ScUri &uri)");
    */
    ScUriVector res;

    ScUri keynode_sem_eq = mScHelper->keynode("/etc/sem_eq*");
    // trying to find sem eq set, if it doesn't exist, then generate it
    ScTemplate templ;
    ScUri sem_eq_set;
    templ << ScElementType(ScNode | ScConst) << ScElementType(ScArcMain) << uri;
    ScSafeIterator scIt(mMemoryInterface, templ);
    while (!scIt.is_over())
    {
        // get relation arc
        ScUriVector v;
        if (mScHelper->searchOneShot(ScTemplate() << scIt.value(0)
                                            << ScElementType(ScArcCommon | ScConst)
                                            << ScElementType(ScNode | ScConst)
                                            << ScElementType(ScArcMain)
                                            << keynode_sem_eq, v))
        {
            sem_eq_set = v[2];
        }

        scIt.next();
    }

    // check if founded
    if (sem_eq_set.isEmpty())
    {
        mScHelper->genElStr(templ, res);
        sem_eq_set = res[0];
    }

    // setup type for set node
    ScUri tuple = mScHelper->keynode("/type/tuple");
    if (tuple.isEmpty()) SuiExcept(SuiExceptionItemNotFound,
                                   QString("Tuple keynode doesn't exist"),
                                   "bool suiRoot::translateDataToSc(const ScUri &uri)");

    templ.clear() << tuple << ScElementType(ScArcMain | ScConst) << res[0];
    if (!mScHelper->ensureExist(templ, res)) return false;

    templ.clear() << res[2]
                  << ScElementType(ScArcCommon | ScConst)
                  << ScElementType(ScNode | ScConst)
                  << ScElementType(ScArcMain)
                  << keynode_sem_eq;

    // build sem eq construction
    if (!mScHelper->ensureExist(templ, res)) return false;

    // output set = res[2]

    // get data format
    ScUri format = mScHelper->searchFormat(uri);
    if (format.isEmpty())   SuiExcept(SuiExceptionItemNotFound,
                                      QString("Can't get format node for element with uri='%1'").arg(uri.value()),
                                      "bool suiRoot::translateDataToSc(const ScUri &uri)");

    bool return_value = false;

    // find translators and try to translate
    UiComponentFactoryInterfaceList translators;
    if (mComponentsManager->factoriesList(UiComponentTransToSc, translators))
    {
        // open data device
        QIODevice *device = mMemoryInterface->open_content(uri);

        // iterate translators and try to translate
        UiComponentFactoryInterface *factory;
        foreach(factory, translators)
        {
            // skip translators that doesn't support that format
            if (!factory->formats().contains(format)) continue;

            UiTranslatorExt2ScInterface *trans = qobject_cast<UiTranslatorExt2ScInterface*>(factory->createInstance());
            if (trans == 0)
            {
                mMemoryInterface->close_content(device);
                SuiExcept(SuiExceptionInternalError,
                          "Can't cast object created by factory to UiTranslatorExt2ScInterface*",
                          "bool suiRoot::translateDataToSc(const ScUri &uri)");
            }

            if (trans->translate(*device, mMemoryInterface, res[2]))
            {
                return_value = true;
                delete trans;
                break;
            }
            delete trans;
        }

        mMemoryInterface->close_content(device);
    }

    return return_value;
}

bool suiRoot::translateScToData(const ScUri &uri, const ScUri &link)
{
    return false;
}

void suiRoot::registerScMemoryFactory(ScMemoryFactoryInterface *factory)
{
    Q_ASSERT(!mMemoryFactoriesList.contains(factory));
    mMemoryFactoriesList.append(factory);
}

void suiRoot::unregisterScMemoryFactory(ScMemoryFactoryInterface *factory)
{
    Q_ASSERT(mMemoryFactoriesList.contains(factory));
    mMemoryFactoriesList.removeOne(factory);
}
