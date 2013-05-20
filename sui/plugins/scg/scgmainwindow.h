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

#ifndef SCGMAINWINDOW_H
#define SCGMAINWINDOW_H

#include <QObject>
#include "interfaces/UiComponents.h"
#include "scgprerequest.h"

class QGraphicsView;
class SCgSceneBase;
class SCgMainWindowInputHandler;
class SCgView;

class SCgMainWindow : public QObject,
                        public UiMainWindowInterface
{
    Q_OBJECT
    Q_INTERFACES(UiMainWindowInterface)
public:
    explicit SCgMainWindow(QObject *parent = 0);
    virtual ~SCgMainWindow();

protected:
    //! @copydoc UiMainWindowInterface::isOpened
    bool isOpened() const;
    //! @copydoc UiMainWindowInterface::widget
    QWidget* widget() const;

    //! @copydoc UiMainWindowInterface::showObjects
    void showObjects(const ScUriList &objects);
    //! @copydoc UiMainWindowInterface::hideObjects
    void hideObjects(const ScUriList &objects);
    //! @copydoc UiMainWindowInterface::isObjectVisible
    bool isObjectVisible(const ScUri &uri) const;

private:
    /*! Resolve ScUri. Return scg-object assigned to ScUri.
      * At first it try to find SCg-object that already exist. If object
      * that designate specified \p uri doesn't exists, then it will be created
      * @param uri ScUri of visualized sc-element
      * @return Return pointer to sc.g-object, that designate sc-element with specified \p uri
      */
    SCgObject *resolveUri(const ScUri &uri);

    /*! Check if sc-element with specified \p uri is a command node
      * @param uri ScUri of sc-element for check
      * @return Return true, if sc-element with specified \p uri is a command node;
      * otherwise return false
      */
    bool isCommand(const ScUri &uri) const;

private:
    SCgMainWindowInputHandler *createInputHandler(QObject *parent);
    void initializeActions();

    //! Pointer to widget, that realize whole logic of window
    SCgView *mView;
    //! Pointer to used graphics scene
    SCgSceneBase *mScene;
    //! Pointer to input handler
    SCgMainWindowInputHandler *mInputHandler;
    /*! Map to get scg-elements by their uri's
      * That map used when we link any scg-pair object to begin and end
      */
    typedef QMap<ScUri, SCgObject*> ScUriToSCgObjectMap;
    ScUriToSCgObjectMap mUriToObject;

signals:

public slots:

};

class SCgMainWindowFactory : public QObject,
                                public UiComponentFactoryInterface
{
    Q_OBJECT
    Q_INTERFACES(UiComponentFactoryInterface)

public:
    explicit SCgMainWindowFactory(QObject *parent);
    virtual ~SCgMainWindowFactory();

protected:
    //! @copydoc UiComponentFactoryInterface::createInstance
    QObject* createInstance();
    //! @copydoc UiComponentFactoryInterface::type
    UiComponentType type() const;
    //! @copydoc UiComponentFactoryInterface::formats
    const ScUriList& formats() const;

private:
    //! List of supported formats
    ScUriList mFormats;
};

#endif // SCGMAINWINDOW_H
