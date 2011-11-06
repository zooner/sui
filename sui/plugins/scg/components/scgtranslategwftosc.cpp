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

#include "scgtranslategwftosc.h"
#include "scgplugin.h"
#include "interfaces/UiRoot.h"
#include "interfaces/ScHelper.h"

#include "formats/gwfobjectinforeader.h"
#include "visual/scgobjectsinfo.h"

SCgTranslateGWFToSc::SCgTranslateGWFToSc(QObject *parent) :
    QObject(parent),
    mScMemory(0)
{

    // create type conversion map
    mTypeAliasToScType["node/const/not_define"] = ScElementType(ScNode | ScConst);
    mTypeAliasToScType["node/const/general_node"] = ScElementType(ScNode | ScConst);
    mTypeAliasToScType["node/const/predmet"] = ScElementType(ScNode | ScConst);
    mTypeAliasToScType["node/const/nopredmet"] = ScElementType(ScNode | ScConst);
    mTypeAliasToScType["node/const/symmetry"] = ScElementType(ScNode | ScConst);
    mTypeAliasToScType["node/const/asymmetry"] = ScElementType(ScNode | ScConst);
    mTypeAliasToScType["node/const/attribute"] = ScElementType(ScNode | ScConst);
    mTypeAliasToScType["node/const/relation"] = ScElementType(ScNode | ScConst);
    mTypeAliasToScType["node/const/atom"] = ScElementType(ScNode | ScConst);
    mTypeAliasToScType["node/const/group"] = ScElementType(ScNode | ScConst);

    mTypeAliasToScType["node/var/not_define"] = ScElementType(ScNode | ScVar);
    mTypeAliasToScType["node/var/general_node"] = ScElementType(ScNode | ScVar);
    mTypeAliasToScType["node/var/predmet"] = ScElementType(ScNode | ScVar);
    mTypeAliasToScType["node/var/nopredmet"] = ScElementType(ScNode | ScVar);
    mTypeAliasToScType["node/var/symmetry"] = ScElementType(ScNode | ScVar);
    mTypeAliasToScType["node/var/asymmetry"] = ScElementType(ScNode | ScVar);
    mTypeAliasToScType["node/var/attribute"] = ScElementType(ScNode | ScVar);
    mTypeAliasToScType["node/var/relation"] = ScElementType(ScNode | ScVar);
    mTypeAliasToScType["node/var/atom"] = ScElementType(ScNode | ScVar);
    mTypeAliasToScType["node/var/group"] = ScElementType(ScNode | ScVar);

    mTypeAliasToScType["node/meta/not_define"] = ScElementType(ScNode | ScMeta);
    mTypeAliasToScType["node/meta/general_node"] = ScElementType(ScNode | ScMeta);
    mTypeAliasToScType["node/meta/predmet"] = ScElementType(ScNode | ScMeta);
    mTypeAliasToScType["node/meta/nopredmet"] = ScElementType(ScNode | ScMeta);
    mTypeAliasToScType["node/meta/symmetry"] = ScElementType(ScNode | ScMeta);
    mTypeAliasToScType["node/meta/asymmetry"] = ScElementType(ScNode | ScMeta);
    mTypeAliasToScType["node/meta/attribute"] = ScElementType(ScNode | ScMeta);
    mTypeAliasToScType["node/meta/relation"] = ScElementType(ScNode | ScMeta);
    mTypeAliasToScType["node/meta/atom"] = ScElementType(ScNode | ScMeta);
    mTypeAliasToScType["node/meta/group"] = ScElementType(ScNode | ScMeta);


    mTypeAliasToScType["pair/const/pos/-/orient"] = ScElementType(ScArcMain | ScConst | ScPos);
    mTypeAliasToScType["pair/const/neg/-/orient"] = ScElementType(ScArcMain | ScConst | ScNeg);
    mTypeAliasToScType["pair/const/fuz/-/orient"] = ScElementType(ScArcMain | ScConst);
    mTypeAliasToScType["pair/const/pos/temp/orient"] = ScElementType(ScArcMain | ScConst | ScPos | ScTemp);
    mTypeAliasToScType["pair/const/neg/temp/orient"] = ScElementType(ScArcMain | ScConst | ScNeg | ScTemp);
    mTypeAliasToScType["pair/const/fuz/temp/orient"] = ScElementType(ScArcMain | ScConst | ScTemp);
    mTypeAliasToScType["pair/const/-/-/-"] = ScElementType(ScEdgeCommon | ScConst);
    mTypeAliasToScType["pair/const/-/-/orient"] = ScElementType(ScArcCommon | ScConst);

    mTypeAliasToScType["pair/var/pos/-/orient"] = ScElementType(ScArcMain | ScVar | ScPos);
    mTypeAliasToScType["pair/var/neg/-/orient"] = ScElementType(ScArcMain | ScVar | ScNeg);
    mTypeAliasToScType["pair/var/fuz/-/orient"] = ScElementType(ScArcMain | ScVar);
    mTypeAliasToScType["pair/var/pos/temp/orient"] = ScElementType(ScArcMain | ScVar | ScPos | ScTemp);
    mTypeAliasToScType["pair/var/neg/temp/orient"] = ScElementType(ScArcMain | ScVar | ScNeg | ScTemp);
    mTypeAliasToScType["pair/var/fuz/temp/orient"] = ScElementType(ScArcMain | ScVar | ScTemp);
    mTypeAliasToScType["pair/var/-/-/-"] = ScElementType(ScEdgeCommon | ScVar);
    mTypeAliasToScType["pair/var/-/-/orient"] = ScElementType(ScArcCommon | ScVar);

    mTypeAliasToScType["pair/meta/pos/-/orient"] = ScElementType(ScArcMain | ScMeta | ScPos);
    mTypeAliasToScType["pair/meta/neg/-/orient"] = ScElementType(ScArcMain | ScMeta | ScNeg);
    mTypeAliasToScType["pair/meta/fuz/-/orient"] = ScElementType(ScArcMain | ScMeta);
    mTypeAliasToScType["pair/meta/pos/temp/orient"] = ScElementType(ScArcMain | ScMeta | ScPos | ScTemp);
    mTypeAliasToScType["pair/meta/neg/temp/orient"] = ScElementType(ScArcMain | ScMeta | ScNeg | ScTemp);
    mTypeAliasToScType["pair/meta/fuz/temp/orient"] = ScElementType(ScArcMain | ScMeta | ScTemp);
    mTypeAliasToScType["pair/meta/-/-/-"] = ScElementType(ScEdgeCommon | ScMeta);
    mTypeAliasToScType["pair/meta/-/-/orient"] = ScElementType(ScArcCommon | ScMeta);
}

bool SCgTranslateGWFToSc::translate(QIODevice &device, ScMemoryInterface *memory, const ScUri &set)
{
    mScMemory = memory;
    Q_ASSERT(mScMemory != 0);

    QScopedPointer<ScHelperInterface> helper(SCgPlugin::rootInterface()->scHelper(mScMemory));

    // read data from gwf
    GwfObjectInfoReader reader;
    if (!reader.read(&device))
    {
        qDebug() << "Error while translate to sc-code: " << reader.lastError();
        return false;
    }

    // iterate all objects and resolve them
    GwfObjectInfoReader::TypeToObjectsMap::const_iterator it;
    for (it = reader.objectsInfo().begin(); it != reader.objectsInfo().end(); ++it)
    {
        GwfObjectInfoReader::ObjectInfoList::const_iterator it_info;
        for (it_info = (*it).begin(); it_info != (*it).end(); ++it_info)
            resolveObject(*it_info);
    }

    // setup pair begin and end objects
    const GwfObjectInfoReader::ObjectInfoList &list = reader.objectsInfo()[SCgVisualObject::SCgPairType];
    GwfObjectInfoReader::ObjectInfoList::const_iterator it_info;
    for (it_info = list.begin(); it_info != list.end(); ++it_info)
    {
        SCgPairInfo *pairInfo = static_cast<SCgPairInfo*>(*it_info);
        ScUri pair_uri = mIdToScUri[pairInfo->id()];

        // get begin and end uri's
        ScUri b = mIdToScUri[pairInfo->beginObjectId()];
        ScUri e = mIdToScUri[pairInfo->endObjectId()];

        // setup begin and end
        mScMemory->set_beg(pair_uri, b);
        mScMemory->set_end(pair_uri, e);
    }

    // append objects into parent sets
    for (it = reader.objectsInfo().begin(); it != reader.objectsInfo().end(); ++it)
        for (it_info = (*it).begin(); it_info != (*it).end(); ++it_info)
        {
            SCgObjectInfo *info = *it_info;

            // check if object has a parent
            if (info->parentId() != "0" && !info->parentId().isEmpty())
            {
                ScUri uri = mIdToScUri[info->id()];
                ScUri parent = mIdToScUri[info->parentId()];

                // generate 5 elements construction to append new arc between parent and child into output set
                ScUriVector res;
                ScTemplate templ(parent,
                                 ScElementType(ScArcMain | ScConst | ScPos),
                                 uri,
                                 ScElementType(ScArcMain | ScConst | ScPos),
                                 set);

                if (!helper->genElStr(templ, res))
                    SuiExcept(SuiExceptionInternalError,
                              QString("Can't append '%1' into '%1'").arg(uri.value()).arg(parent.value()),
                              "bool SCgTranslateGWFToSc::translate(QIODevice &device, ScMemoryInterface *memory, const ScUri &set)");
            }
        }

    // append all translated objects into output set
    ScUriList::iterator it_list;
    ScUriVector res;
    for (it_list = mTranslatedObjects.begin(); it_list != mTranslatedObjects.end(); ++it_list)
        if (!helper->genElStr(ScTemplate() << set << ScElementType(ScArcMain | ScConst| ScPos) << *it_list, res))
            SuiExcept(SuiExceptionInternalError,
                      QString("Can't append '%1 into output set '%2").arg((*it_list).value()).arg(set.value()),
                      "bool SCgTranslateGWFToSc::translate(QIODevice &device, ScMemoryInterface *memory, const ScUri &set)");


    return true;
}

void SCgTranslateGWFToSc::clearSet(const ScUri &set)
{
    //! TODO: implement this function

    /* Destroy just objects, that haven't main identifier and
      * aren't linked with any object out of set
      */
}

ScUri SCgTranslateGWFToSc::resolveObject(SCgObjectInfo *objInfo)
{
    // trying to get in local id's
    idToScUri::iterator it = mIdToScUri.find(objInfo->id());
    if (it != mIdToScUri.end()) return it.value();

    // if object has identifier, than try to find it
    ScUri res = SCgPlugin::rootInterface()->scHelper()->findElementByMainIdentifier(objInfo->idtfValue());
    if (!res.isEmpty())
    {
        mIdToScUri[objInfo->id()] = res;
        if (!mTranslatedObjects.contains(res)) mTranslatedObjects.append(res);
        return res;
    }

    // if object wasn't found, then create it
    if (objInfo->objectType() == SCgVisualObject::SCgBusType)
    {
        SCgBusInfo *bus_info = static_cast<SCgBusInfo*>(objInfo);
        res = mIdToScUri[bus_info->ownerId()];
        mIdToScUri[objInfo->id()] = res;
    }else
    {
        ScElementType type = ScElementType(ScNode | ScConst);

        // just node and arc(pair) tags have type attribute
        if (objInfo->objectType() != SCgVisualObject::SCgContourType)
        {
            TypeAliasToScType::iterator itType = mTypeAliasToScType.find(objInfo->typeAlias());
            if (itType == mTypeAliasToScType.end())
                SuiExcept(SuiExceptionInternalError,
                          QString("Unsupported type alias '%1'").arg(objInfo->typeAlias()),
                          "ScUri SCgTranslateGWFToSc::resolveObject(SCgObjectInfo *objInfo)");
            type = itType.value();
        }
        res = mScMemory->gen_el(type);
        mIdToScUri[objInfo->id()] = res;
        mTranslatedObjects.append(res);
    }

    return res;
}


// ----- Factory -----
SCgTranslateGWFToScFactory::SCgTranslateGWFToScFactory(QObject *parent) :
    QObject(parent)
{
    ScHelperInterface *helper = SCgPlugin::rootInterface()->scHelper();
    mFormats.push_back(helper->appendFormatKeynode("gwf"));
}

SCgTranslateGWFToScFactory::~SCgTranslateGWFToScFactory()
{

}

QObject* SCgTranslateGWFToScFactory::createInstance()
{
    return new SCgTranslateGWFToSc(this);
}

UiComponentType SCgTranslateGWFToScFactory::type() const
{
    return UiComponentTransToSc;
}

const ScUriList& SCgTranslateGWFToScFactory::formats() const
{
    return mFormats;
}
