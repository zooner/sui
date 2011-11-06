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

#include "suiknowbase.h"
#include "suiroot.h"

suiKnowBase::suiKnowBase(QObject *parent) :
    QObject(parent)
{
}

void suiKnowBase::registerAllKeynodes()
{
    mKeynodesMap["stype_const"] = "/type/const";
    mKeynodesMap["stype_var"] = "/type/var";
    mKeynodesMap["stype_meta"] = "/type/meta";

    mKeynodesMap["stype_sheaf"] = "/type/tuple";

    //mKeynodesMap["identification*"] = "/etc/identification*";
    mKeynodesMap["decomposition*"] = "/etc/decomposition*";
    //mKeynodesMap["rrel_main"] = "/etc/main_";

    mKeynodesMap["group_text"] = "/etc/text";

    mKeynodesMap["russian_language"] = "/language/russian";
    mKeynodesMap["english_language"] = "/language/english";

    mKeynodesMap["nrel_content*"] = "/etc/content*";
    mKeynodesMap["nrel_file_path*"] = "/etc/path*";
    mKeynodesMap["nrel_sem_equiv"] = "/etc/sem_eq*";

    mKeynodesMap["kb_source"] = "/etc/source";

    mKeynodesMap["ui_format"] = "/ui/format";
    mKeynodesMap["ui_translator_to_sc"] = "/ui/trans_to_sc";
    mKeynodesMap["ui_translator_from_sc"] = "/ui/trans_from_sc";
    mKeynodesMap["ui_viewer"] = "/ui/viewer";
    mKeynodesMap["ui_editor"] = "/ui/editor";
    mKeynodesMap["ui_main_window"] = "/ui/main_window";
    mKeynodesMap["ui_main_menu"] = "/ui/main_menu";
    mKeynodesMap["ui_noatom_command"] = "/ui/command/noatom";
    mKeynodesMap["ui_atom_command"] = "/ui/command/atom";

    // test code that works

    /*ScMemoryInterface *sc_memory = suiRoot::getInstance()->scMemory();
    ScHelperInterface *sc_help = suiRoot::getInstance()->scHelper();

    QBuffer buf;
    buf.open(QBuffer::WriteOnly);
    QDataStream stream(&buf);
    stream << QString("test");
    buf.close();

    ScUri uri = sc_memory->gen_el(ScElementType(ScLink));
    qDebug() << uri.value();
    sc_memory->set_content(uri, buf);

    ScUriList res;
    sc_memory->find_content(buf, res);

    qDebug() << res.size();*/
}

void suiKnowBase::initialize()
{
    registerAllKeynodes();
//    createMinimalBase();

    // first of all we need to find identification* and main_ nodes
    resolveMainIdentificationKeynodes();

    // resolve other keynodes
    ScHelperInterface *helper = suiRoot::getInstance()->scHelper();
    for (KeynodesMap::iterator it = mKeynodesMap.begin(); it != mKeynodesMap.end(); ++it)
    {
        ScUri uri = helper->findElementByMainIdentifier(it.key());
        if (!uri.isEmpty()) helper->appendKeynode(uri, it.value());
    }
}

void suiKnowBase::shutdown()
{

}

QStringList suiKnowBase::availableFormats()
{
    return QStringList() << "gwf";
}

void suiKnowBase::createMinimalBase()
{
    ScMemoryInterface *sc_memory = suiRoot::getInstance()->scMemory();
    ScHelperInterface *sc_helper = suiRoot::getInstance()->scHelper();

    // create keynodes at first
    KeynodesMap::iterator it;
    for (it = mKeynodesMap.begin(); it != mKeynodesMap.end(); ++it)
        sc_helper->appendKeynode(sc_memory->gen_el(ScElementType(ScNode | ScConst)), it.value());

    // get text keynode
    ScUri key_text = sc_helper->keynode("/etc/text");

    // setup main identifiers
    for (it = mKeynodesMap.begin(); it != mKeynodesMap.end(); ++it)
        sc_helper->appendTextIdtf(sc_helper->keynode(it.value()), it.key(), true);
}

void suiKnowBase::loadSources(const QStringList &sourceDirs)
{
    // load knowledge base from sources
    QString sDir;
    foreach(sDir, sourceDirs)
        loadSourceDirectory(sDir, true);

    // find all keynodes
    ScHelperInterface *helper = suiRoot::getInstance()->scHelper();
    KeynodesMap::iterator it;
    for (it = mKeynodesMap.begin(); it != mKeynodesMap.end(); ++it)
    {
        // skip keynodes, that already found
        if (helper->hasKeynode(it.value())) continue;
        // try to find keynodes by main identifier
        ScUri uri = helper->findElementByMainIdentifier(it.key());
        if (uri == ScUriEmpty) SuiExcept(SuiExceptionItemNotFound,
                                         QString("Can't find keynode '%1'").arg(it.key()),
                                         "void suiKnowBase::initialize(const QStringList &sourceDirs)");
    }

    ScUri content_keynode = helper->keynode("/etc/content*");

    // trying to search all loaded sources
    ScMemoryInterface *mem = suiRoot::getInstance()->scMemory();
    ScSafeIterator scIt(mem, ScTemplate() << helper->keynode("/etc/source")
                                          << ScElementType(ScArcMain)
                                          << ScElementType(ScNode | ScConst));
    while (!scIt.is_over())
    {
        ScUriVector res;
        // trying to find content of source
        if (helper->searchOneShot(ScTemplate() << scIt.value(2)
                                             << ScElementType(ScArcCommon | ScConst | ScPos)
                                             << ScElementType(0) // fix to link
                                             << ScElementType(ScArcMain)
                                             << content_keynode, res))
        {
            suiRoot::getInstance()->translateDataToSc(res[2]);
        }else
            SuiExcept(SuiExceptionInternalError,
                      "Can't find knowledge base source content",
                      "void suiKnowBase::initialize(const QStringList &sourceDirs)");

        scIt.next();
    }
}

void suiKnowBase::loadSourceFile(const QString& filename)
{
    QFile file(filename);
    QFileInfo finfo(filename);

    ScMemoryInterface *sc_memory = suiRoot::getInstance()->scMemory();
    ScHelperInterface *sc_helper = suiRoot::getInstance()->scHelper();

    //get needed keynodes
    ScUri content_keynode = sc_helper->keynode("/etc/content*");
    ScUri path_keynode = sc_helper->keynode("/etc/path*");
    ScUri source_keynode = sc_helper->keynode("/etc/source");


    QString formatAlias = "/ui/format/" + finfo.suffix().toLower();

    ScUri format_keynode;
    if (!sc_helper->hasKeynode(formatAlias))
    {
        qDebug() << "format " << finfo.suffix() << " doesn't supported";
        return;
    }else
        format_keynode = sc_helper->keynode(formatAlias);

    ScUri source_node = sc_memory->gen_el(ScElementType(ScNode | ScConst));
    // Create link and write content to it.
    ScUri source_content = sc_memory->gen_el(ScElementType(ScLink | ScConst));
    sc_memory->set_content(source_content, file);

    // include sc-link into format set
    ScUriVector r;
    if (!sc_helper->genElStr(ScTemplate() << format_keynode << ScElementType(ScArcMain) << source_content, r))
        SuiExcept(SuiExceptionInternalError,
                  QString("Can't include sc-link into '%1' set").arg(formatAlias),
                  "void suiKnowBase::loadSourceFile(const QString& filename)");

    // Create node for storing file path.
    ScUri source_path_node = sc_memory->gen_el(ScElementType(ScLink | ScConst));
    QByteArray ba = filename.toUtf8();
    QBuffer buffer(&ba);
    sc_memory->set_content(source_path_node, buffer);


    ScUriVector v;
    sc_helper->genElStr(ScTemplate() << source_keynode
                        << ScElementType(ScArcMain)
                        << source_node, v);

    sc_helper->genElStr(ScTemplate() << source_node
                        << ScElementType(ScArcCommon | ScConst | ScPos)
                        << source_content
                        << ScElementType(ScArcMain)
                        << content_keynode, v);

    sc_helper->genElStr(ScTemplate() << source_node
                        << ScElementType(ScArcCommon | ScConst | ScPos)
                        << source_path_node
                        << ScElementType(ScArcMain)
                        << path_keynode, v);

}

void suiKnowBase::loadSourceDirectory(const QDir& path, bool recursively)
{
    // check if path exist
    if (!path.exists())     SuiExcept(SuiExceptionFileNotFound,
                                      QString("Can't find directory '%1'").arg(path.absolutePath()),
                                      "void suiKnowBase::loadSourceDirectory(const QDir& path, bool recursively)");

    QDirIterator dirIt(path, recursively ? QDirIterator::Subdirectories : QDirIterator::NoIteratorFlags);
    while (dirIt.hasNext())
    {
        QFileInfo finfo(dirIt.next());

        if (availableFormats().contains(finfo.suffix(), Qt::CaseInsensitive))
            loadSourceFile(finfo.absoluteFilePath());
    }

}

void suiKnowBase::resolveMainIdentificationKeynodes()
{
    // get sc-links with identification* and main_ strings
    ScMemoryInterface *memory = suiRoot::getInstance()->scMemory();
    ScHelperInterface *helper = suiRoot::getInstance()->scHelper();

    QString idtf_alias = "identification*";
    QString main_alias = "main_";

    ScUriList idtf_candidates;
    if (!memory->find_str_content(idtf_alias, idtf_candidates))
        SuiExcept(SuiExceptionItemNotFound,
                  QString("Can't find sc-link with content: %1").arg(idtf_alias),
                  "void suiKnowBase::resolveMainIdentificationKeynodes()");

    ScUriList main_candidates;
    if (!memory->find_str_content(main_alias, main_candidates))
        SuiExcept(SuiExceptionFileNotFound,
                  QString("Can't find sc-link with content: %1").arg(main_alias),
                  "void suiKnowBase::resolveMainIdentificationKeynodes()");

    // all founded objects can be a candidates, so try them all
    for (ScUriList::iterator idtf_it = idtf_candidates.begin(); idtf_it != idtf_candidates.end(); ++idtf_it)
        for (ScUriList::iterator main_it = main_candidates.begin(); main_it != main_candidates.end(); ++main_it)
        {
            // iterate all possible identification sets for node identification*
            ScSafeIterator it_idtf_set(memory,
                                       ScTemplate() << ScElementType(ScNode | ScConst | ScTuple)
                                       << ScElementType(ScArcMain)
                                       << *idtf_it
                                       << ScElementType(ScArcMain)
                                       << ScElementType(ScNode | ScConst | ScRole));
            while (!it_idtf_set.is_over())
            {
                // now check if founded attribute (value with index 4) also
                // exist in any construction when we trying to find
                // identification set for main_ node
                ScSafeIterator it_main_set(memory,
                                           ScTemplate() << ScElementType(ScNode | ScConst)
                                           << ScElementType(ScArcMain)
                                           << *main_it
                                           << ScElementType(ScArcMain)
                                           << it_idtf_set.value(4));
                while (!it_main_set.is_over())
                {
                    // trying to find idetification* node
                    ScSafeIterator it1(memory,
                                       ScTemplate() << it_idtf_set.value(0)
                                       << ScElementType(ScArcCommon | ScConst)
                                       << ScElementType(ScNode | ScConst));

                    memory->_printEl(it_idtf_set.value(0));
                    while (!it1.is_over())
                    {
                        // check if it have output arc into common arc from identifiers set
                        // to identification* node
                        if (helper->checkExist(ScTemplate() << it1.value(2)
                                               << ScElementType(ScArcMain)
                                               << it1.value(1)))
                        {
                            // now we just have founded candidate to identification* (it1.value(2)) node
                            // to ensure we just need to check if it links to common arc
                            // from identification set for main_ node
                            if (helper->checkExist(ScTemplate() << it_main_set.value(0)
                                                   << ScElementType(ScArcCommon | ScConst)
                                                   << it_idtf_set.value(4)
                                                   << ScElementType(ScArcMain)
                                                   << it1.value(2)))
                            {
                                helper->appendKeynode(it_idtf_set.value(4), "/etc/main_");
                                helper->appendKeynode(it1.value(2), "/etc/identification*");
                                return;
                            }
                        }

                        it1.next();
                    }

                    it_main_set.next();
                }


                it_idtf_set.next();
            }
        }

}

