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

#ifndef SUIKNOWBASE_H
#define SUIKNOWBASE_H

#include "suiCore_global.h"
#include <QObject>
#include <QMap>
#include <QtCore>

// base keynode aliases
#define key_rrel_main "/etc/main_"
#define key_nrel_identification "/etc/identification*"
#define key_group_text "/etc/text"

#define key_command_noatom  "/ui/command/noatom"
#define key_command_atom    "/ui/command/atom"

/*! Class that control knowledge base stuff, like keynodes and garbage clean
  */
class SUICORESHARED_EXPORT suiKnowBase : public QObject
{
    Q_OBJECT
public:
    explicit suiKnowBase(QObject *parent = 0);

    /*! Initialize all knowledge base stuff
      */
    void initialize();
    //! Shutdown knowledge base stuff
    void shutdown();

    /*! Load knowledge base sources from directories list
      * @param sourceDirs List of path to source directories
      */
    void loadSources(const QStringList &sourceDirs);

protected:
    /*! Load knowledge base source into sc-memory.
      * It generates construction in sc-memory that showed on image:
      * \image html kb_source_templ.png
      * @see loadSourceDirectory().
      */
    void loadSourceFile(const QString& fileName);

    /*! This is an overloaded function for convenient usage.
     * Loads all source files from specified directory into SCMemory.
     * @see loadSourceDirectory(const QString&, bool)
     */
    inline void loadSourceDirectory(const QString& path, bool recursively = false)
    {
        loadSourceDirectory(QDir(path), recursively);
    }

    /*! Loads all source files from specified directory into SCMemory.
     * @param path directory, source files will be loaded from.
     * @param recursively true if you'd like to load all files from all subdirectories.
     * @see loadSourceFile(const QString&).
     */
    void loadSourceDirectory(const QDir& path, bool recursively = false);

    /*! Resolve identification* and main_ keynodes.
      * This function trying to find \e identification* and \e main_ keynodes.
      * See search template on image:
      * \image html keynodes/main_identification_templ.png
      */
    void resolveMainIdentificationKeynodes();

protected:
    /*! Create minimal knowledge base. That base is minimal requiment knowledge base.
      */
    void createMinimalBase();

    //! Build keynodes map
    void registerAllKeynodes();

    /*!
     * @return list of available file formats for loading sources.
     * @see loadSourceDirectory(),
     * @see loadSourceFile().
     */
    static QStringList availableFormats();

protected:
    //! Keynodes map
    typedef QMap<QString, QString> KeynodesMap;
    KeynodesMap mKeynodesMap;

signals:

public slots:

};

#endif // SUIKNOWBASE_H
