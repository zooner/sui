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

#ifndef ROOT_H
#define ROOT_H

#include <QtPlugin>
#include "ScHelper.h"
#include "UiCompManager.h"
#include "UiPlugins.h"

class QMainWindow;

/*! Root object. That object manage whole application.
  */
class UiRootInterface
{
public:
    virtual ~UiRootInterface() {}

    /*! Returns path to media folder
      */
    virtual const QString& mediaPath() const = 0;

    /*! Get main window size
      * @return Return main window size.
      */
    virtual QSize mainWindowSize() const = 0;

    /*! Returns pointer to sc-memory interface
      * @return Pointer to sc-memory interface
      */
    virtual ScMemoryInterface* scMemory() = 0;

    /*! Returns pointer to ScHelper interface.
      * @return Return pointer to sc helper interface.
      */
    virtual ScHelperInterface* scHelper() = 0;

    /*! Returns pointer to ScHelper created for specified ScMemoryInterface
      * @param memoryInterface Pointer to ScMemoryInterface that will be used for ScHelper work
      * @return Return pointer to created sc-helper
      * @note You will need to destroy created sc-helper manualy. For example you can use QScopedPointer.
      */
    virtual ScHelperInterface* scHelper(ScMemoryInterface *memoryInterface) = 0;

    /*! Register new sc-memory factory
      * @param factory Pointer to new sc-memory factory
      * @see UiRootInterface::unregisterScMemoryFactory
      */
    virtual void registerScMemoryFactory(ScMemoryFactoryInterface *factory) = 0;

    /*! Unregister sc-memory factory
      * @param factory Pointer to sc-memory factory, that need to be unregistered
      * @see UiRootInterface::registerScMemoryFactory
      */
    virtual void unregisterScMemoryFactory(ScMemoryFactoryInterface *factory) = 0;

    /*! Returns pointer to components memory interface
      * @return Return pointer to used components manager
      */
    virtual UiComponentManagerInterface* componentsManager() = 0;

    /*! Returns pointer to plugin manager
      */
    virtual UiPluginManagerInterface* pluginManager() = 0;

    /*! Get current language that used to work with user.
      * You can see used search template on image:
      * \image html current_language_templ.png
      * @return Return ScUri of sc-element that designate current language.
      */
    virtual const ScUri& currentLanguage() const = 0;

    /*! Translate data from sc-link into sc-code. Translated construction included into
      * specified set \p <output_set> see image.
      * \image html content_transl_templ.png
      * \image latex content_transl_templ.png
      * It iterate all translators that registered to specified data format,
      * and try to translate until one of them return true. If no one return true,
      * then it return false.
      * @param uri Uri of sc-link that contains data to translate.
      * @return Return true, if data translated; otherwise return false.
      */
   virtual bool translateDataToSc(const ScUri &uri) = 0;

    /*! Translate sc-contruction to sc-link data. Translated construction included into
      * specified content see image.
      * \image html content_transl_templ.png
      * \image latex content_transl_templ.png
      * It iterate all translators that registered to specified data format,
      * and try to translate until one of them return true. If no one return true,
      * then it return false.
      * @param uri ScUri of sc-set that contains sc-construction to translate.
      * @param link ScUri of sc-link that would be contain data
      * @return Return true, if data translated; otherwise return false.
      */
    virtual bool translateScToData(const ScUri &uri, const ScUri &link) = 0;

};

Q_DECLARE_INTERFACE(UiRootInterface,
                    "com.OSTIS.ui.UiRootInterface/1.0");


#endif // ROOT_H
