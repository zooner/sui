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

#ifndef SCGTRANSLATEGWFTOSC_H
#define SCGTRANSLATEGWFTOSC_H

#include "interfaces/UiComponents.h"
#include <QObject>

class SCgObjectInfo;

/*! Translator from gwf format into sc-code
  */
class SCgTranslateGWFToSc : public QObject,
                            public UiTranslatorExt2ScInterface
{
    Q_OBJECT
    Q_INTERFACES(UiTranslatorExt2ScInterface)
public:
    explicit SCgTranslateGWFToSc(QObject *parent = 0);

protected:
    //! @copydoc UiTranslatorExt2ScInterface::translate
    bool translate(QIODevice &device, ScMemoryInterface *memory, const ScUri &set);

    /*! Clear output set. Delete old translated sc-structure
      * @param set ScUri of sc-set that need to be cleared
      */
    void clearSet(const ScUri &set);

    /*! Resolve object by it info
      * @param objInfo Pointer to object info, that need to be resolved
      * @return Return ScUri of resolved sc-element
      */
    ScUri resolveObject(SCgObjectInfo *objInfo);

private:
    //! Map that converts local id into sc-uri
    typedef QMap<QString, ScUri> idToScUri;
    idToScUri mIdToScUri;
    //! List of translated objects
    ScUriList mTranslatedObjects;
    //! Map that convert scg type alias into sc-type
    typedef QMap<QString, ScElementType> TypeAliasToScType;
    TypeAliasToScType mTypeAliasToScType;
    //! Pointer to used sc-memory interface
    ScMemoryInterface *mScMemory;

signals:

public slots:

};


/*! GWF to sc translator factory
  */
class SCgTranslateGWFToScFactory : public QObject,
                                    public UiComponentFactoryInterface
{
    Q_OBJECT
    Q_INTERFACES(UiComponentFactoryInterface)
public:
    explicit SCgTranslateGWFToScFactory(QObject *parent);
    virtual ~SCgTranslateGWFToScFactory ();

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

#endif // SCGTRANSLATEGWFTOSC_H
