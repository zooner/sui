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

#ifndef SUISCHELPER_H
#define SUISCHELPER_H

#include <QObject>
#include "interfaces/ScHelper.h"

class suiScHelper : public QObject,
                    public ScHelperInterface

{
    Q_OBJECT
    Q_INTERFACES(ScHelperInterface)
public:
    explicit suiScHelper(ScMemoryInterface *memoryInterface, QObject *parent = 0);
    virtual ~suiScHelper();

    //! @copydoc ScHelperInterface::scMemory
    ScMemoryInterface* scMemory() const { return mMemoryInterface; }
    //! @copydoc ScHelperInterface::keynode
    ScUri keynode(const QString &alias) const;
    //! @copydoc ScHelperInterface::appendKeynode
    void appendKeynode(const ScUri &uri, const QString &alias);
    //! @copydoc ScHelperInterface::appendFormatKeynode
    ScUri appendFormatKeynode(const QString &formatName);
    //! @copydoc ScHelperInterface::removeKeynode
    void removeKeynode(const QString &alias);
    //! @copydoc ScHelperInterface::hasKeynode
    bool hasKeynode(const QString &alias) const;

    //! @copydoc ScHelperInterface::appendTextIdtf
    bool appendTextIdtf(const ScUri &elem, const QString &idtf, bool is_main);
    //! @copydoc ScHelperInterface::appendIdtf
    bool appendIdtf(const ScUri &elem, const ScUri &idtf, bool is_main);
    //! @copydoc ScHelperInterface::removeTextIdtf
    bool removeTextIdtf(const ScUri &elem, const QString &idtf);
    //! @copydoc ScHelperInterface::removeIdtf
    bool removeIdtf(const ScUri &elem, const ScUri &idtf);

    //! @copydoc ScHelperInterface::allIdtfs
    bool allIdtfs(const ScUri &elem, ScUriVector &result) const;
    //! @copydoc ScHelperInterface::
    QString stringIdtf(const ScUri &uri, const ScUri &langUri) const;

    //! @copydoc ScHelperInterface::findElementByMainIdentifier
    ScUri findElementByMainIdentifier(const QString &idtf) const;

    //! @copydoc ScHelperInterface::searchOneShot
    bool searchOneShot(const ScTemplate &templ, ScUriVector &res) const;
    //! @copydoc ScHelperInterface::genElStr
    bool genElStr(const ScTemplate &templ, ScUriVector &res);
    //! @copydoc ScHelperInterface::ensureExist
    bool ensureExist(const ScTemplate &templ, ScUriVector &res);
    //! @copydoc ScHelperInterface::checkExist
    bool checkExist(const ScTemplate &templ) const;
    //! @copydoc ScHelperInterface::searchFormat
    ScUri searchFormat(const ScUri &uri) const;

    //! @copydoc ScHelperInterface::checkInclusion
    bool checkInclusion(const ScUri &uri, const ScUri &setUri) const;

protected:
    //! Pointer to used sc-memory interface
    ScMemoryInterface *mMemoryInterface;
    //! Keynodes map
    typedef QMap<QString, ScUri> KeynodesMap;
    KeynodesMap mKeynodesMap;

signals:

public slots:

};

#endif // SUISCHELPER_H
