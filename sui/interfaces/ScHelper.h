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

#ifndef SCHELPER_H
#define SCHELPER_H

#include <QtPlugin>
#include "ScMemory.h"

class ScMemoryInterface;

/*! Interface that provides high level api to work with sc-memory.
  * It contains functions, that make it easier to work with sc-memory interface.
  * Also it contains functions to operate with keynodes. Each keynode
  * can be used by it alias. Alias - unique string name for a keynode.
  * For example: ui/window/main, sc/const and etc.
  * We recomend to separate them by '/' symbol for a logical groups.
  * For example, all keynode aliases that starts with \e ui us associated with
  * keynodes that used in User Interface.
  */
class ScHelperInterface
{
public:
    virtual ~ScHelperInterface() {}

public:
    /*! Get pointer to used sc-memory interface
      * @return Return pointer to used sc-memeory interface
      */
    virtual ScMemoryInterface* scMemory() const = 0;

    /*! Get keynode
      * @param alias Keynode alias
      * @return Return keynode ScUri if it exist; otherwise return ScUriEmpty
      * @see ScHelperInterface::appendKeynode, ScHelperInterface::removeKeynode, ScHelperInterface::hasKeynode
      */
    virtual ScUri keynode(const QString &alias) const = 0;

    /*! Append new keynode with specified alias
      * @param uri ScUri of keynode sc-element
      * @param alias Keynode alias
      * @see ScHelperInterface::removeKeynode, ScHelperInterface::keynode, ScHelperInterface::hasKeynode
      */
    virtual void appendKeynode(const ScUri &uri, const QString &alias) = 0;

    /*! Append new format keynode. Keynode created with that function
      * will be added into formats set and have alias "/ui/format/x", where x
      * is a format name
      *
      * @param formatName Format name. Usually file suffix in lower case
      * @return Return ScUri of created keynode
      */
    virtual ScUri appendFormatKeynode(const QString &formatName) = 0;


    /*! Remove keynode by alias
      * @param alias Alias of keynode, that need to be removed
      * @see ScHelperInterface::appendKeynode, ScHelperInterface::keynode, ScHelperInterface::hasKeynode
      */
    virtual void removeKeynode(const QString &alias) = 0;

    /*! Check if keynode with specified alias exist
      * @param alias Keynode alias to check
      * @return Return true, if keynode with specified \p alias exist; otherwise return false.
      * @see ScHelperInterface::keynode, ScHelperInterface::appendKeynode, ScHelperInterface::removeKeynode
      */
    virtual bool hasKeynode(const QString &alias) const = 0;

    /*! Append new text identifier for sc-element
      * @param elem ScUri of sc-element. It append new identifier for that element
      * @param idtf Text identifier
      * @param is_main Flag to append \p itdf as main, or not
      * @return Returns true, if identifier was successfully appended; otherwise return false.
      * @note If you try to append identifier that exists and \p is_main value is \e false, then function return false.
      * Otherwise if \p is_main value is \e true, then it will be set as a main identifier and function will return true.
      * @see ScHelperInterface::removeTextIdtf
      */
    virtual bool appendTextIdtf(const ScUri &elem, const QString &idtf, bool is_main) = 0;

    /*! Append new identifier for sc-element
      * @param elem ScUri of sc-element. It append new identifier for that element
      * @param idtf ScUri of sc-link that is an identifier
      * @param is_main Flag to append \p itdf as main, or not
      * @return Returns true, if identifier was successfully appended; otherwise return false.
      * @note If you try to append identifier that exists and \p is_main value is \e false, then function return false.
      * Otherwise if \p is_main value is \e true, then it will be set as a main identifier and function will return true.
      * @see ScHelperInterface::removeIdtf
      */
    virtual bool appendIdtf(const ScUri &elem, const ScUri &idtf, bool is_main) = 0;

    /*! Remove identifier from sc-element identifiers set
      * @param elem ScUri of sc-element, it identifiers set will be changed
      * @param idtf Text identifier
      * @return Returns true, if identifier was successfully removed; otherwise return false.
      * @note If you try to remove main identifier, then it will return false. If you want to change
      * main identifier you need to append new identifier as main at first.
      * @see ScHelperInterface::appendTextIdtf
      */
    virtual bool removeTextIdtf(const ScUri &elem, const QString &idtf) = 0;

    /*! Remove identifier from sc-element identifiers set
      * @param elem ScUri of sc-element, it identifiers set will be changed
      * @param idtf Scuri of sc-link that is an identifier
      * @return Returns true, if identifier was successfully removed; otherwise return false.
      * @note If you try to remove main identifier, then it will return false. If you want to change
      * main identifier you need to append new identifier as main at first.
      * @see ScHelperInterface::appendIdtf
      */
    virtual bool removeIdtf(const ScUri &elem, const ScUri &idtf) = 0;

    /*! Get all identifiers for specified sc-element
      * @param elem ScUri of sc-element we want to get identifiers
      * @param result Search result container. Contains ScUri's of all identifiers.
      * @return Return ture, if any identifiers was found; otherwise return false
      */
    virtual bool allIdtfs(const ScUri &elem, ScUriVector &result) const = 0;

    /*! Find node by main identifier.
      * @param idtf Main identifier
      * @return Return ScUri of sc-element with specified main identifier. If it wasn't found,
      * then return ScUriEmpty
      */
    virtual ScUri findElementByMainIdentifier(const QString &idtf) const = 0;

    /*! Get string identifier of sc-element with specified \p uri.
      * You can see template for search on image:
      * \image html get_str_idtf_templ.png
      * @param uri ScUri of sc-element that we want to get identifier
      * @param langUri ScUri of sc-element that designate language
      *
      * @return Return string that contains identifier if it exist. If identifier doesn't exist, then
      * return empty string.
      */
    virtual QString stringIdtf(const ScUri &uri, const ScUri &langUri) const = 0;

    /*! Find just one consturction for sc-elements template
      * @param templ Search template
      * @param res Result container. Contains search result in order of ScIteratorInterface::value.
      * Clear on search start.
      * @return Returns true, if any construction foundedl otherwise return false
      * @see ScMemoryInterface::create_iterator3, ScHelperInterface::searchOneShot5
      */
    virtual bool searchOneShot(const ScTemplate &templ, ScUriVector &res) const = 0;

    /*! Create sc-construction from template
      * @param templ sc-construction template.
      * @param res Result container. Contains whole construction.
      * @return Returns true, if construction was created; otherwise return false.
      * @see ScMemoryInterface::create_iterator3
      */
    virtual bool genElStr(const ScTemplate &templ, ScUriVector &res) = 0;

    /*! Try to search construction by template. And if it doesn't exist, then create one
      * @param templ sc-construction template.
      * @param res Result container. Contains whole construction.
      * @return Returns true, if construction was created or founded; otherwise return false.
      * @see ScHelperInterface::checkExist, ScHelperInterface::genElStr
      */
    virtual bool ensureExist(const ScTemplate &templ, ScUriVector &res ) = 0;

    /*! Check if there are any sc-construction that math template
      * @param templ sc-construction template.
      * @see ScHelperInterface::ensureExist
      */
    virtual bool checkExist(const ScTemplate &templ) const = 0;

    /*! Get node that specified format for sc-link
      * @param uri ScUri of sc-link we want to get format
      * @return Return ScUri of node that designate format
      */
    virtual ScUri searchFormat(const ScUri &uri) const = 0;

    /*! Check if specified sc-element have an input arc or edge from other sc-element.
      * Another words, check if sc-element is an member of specified sc-set.
      * @param uri ScUri of sc-element that need to be checked
      * @param setUri ScUri of sc-set
      * @return Return true, if sc-element with specified \p uri have an input arc or edge
      * from set \p setUri; otherwise return false.
      */
    virtual bool checkInclusion(const ScUri &uri, const ScUri &setUri) const = 0;

};

Q_DECLARE_INTERFACE(ScHelperInterface,
                    "com.OSTIS.sui.ScHelperInterface/1.0")

#endif // SCHELPER_H
