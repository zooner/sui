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

#include "suischelper.h"
#include "suiknowbase.h"
#include <QBuffer>

suiScHelper::suiScHelper(ScMemoryInterface *memoryInterface, QObject *parent) :
    QObject(parent),
    mMemoryInterface(memoryInterface)
{
    Q_ASSERT(mMemoryInterface != 0);
}

suiScHelper::~suiScHelper()
{

}

ScUri suiScHelper::keynode(const QString &alias) const
{
    KeynodesMap::const_iterator it = mKeynodesMap.find(alias);

    if (it != mKeynodesMap.end()) return it.value();

    SuiExcept(SuiExceptionItemNotFound,
              QString("Can't find keynode with alias='%1'").arg(alias),
              "ScUri suiScHelper::keynode(const QString &alias) const");

    return ScUriEmpty;
}

void suiScHelper::appendKeynode(const ScUri &uri, const QString &alias)
{
    KeynodesMap::iterator it = mKeynodesMap.find(alias);

    if (it != mKeynodesMap.end())   SuiExcept(SuiExceptionDuplicateItem,
                                              QString("Keynode with alias %1 already exist").arg(alias),
                                              "void suiScHelper::appendKeynode(const ScUri &uri, const QString &alias)");

    mKeynodesMap[alias] = uri;
}

ScUri suiScHelper::appendFormatKeynode(const QString &formatName)
{
    KeynodesMap::iterator it = mKeynodesMap.find(QString("/ui/format/%1").arg(formatName));
    if (it != mKeynodesMap.end()) return it.value();

    ScUri res = mMemoryInterface->gen_el(ScElementType(ScNode | ScConst));
    // include it into formats set
    ScUriVector v;
    if (!genElStr(ScTemplate() << keynode("/ui/format") << ScElementType(ScArcMain) << res, v))
        SuiExcept(SuiExceptionInternalError,
                  QString("Can't include format '%1' into formats set").arg(formatName),
                  "ScUri suiScHelper::appendFormatKeynode(const QString &formatName)");
    appendKeynode(res, QString("/ui/format/%1").arg(formatName));

    return res;
}

void suiScHelper::removeKeynode(const QString &alias)
{
    KeynodesMap::iterator it = mKeynodesMap.find(alias);

    if (it == mKeynodesMap.end()) SuiExcept(SuiExceptionItemNotFound,
                                            QString("Keynode with alias %1 doesn't exist").arg(alias),
                                            "void suiScHelper::removeKeynode(const QString &alias)");

    mKeynodesMap.erase(it);
}

bool suiScHelper::hasKeynode(const QString &alias) const
{
    return mKeynodesMap.find(alias) != mKeynodesMap.end();
}

bool suiScHelper::appendTextIdtf(const ScUri &elem, const QString &idtf, bool is_main)
{
    // create buffer that contains text
    QBuffer buff;
    string2IODevice(buff, idtf);

    ScUri idtf_uri = ScUriEmpty;
    // try to find sc-link with same content
    ScUriList result;
    mMemoryInterface->find_content(buff, result);
    if (result.size() == 1)
        idtf_uri = result.first();
    else
    {
        idtf_uri = mMemoryInterface->gen_el(ScElementType(ScLink | ScConst));
        mMemoryInterface->set_content(idtf_uri, buff);
    }

    // setup new identifier
    return appendIdtf(elem, idtf_uri, is_main);
}

bool suiScHelper::appendIdtf(const ScUri &elem, const ScUri &idtf, bool is_main)
{
    Q_ASSERT(elem != ScUriEmpty && idtf != ScUriEmpty);

    // check if main idtf already exist
    ScUri nrel_idtf = keynode(key_nrel_identification);
    ScUri main_ = keynode(key_rrel_main);

    Q_ASSERT(nrel_idtf != ScUriEmpty && main_ != ScUriEmpty);

    // get identifiers set
    ScUriVector set;
    ScTemplate idtf_set_templ = ScTemplate(scParamType(ScNode | ScConst),
                                           scParamType(ScArcCommon | ScConst | ScPos),
                                           scParamUri(elem),
                                           scParamType(ScArcMain),
                                           scParamUri(nrel_idtf));
    if (ensureExist(idtf_set_templ, set))
    {
        if (is_main)
        {

            // trying to find and remove old main identifier
            ScUriVector main_res;
            ScTemplate main_templ = ScTemplate(scParamUri(set[0]),
                                               scParamType(ScArcMain),
                                               scParamType(ScLink),
                                               scParamType(ScArcMain),
                                               scParamUri(main_));
            if (searchOneShot(main_templ, main_res))
            {
                mMemoryInterface->erase_el(main_res[2]);
            }

            // setup new main identifier
            main_templ.set(2, scParamUri(idtf));
            if (!genElStr(main_templ, main_res)) return false;
        }
        ScUriVector idtf_res;
        // is not main identifier
        if (!genElStr(ScTemplate(scParamUri(set[0]),
                                 scParamType(ScArcMain),
                                 scParamUri(idtf)), idtf_res)) return false;

    } else return false;

    return false;
}

bool suiScHelper::removeTextIdtf(const ScUri &elem, const QString &idtf)
{
    return false;
}

bool suiScHelper::removeIdtf(const ScUri &elem, const ScUri &idtf)
{
    return false;
}

bool suiScHelper::allIdtfs(const ScUri &elem, ScUriVector &result) const
{
    if (elem.isEmpty()) SuiExcept(SuiExceptionInvalidParameters,
                                  "ScUir is empty",
                                  "bool suiScHelper::allIdtfs(const ScUri &elem, ScUriVector &result) const");

    result.clear();

    // get keynodes we need to work
    ScUri nrel_idtf = keynode(key_nrel_identification);

    // search idtfs set
    ScUriVector res_tmp;

   if (searchOneShot(ScTemplate() << ScElementType(ScNode | ScConst)
                                << ScElementType(ScArcCommon | ScConst | ScPos)
                                << elem
                                << ScElementType(ScArcMain)
                                << nrel_idtf
                     , res_tmp))
   {
       // search all output arcs
       ScTemplate templ = ScTemplate() << res_tmp[0]
                                       << ScElementType(ScArcMain)
                                       << ScElementType(ScNode);
       ScIteratorInterface *iter = mMemoryInterface->create_iterator(templ);
       while (!iter->is_over())
       {
           result.push_back(iter->value(2));
           iter->next();
       }
   }

   return !result.empty();
}

// FIXME
ScUri suiScHelper::findElementByMainIdentifier(const QString &idtf) const
{
    ScUriList contents;

    // get all contents that same to our identifier
    mMemoryInterface->find_str_content(idtf, contents);

    if (contents.size() == 0)   return ScUriEmpty;

    ScUri keynode_main_ = keynode("/etc/main_");
    ScUri keynode_idtf = keynode("/etc/identification*");

    ScUriList::iterator it;
    for (it = contents.begin(); it != contents.end(); ++it)
    {
        // find set where current sc-link is a main identifier
        ScUriVector res;
        if (searchOneShot(ScTemplate(ScElementType(ScNode | ScConst),
                                     ScElementType(ScArcMain),
                                     *it,
                                     ScElementType(ScArcMain),
                                     keynode_main_), res))
        {
            // get object by founded identifiers set
            if (searchOneShot(ScTemplate(res[0],
                                         ScElementType(ScArcCommon | ScConst),
                                         ScElementType(ScNode | ScConst),
                                         ScElementType(ScArcMain),
                                         keynode_idtf), res))
            {
                return res[2];
            }else
                SuiExcept(SuiExceptionInternalError,
                          QString("Invalid knowledge base"),
                          "ScUri suiScHelper::findElementByMainIdentifier(const QString &idtf) const");
        }

    }

    return ScUriEmpty;
}

QString suiScHelper::stringIdtf(const ScUri &uri, const ScUri &langUri) const
{
    // get all identifiers
    ScUriVector idtfs;
    allIdtfs(uri, idtfs);

    // iterate all identifiers and trying to find with specified language
    for (ScUriVector::iterator it = idtfs.begin(); it != idtfs.end(); ++it)
    {
        ScUri idtfUri = *it;
        // check language
        if (checkInclusion(idtfUri, langUri))
        {
            QString res;
            QIODevice *device = mMemoryInterface->open_content(idtfUri);

            if (device == 0)
                SuiExcept(SuiExceptionInvalidParameters,
                          QString("Can't open content for sc-element with uri = %1").arg(idtfUri.value()),
                          "QString suiScHelper::stringIdtf(const ScUri &uri, const ScUri &langUri) const");

            res = mMemoryInterface->decode_str_content(*device);
            mMemoryInterface->close_content(device);

            return res;
        }
    }

    return QString();
}

bool suiScHelper::searchOneShot(const ScTemplate &templ, ScUriVector &res) const
{
    res.clear();
    res.resize(templ.count());

    ScSafeIterator it(mMemoryInterface, templ);
    if (it.is_over()) return false;

    for (int i = 0; i < templ.count(); i++) res[i] = it.value(i);
    it.next();

    // check if there is error in knowledge base
    if (!it.is_over()) SuiExcept(SuiExceptionDuplicateItem,
                                  QString("Founded more than one result"),
                                  "bool suiScHelper::searchOneShot(const ScTemplate &templ, ScUriVector &res)")

    return true;
}

bool suiScHelper::genElStr(const ScTemplate &templ, ScUriVector &res)
{
    res.clear();
    res.resize(templ.count());

    // create sc-elements
    for (int i = 0; i < templ.count(); i++)
    {
        res[i] = templ.param(i).is_uri() ? templ.param(i).uri() : mMemoryInterface->gen_el(templ.param(i).type());
        Q_ASSERT(!res[i].isEmpty());
    }

    // check arc types
    ScElementType type1 = mMemoryInterface->get_el_type(res[1]);
    Q_ASSERT(type1.check(ScArcCommon) || type1.check(ScArcMain) || type1.check(ScEdgeCommon));

    mMemoryInterface->set_beg(res[1], res[0]);
    mMemoryInterface->set_end(res[1], res[2]);

    // process 5 elements template
    if (templ.count() > 3)
    {
        ScElementType type3 = mMemoryInterface->get_el_type(res[3]);
        Q_ASSERT(type3.check(ScArcCommon) || type3.check(ScArcMain) || type3.check(ScEdgeCommon));

        mMemoryInterface->set_beg(res[3], res[4]);
        mMemoryInterface->set_end(res[3], res[1]);
    }

    return true;
}

bool suiScHelper::ensureExist(const ScTemplate &templ, ScUriVector &res)
{
    // trying to find construction and if doesn't exist, then create it
    if (!searchOneShot(templ, res))
        return genElStr(templ, res);

    return true;
}

bool suiScHelper::checkExist(const ScTemplate &templ) const
{
    ScSafeIterator it(mMemoryInterface, templ);
    return !it.is_over();
}

ScUri suiScHelper::searchFormat(const ScUri &uri) const
{
    // get format keynode
    ScUri group_format = keynode("/ui/format");

    // search all input arcs into uri
    ScSafeIterator iter(mMemoryInterface, ScTemplate() << ScElementType(ScNode | ScConst)
                                                       << ScElementType(ScArcMain)
                                                       << uri);
    while (!iter.is_over())
    {
        ScUriVector res;
        if (searchOneShot(ScTemplate() << group_format << ScElementType(ScArcMain) << iter.value(0), res))
            return res[2];
        iter.next();
    }

    return ScUri();
}

bool suiScHelper::checkInclusion(const ScUri &uri, const ScUri &setUri) const
{
    ScSafeIterator iter(mMemoryInterface,
                        ScTemplate() << setUri << ScElementType(ScArcMask) << uri);

    return !iter.is_over();
}
