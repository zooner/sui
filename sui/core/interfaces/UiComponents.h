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

#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <QtPlugin>
#include "ScMemory.h"
#include "UiObjects.h"

// ----- Component types -----
typedef enum
{
    UiComponentEditor = 0,
    UiComponentViewer,
    UiComponentTransToSc,
    UiComponentTransFromSc,
    UiComponentMainWindow
} UiComponentType;

typedef enum
{
    UiUnknown = 0,
    UiOk,
    UiErrorUnknownFormat
} UiReturnCode;

// ----- Interfaces ------
class UiViewerInterface : public ScWindowInterface
{
    Q_INTERFACES(ScObjectInterface)
public:
    virtual ~UiViewerInterface() {}

    /*! Set new data for view
      * @param device Pointer to input device for data reading.
      * Data for viewing need to be read from input device.
      * @return Return code. If it's equal to UiOk, then data passed into viewer without any errors;
      * otherwise return UiErrorXXX
      */
    virtual UiReturnCode setData(const QIODevice &device) = 0;
};

class UiEditorInterface : public ScWindowInterface
{
    Q_INTERFACES(ScObjectInterface)
public:
    virtual ~UiEditorInterface() {}

    /*! Get data from editor
      * @param device Pointer to output device for write into it.
      * Edited data need to written into output device.
      * @return Return code. If it's equal to UiOk, then data passed into editor without any errors;
      * otherwise return UiErrorXXX
      */
    virtual UiReturnCode data(QIODevice &device) = 0;
};

class UiTranslatorSc2ExtInterface : public ScObjectInterface
{
    Q_INTERFACES(ScObjectInterface)
public:
    virtual ~UiTranslatorSc2ExtInterface() {}

    /*! Translate sc-set into external data format
      * @param set Uri of sc-set that need to be translated
      * @param memory Pointer to sc-memory interface, that need to be used for translation
      * @param device IODevice for translated data writing
      * @return Return true if data translated from sc-core; otherwise return false.
      */
    virtual UiReturnCode translate(const ScUri &set, ScMemoryInterface *memory, QIODevice &device) = 0;
};

class UiTranslatorExt2ScInterface : public ScObjectInterface
{
    Q_INTERFACES(ScObjectInterface)
public:
    virtual ~UiTranslatorExt2ScInterface() {}

    /*! Translate external data into sc-construction
      * @param device IODevice for external data reading
      * @param memory Pointer to sc-memory interface, that need to be used for translation
      * @param set Uri of ouput sc-set. Whole translated construction will be added into it
      * @return Return true if data translated into sc-core; otherwise return false.
      */
    virtual bool translate(QIODevice &device, ScMemoryInterface *memory, const ScUri &set) = 0;
};

class UiMainWindowInterface : public ScWindowInterface
{
    Q_INTERFACES(ScWindowInterface)
public:
    virtual ~UiMainWindowInterface() {}

    /*! Show sc-objects on main window
      * @param objects List of sc-object uri's that need to be showed
      */
    virtual void showObjects(const ScUriList &objects) = 0;

    /*! Hide sc-objects in main window
      * @param objects List of sc-object uri's that need to be hidden
      */
    virtual void hideObjects(const ScUriList &objects) = 0;

    /*! Check if sc-object is showed in main window
      * @param uri ScUri of sc-object that need to be checked
      * @return Return true, if object is showed; otherwise return false
      */
    virtual bool isObjectVisible(const ScUri &uri) const = 0;
};

// ----- Factories ----
class UiComponentFactoryInterface : public ScObjectInterface
{
    Q_INTERFACES(ScObjectInterface)
public:
    virtual ~UiComponentFactoryInterface() {}

    /*! Return pointer to created component instance
      * @return Pointer to created component instance
      */

    virtual QObject* createInstance() = 0;
    /*! Return components type
      * @return components type
      */
    virtual UiComponentType type() const = 0;

    /*! Get supported formats
      * @return Return list with ScUri's of sc-element that designate supported formats
      */
    virtual const ScUriList& formats() const = 0;
};

typedef QList<UiComponentFactoryInterface*> UiComponentFactoryInterfaceList;


Q_DECLARE_INTERFACE(UiViewerInterface,
                    "com.OSTIS.ui.ViewerInterface/1.0")
Q_DECLARE_INTERFACE(UiEditorInterface,
                    "com.OSTIS.ui.EditorInterface/1.0")
Q_DECLARE_INTERFACE(UiTranslatorSc2ExtInterface,
                    "com.OSTIS.ui.TranslatorSc2ExtInterface/1.0")
Q_DECLARE_INTERFACE(UiTranslatorExt2ScInterface,
                    "com.OSTIS.ui.TranslatorExt2ScInterface/1.0")
Q_DECLARE_INTERFACE(UiMainWindowInterface,
                    "com.OSTIS.ui.MainWindowInterface/1.0")
Q_DECLARE_INTERFACE(UiComponentFactoryInterface,
                    "com.OSTIS.ui.UiComponentFactoryInterface")

#endif // COMPONENTS_H
