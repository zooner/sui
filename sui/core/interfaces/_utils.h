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

#ifndef _UTILS_H
#define _UTILS_H

#include <QtCore>

// write string to specified IODevice
#define string2IODevice(ioDev, str) ioDev.open(QIODevice::WriteOnly); \
QDataStream stream(&ioDev); \
stream << idtf; \
ioDev.close();


class BaseException : public QtConcurrent::Exception
{
public:
    BaseException(const QString &inName, const QString& inDescription, const QString& inSource, const char* inFile, long inLine) :
        mName(inName),
        mDescription(inDescription),
        mSource(inSource),
        mFile(inFile),
        mLine(inLine)
    {

    }

    virtual ~BaseException() throw() {}

    void raise() const
    {
        qDebug() << "Exception: " << mName << "\nDescription: " << mDescription <<
                    "\nSource: " << mSource << "\nFile: " << mFile << "\nLine: " << mLine << "\n";
        throw *this;
    }
    Exception *clone() const { return new BaseException(*this); }

protected:
    QString mName;
    QString mDescription;
    QString mSource;
    QString mFile;
    long mLine;
};

// define all core exceptions
class SuiExceptionUnknown : public BaseException
{
public:
    SuiExceptionUnknown(const QString& inDescription, const QString& inSource, const char* inFile, long inLine) :
        BaseException("SuiExceptionUnknown", inDescription, inSource, inFile, inLine) {}

    Exception *clone() const { return new SuiExceptionUnknown(*this); }
};

class SuiExceptionFileNotFound : public BaseException
{
public:
    SuiExceptionFileNotFound(const QString& inDescription, const QString& inSource, const char* inFile, long inLine) :
        BaseException("SuiExceptionFileNotFound", inDescription, inSource, inFile, inLine) {}

    Exception *clone() const { return new SuiExceptionFileNotFound(*this); }
};

class SuiExceptionIO : public BaseException
{
public:
    SuiExceptionIO(const QString& inDescription, const QString& inSource, const char* inFile, long inLine) :
        BaseException("SuiExceptionIO", inDescription, inSource, inFile, inLine) {}

    Exception *clone() const { return new SuiExceptionIO(*this); }
};

class SuiExceptionInvalidState : public BaseException
{
public:
    SuiExceptionInvalidState(const QString& inDescription, const QString& inSource, const char* inFile, long inLine) :
        BaseException("SuiExceptionInvalidState", inDescription, inSource, inFile, inLine) {}

    Exception *clone() const { return new SuiExceptionInvalidState(*this); }
};

class SuiExceptionItemNotFound : public BaseException
{
public:
    SuiExceptionItemNotFound(const QString& inDescription, const QString& inSource, const char* inFile, long inLine) :
        BaseException("SuiExceptionItemNotFound", inDescription, inSource, inFile, inLine) {}

    Exception *clone() const { return new SuiExceptionItemNotFound(*this); }
};

class SuiExceptionDuplicateItem : public BaseException
{
public:
    SuiExceptionDuplicateItem(const QString& inDescription, const QString& inSource, const char* inFile, long inLine) :
        BaseException("SuiExceptionDuplicateItem", inDescription, inSource, inFile, inLine) {}

    Exception *clone() const { return new SuiExceptionDuplicateItem(*this); }
};

class SuiExceptionInvalidParameters : public BaseException
{
public:
    SuiExceptionInvalidParameters(const QString& inDescription, const QString& inSource, const char* inFile, long inLine) :
        BaseException("SuiExceptionInvalidParameters", inDescription, inSource, inFile, inLine) {}

    Exception *clone() const { return new SuiExceptionInvalidParameters(*this); }
};

class SuiExceptionInternalError : public BaseException
{
public:
    SuiExceptionInternalError(const QString& inDescription, const QString& inSource, const char* inFile, long inLine) :
        BaseException("SuiExceptionInternalError", inDescription, inSource, inFile, inLine) {}

    Exception *clone() const { return new SuiExceptionInternalError(*this); }
};

class SuiInvalidKnowledgeBase : public BaseException
{
public:
    SuiInvalidKnowledgeBase(const QString& inDescription, const QString& inSource, const char* inFile, long inLine) :
        BaseException("SuiInvalidKnowledgeBase", inDescription, inSource, inFile, inLine) {}

    Exception *clone() const { return new SuiInvalidKnowledgeBase(*this); }
};

#define SuiExcept(_class, desc, src) _class(desc, src, __FILE__, __LINE__).raise();

#define def_exception(ex_name) class ex_name : public BaseException \
{ \
public: \
    ex_name(const QString& inDescription, const QString& inSource, const char* inFile, long inLine) : \
        BaseException( #ex_name, inDescription, inSource, inFile, inLine) \
    {} \
    Exception *clone() const { return new ex_name(*this); } \
};

#endif // _UTILS_H
