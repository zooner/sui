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
#include "scgmainwindow.h"
#include "scgmainwindowscene.h"
#include "scgmainwindowinputhandler.h"
#include "scgplugin.h"
#include "interfaces/UiRoot.h"

#include <QUndoStack>
#include <QAction>
#include <QApplication>
#include <QGraphicsView>
//#include <QGLWidget>

SCgMainWindow::SCgMainWindow(QObject *parent) :
    QObject(parent),
    mView(0),
    mScene(0),
    mInputHandler(0)
{
    mView = new QGraphicsView();
    mInputHandler = new SCgMainWindowInputHandler(mView);
    mScene = new SCgMainWindowScene(mInputHandler, mView);

    mView->setCacheMode(QGraphicsView::CacheBackground);//CacheBackground);
    mView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    mView->setRenderHint(QPainter::Antialiasing);
    mView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    mView->setResizeAnchor(QGraphicsView::AnchorViewCenter);
    mView->setOptimizationFlag(QGraphicsView::DontAdjustForAntialiasing);
    mView->setDragMode(QGraphicsView::RubberBandDrag);
    mView->setAcceptDrops(true);
    mView->setSceneRect(-1024, -1024, 2048, 2048);

//    mView->setViewport(new QGLWidget());
//    mView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    mView->setScene(mScene);

    initializeActions();

    mView->show();
}

void SCgMainWindow::initializeActions()
{
    QUndoStack* undoStack = mScene->undoStack();

    QAction* actionRedo = undoStack->createRedoAction(mScene);
    actionRedo->setShortcut(QKeySequence::Redo);
//    actionRedo->setShortcutContext(Qt::WidgetShortcut);

    QAction* actionUndo = undoStack->createUndoAction(mScene);
    actionUndo->setShortcut(QKeySequence::Undo);
//    actionUndo->setShortcutContext(Qt::WidgetShortcut);

    QAction* actionDelete = new QAction("Delete", mScene);
    actionDelete->setShortcut(QKeySequence::Delete);
    connect(actionDelete, SIGNAL(triggered()), mInputHandler, SLOT(deleteSelected()));
    actionDelete->setShortcutContext(Qt::WidgetShortcut);

    QAction* actionDeleteJustContour = new QAction("Delete just contour", mScene);
    actionDeleteJustContour->setShortcut( QKeySequence(tr("Backspace")) );
    connect(actionDeleteJustContour, SIGNAL(triggered()), mInputHandler, SLOT(deleteJustContour()));
    actionDeleteJustContour->setShortcutContext(Qt::WidgetShortcut);

    mView->addAction(actionDeleteJustContour);
    mView->addAction(actionDelete);
    mView->addAction(actionRedo);
    mView->addAction(actionUndo);
}

void SCgMainWindow::initTypeConvert()
{
    mAliasToScElementTypeMap["pair/const/pos/-/orient"] = ScElementType(ScArcMain | ScConst | ScPos);
    mAliasToScElementTypeMap["pair/const/neg/-/orient"] = ScElementType(ScArcMain | ScConst | ScNeg);
    mAliasToScElementTypeMap["pair/const/fuz/-/orient"] = ScElementType(ScArcMain | ScConst);
    mAliasToScElementTypeMap["pair/const/pos/temp/orient"] = ScElementType(ScArcMain | ScConst | ScPos);
    mAliasToScElementTypeMap["pair/const/neg/temp/orient"] = ScElementType(ScArcMain | ScConst | ScNeg | ScTemp);
    mAliasToScElementTypeMap["pair/const/fuz/temp/orient"] = ScElementType(ScArcMain | ScConst | ScTemp);
    mAliasToScElementTypeMap["pair/const/-/-/-"] = ScElementType(ScEdgeCommon | ScConst);
    mAliasToScElementTypeMap["pair/const/-/-/orient"] = ScElementType(ScArcCommon | ScConst);

    mAliasToScElementTypeMap["pair/var/pos/-/orient"] = ScElementType(ScArcMain | ScVar | ScPos);
    mAliasToScElementTypeMap["pair/var/neg/-/orient"] = ScElementType(ScArcMain | ScVar | ScNeg);
    mAliasToScElementTypeMap["pair/var/fuz/-/orient"] = ScElementType(ScArcMain | ScVar);
    mAliasToScElementTypeMap["pair/var/pos/temp/orient"] = ScElementType(ScArcMain | ScVar | ScPos | ScTemp);
    mAliasToScElementTypeMap["pair/var/neg/temp/orient"] = ScElementType(ScArcMain | ScVar | ScNeg | ScTemp);
    mAliasToScElementTypeMap["pair/var/fuz/temp/orient"] = ScElementType(ScArcMain | ScVar | ScTemp);
    mAliasToScElementTypeMap["pair/var/-/-/-"] = ScElementType(ScEdgeCommon | ScVar);
    mAliasToScElementTypeMap["pair/var/-/-/orient"] = ScElementType(ScArcCommon | ScVar);

    mAliasToScElementTypeMap["pair/meta/pos/-/orient"] = ScElementType(ScArcMain | ScMeta | ScPos);
    mAliasToScElementTypeMap["pair/meta/neg/-/orient"] = ScElementType(ScArcMain | ScMeta | ScNeg);
    mAliasToScElementTypeMap["pair/meta/fuz/-/orient"] = ScElementType(ScArcMain | ScMeta);
    mAliasToScElementTypeMap["pair/meta/pos/temp/orient"] = ScElementType(ScArcMain | ScMeta | ScPos | ScTemp);
    mAliasToScElementTypeMap["pair/meta/neg/temp/orient"] = ScElementType(ScArcMain | ScMeta | ScNeg | ScTemp);
    mAliasToScElementTypeMap["pair/meta/fuz/temp/orient"] = ScElementType(ScArcMain | ScMeta | ScTemp);
    mAliasToScElementTypeMap["pair/meta/-/-/-"] = ScElementType(ScEdgeCommon | ScMeta);
    mAliasToScElementTypeMap["pair/meta/-/-/orient"] = ScElementType(ScArcCommon | ScMeta);

    // revert map
    AliasToScElementTypeMap::iterator it;
    for (it = mAliasToScElementTypeMap.begin(); it != mAliasToScElementTypeMap.end(); ++it)
        mScElementTypeToAliasMap[it.value()] = it.key();
}

SCgMainWindow::~SCgMainWindow()
{
    delete mInputHandler;
    delete mScene;
    delete mView;
}

bool SCgMainWindow::isOpened() const
{
    return true;
}

QWidget* SCgMainWindow::widget() const
{
    return mView;
}

void SCgMainWindow::showObjects(const ScUriList &objects)
{
    QMap<ScUri, SCgVisualObject*> uri2obj;
    ScUri uri;
    foreach(uri, objects)
        uri2obj[uri] = resolveUri(uri);
}

void SCgMainWindow::hideObjects(const ScUriList &objects)
{

}

bool SCgMainWindow::isObjectVisible(const ScUri &uri) const
{
    return false;
}

SCgVisualObject* SCgMainWindow::resolveUri(const ScUri &uri)
{
    // trying to find scg-object with uri
    SCgObjectList list;
//    if (SCgVisualObject::objectsByUri(uri, list))
//        return list.first();    //! FIXME: need to resolve situation, when we have more than one scg-object in list

//    UiRootInterface *root = SCgPlugin::rootInterface();

//    ScMemoryInterface *memory = root->scMemory();
//    SCgVisualObject *res = 0;

//    // get element type and create scg-object
//    ScElementType type = memory->get_el_type(uri);

//    // create new scg-object
//    if (type.check(ScNode))
//    {
//        // check if it a command
//        if (isCommand(uri))
//        {
//            SCgVisualControl *control = new SCgVisualControl();
//            mScene->addItem(control);

//            res = control;
//        }else
//        {
//            SCgVisualNode *node = new SCgVisualNode();
//            node->setTypeAlias(resolveTypeAlias(uri));
//            mScene->addItem(node);

//            res = node;
//        }
//    }else
//        if (type.check(ScArcMask))
//        {

//        }else
//            if (type.check(ScLink))
//            {

//            }

//    // setup identifier
//    QString idtf_value = root->scHelper()->stringIdtf(uri, root->currentLanguage());
//    if (!idtf_value.isEmpty())
//        res->setIdtfValue(idtf_value);

    return 0;
}

QString SCgMainWindow::resolveTypeAlias(const ScUri &uri)
{
    ScElementType type = SCgPlugin::rootInterface()->scMemory()->get_el_type(uri);
    QString res;

    Q_ASSERT(type.isValid());

    if (type.check(ScNode))
    {
        res = "node/";

        if (type.check(ScConst))
            res += "const/";
        else if (type.check(ScVar))
            res += "var/";
        else if (type.check(ScMeta))
            res += "meta/";

        //! TODO: struct types
        res += "general_node"; /// temporary
    }else if (type.check(ScLink))
    {

    }else
    {
        ScElementTypeToAliasMap::iterator it = mScElementTypeToAliasMap.find(type);
        if (it != mScElementTypeToAliasMap.end())
            return it.value();
        else
            SuiExcept(SuiExceptionItemNotFound,
                      QString("Can't find alias for type: %1").arg(type.toString()),
                      "QString SCgMainWindow::resolveTypeAlias(const ScUri &uri)");
    }

    return res;
}

bool SCgMainWindow::isCommand(const ScUri &uri) const
{
    ScHelperInterface *helper = SCgPlugin::rootInterface()->scHelper();

    return helper->checkInclusion(uri, helper->keynode("/ui/command/atom")) ||
            helper->checkInclusion(uri, helper->keynode("/ui/command/noatom"));
}


/// -------------------
/// ----- Factory -----
/// -------------------
SCgMainWindowFactory::SCgMainWindowFactory(QObject *parent) :
    QObject(parent)
{

}

SCgMainWindowFactory::~SCgMainWindowFactory()
{
}

QObject* SCgMainWindowFactory::createInstance()
{
    return new SCgMainWindow(this);
}

UiComponentType SCgMainWindowFactory::type() const
{
    return UiComponentMainWindow;
}

const ScUriList& SCgMainWindowFactory::formats() const
{
    return mFormats;
}
