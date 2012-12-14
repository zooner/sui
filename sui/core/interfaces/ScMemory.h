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

#ifndef SC_INTERFACES_H
#define SC_INTERFACES_H

#include <QtPlugin>
#include <QString>
#include <QIODevice>
#include <QVariant>

#include "_utils.h"

// sc-element type
enum _ScElementCommonType
{
    /*! \def Type of sc-element, that designate node.
     * See image: \image html images/model/scg/node_not_define.png
     */
    ScNode = 1,
    /*! \def Type of sc-element, that designate commond edge.
     * See image: \image html images/model/scg/edge.png
     */
    ScEdgeCommon = 2,
    /*! \def Type of sc-element, that designate commond arc.
     * See image: \image html images/model/scg/arc_common.png
     */
    ScArcCommon = 4,
    /*! \def Type of sc-element, that designate main arc (equivalent to (ScArcCommon | ScAccessory | ScConst | ScPos)).
     * See image: \image html images/model/scg/arc_main.png
     */
    ScArcMain = 8,
    /*! \def Type of sc-element, that designate link to other content.
     * See image: \image html images/model/scg/content.png
     */
    ScLink = 16
};

enum _ScElementConstancy
{
    ScConst = 32,
    ScVar = 64,
    ScMeta = 128
};

enum _ScElementPositivity
{
    ScPositive = 256,
    ScNegative = 512,
    ScFuzzy = 1024
};

enum _ScElementPermanence
{
    ScTemporary = 2048,
    ScPermanent = 4096
};

/*!
 * @TODO: Add comment here
 */
enum
{
    ScAccessory = 8192
};

enum _ScNodeType
{
    ScTuple = 256,
    ScStruct = 512,
    ScRole = 1024,
    ScBinary = 2048,
    ScConcept = 4096,
    ScAbstract = 8192
};

enum _ScTypeMask
{
    ScArcMask = (ScEdgeCommon | ScArcCommon | ScArcMain),
    ScConstMask = (ScConst | ScVar | ScMeta),
    ScPositivityMask = (ScPositive | ScNegative),
    ScPermanenceMask = (ScTemporary | ScPermanent),
    ScStructuralMask = (ScTuple | ScStruct | ScRole | ScBinary | ScConcept | ScAbstract)
};

struct _ScUri
{
    explicit _ScUri(quintptr v = 0) : val(v) {}
    _ScUri(const _ScUri &other) { val = other.val; }

    bool operator ==(const _ScUri &other) const { return val == other.val; }
    bool operator !=(const _ScUri &other) const { return val != other.val; }

    bool operator <(const _ScUri &other) const { return val < other.val; }
    bool operator >(const _ScUri &other) const { return val > other.val; }

    bool operator <=(const _ScUri &other) const { return val <= other.val; }
    bool operator >=(const _ScUri &other) const { return val >= other.val; }

    // check if it empty
    bool isEmpty() const { return val == 0; }
    // get value
    quintptr value() const { return val; }

    static inline _ScUri empty() {return _ScUri(0);}

private:
    quintptr val;
};

typedef quint16 _ScElemTypeValue;
struct _ScElementType
{
    explicit _ScElementType(_ScElemTypeValue v = 0) : val(v) {}
    _ScElementType(const _ScElementType &other) { val = other.val; }

    bool operator ==(const _ScElementType &other) const { return val == other.val; }
    bool operator !=(const _ScElementType &other) const { return val != other.val; }

    bool operator <(const _ScElementType &other) const { return val < other.val; }
    bool operator >(const _ScElementType &other) const { return val > other.val; }

    bool operator <=(const _ScElementType &other) const { return val <= other.val; }
    bool operator >=(const _ScElementType &other) const { return val >= other.val; }

    /*! Append new component into type. Equivalent to: type | v
      */
    _ScElementType& add(const _ScElemTypeValue &v) { val = val | v; return *this; }
    /*! Remove compoentn from type. Equivalent to: type & (~v)
      */
    _ScElementType& rem(const _ScElemTypeValue &v) { val = val & (~v); return *this; }
    /*! Check if type have specified components \p v
      */
    bool check(const _ScElemTypeValue &v) const { return val & v; }
    //! Check if that type is arc or edge
    bool isArcOrEdge() const
    {
        if (val & ScArcCommon) return true;
        if (val & ScArcMain) return true;
        if (val & ScEdgeCommon) return true;

        return false;
    }
    //! Check if type is valid
    bool isValid() const
    {
        if (val == 0) return false;

        // check element types
        if ((val & ScNode) && (val & ScArcCommon)) return false;
        if ((val & ScNode) && (val & ScArcMain)) return false;
        if ((val & ScNode) && (val & ScEdgeCommon)) return false;
        if ((val & ScNode) && (val & ScLink)) return false;

        if ((val & ScArcCommon) && (val & ScArcMain)) return false;
        if ((val & ScArcCommon) && (val & ScEdgeCommon)) return false;
        if ((val & ScArcCommon) && (val & ScLink)) return false;

        if ((val & ScArcMain) && (val & ScEdgeCommon)) return false;
        if ((val & ScArcMain) && (val & ScLink)) return false;

        if ((val & ScEdgeCommon) && (val & ScLink)) return false;

        // check constant types
        if ((val & ScConst) && (val & ScVar)) return false;
        if ((val & ScConst) && (val & ScMeta)) return false;

        if ((val & ScVar) && (val & ScMeta)) return false;

        // check positive types
        if ((val & ScPositive) && (val & ScNegative)) return false;


        return true;
    }

    /*! Convert type into string representation
      */
    QString toString() const
    {
        QString res;

        if (check(ScNode))
            res = "node";
        else if (check(ScArcCommon))
            res = "arc common";
        else if (check(ScArcMain))
            res = "arc main";
        else if (check(ScEdgeCommon))
            res = "edge common";
        else if (check(ScLink))
            res = "link";

        if (check(ScConst))
            res += " | const";
        else if (check(ScVar))
            res += " | var";
        else if (check(ScMeta))
            res += " | meta";

        if (check(ScPositive))
            res += " | pos";
        else if (check(ScNegative))
            res += " | neg";
        else
            res += " | fuz";

        if (check(ScTemporary))
            res += " | temp";
        else
            res += " | perm";

        return res;
    }

    _ScElemTypeValue value() const { return val; }

private:
    _ScElemTypeValue val;
};

//! sc-element identifier type
typedef _ScUri ScUri;
//! sc-element type
typedef _ScElementType ScElementType;

//! List of ScUri's
typedef QList<ScUri> ScUriList;
//! Vector of ScUri's
typedef QVector<ScUri> ScUriVector;

class ScMemoryInterface;

// ----- Iterators -----
/*! Iterator parameter
  */
struct ScParam
{
    ScParam() :
        m_is_type(false),
        m_value(ScUri().value())
    {
    }

    ScParam(const ScElementType &type) :
        m_is_type(true),
        m_value(type.value())
    {
    }

    ScParam(const ScUri &uri) :
        m_is_type(false),
        m_value(uri.value())
    {
    }

    //! Return uri value
    ScUri uri() const { Q_ASSERT(!m_is_type); return ScUri(m_value.toULongLong()); }
    //! Return type value
    ScElementType type() const { Q_ASSERT(m_is_type); return ScElementType(m_value.toLongLong()); }
    //! Check if parameter contains uri value
    bool is_uri() const { return !m_is_type; }
    //! Check if paramater contains type value
    bool is_type() const { return m_is_type; }

    bool m_is_type;
    QVariant m_value;
};

static inline ScParam scParamUri(ScUri x) { return ScParam(x); }
static inline ScParam scParamUri(quint64 x) { return ScParam(ScUri(x)); }
static inline ScParam scParamType(ScElementType x) { return ScParam(x); }
static inline ScParam scParamType(_ScElemTypeValue x) { return ScParam(ScElementType(x)); }

/*! Structure to store template for sc-construction that contains from 3 or 5 sc-elements
  */
struct ScTemplate
{
protected:
    //! Tempalte arguments
    ScParam mParams[5];
    //! Number of template arguments
    quint8 mCount;

public:
    /*! Construct empty template
      */
    ScTemplate() : mCount(0)
    {
    }

    /*! Construct template for 3 sc-elements
      * @param p0 Zero parameter of search template.
      * @param p1 First parameter of search template.
      * @param p2 Second parameter of search template.
      */
    ScTemplate(const ScParam &p0,
               const ScParam &p1,
               const ScParam &p2) :
        mCount(3)
    {
        mParams[0] = p0;
        mParams[1] = p1;
        mParams[2] = p2;
    }

    /*! Construct template for 5 sc-elements
      * @param p0 Zero parameter of search template.
      * @param p1 First parameter of search template.
      * @param p2 Second parameter of search template.
      * @param p3 Third parameter of search template.
      * @param p4 Fourth parameter of search template.
      */
    ScTemplate(const ScParam &p0,
               const ScParam &p1,
               const ScParam &p2,
               const ScParam &p3,
               const ScParam &p4) :
        mCount(5)
    {
        mParams[0] = p0;
        mParams[1] = p1;
        mParams[2] = p2;
        mParams[3] = p3;
        mParams[4] = p4;
    }

    //! Return number of template parametes
    inline quint8 count() const { return mCount; }
    /*! Return parameter with specified index
      * @param index Paramater index
      */
    inline const ScParam& param(quint8 index) const { Q_ASSERT(index < mCount); return mParams[index]; }

    /*! Set paramater value by index
      * @param index Parameter index
      * @param p Parameter value
      */
    inline void set(quint8 index, const ScParam &p) { Q_ASSERT(index < mCount); mParams[index] = p;}

    ScTemplate& operator <<(const ScUri &uri)
    {
        if (mCount >= 5) SuiExcept(SuiExceptionInvalidParameters,
                                   "Template can't have more then 5 parameters",
                                   "ScMemoryInterface::operator<<()");
        mParams[mCount++] = ScParam(uri);
        return *this;
    }
    ScTemplate& operator <<(const ScElementType &type)
    {
        if (mCount >= 5) SuiExcept(SuiExceptionInvalidParameters,
                                   "Template can't have more then 5 parameters",
                                   "ScMemoryInterface::operator<<()");
        mParams[mCount++] = ScParam(type);
        return *this;
    }

    /*! Clear template. Reset parameters count to zero
      */
    ScTemplate& clear() { mCount = 0; return *this; }

};

/*! That class provide mechanism to iterate search results.
  * @note After creation iterator have null position, so you need
  * to call has_next and next methods to get first value if it exists.
  * Initialize when iterator created, it already setup to first result
  * Usge example:
  * ...
  * while (!it->is_over())
  * {
  *     ... your code that use iterator values
  *     it->next();
  * }
  */
class ScIteratorInterface
{
public:
    virtual ~ScIteratorInterface() {}

public:
    /*! Check if iterator is over
      * @return If iterator have no more elements, then return true; otherwise return false
      */
    virtual bool is_over() const = 0;

    /*! Get sc-uri of element in specified position.
      * Number of positions depend on search results. For example if you search simple construction with
      * 3 elements, then iterator contain 3 values for each search result. So if you need to get first
      * component in one of results, then you need to call that function with \p num = 0
      * @param num element position
      * @return Return uri of sc-element in specified position for current search result
      */
    virtual ScUri value(int num) const = 0;

    /*! Move iterator to next search result
      */
    virtual void next() = 0;
};


// ----- Events -----
typedef enum
{
    //! Unknown event type
    ScEventUnknown = 0,
    //! Output edge/arc from specified sc-element added
    ScEventOutputEdgeAdded,
    //! Input edge/arc to specified sc-element added
    ScEventInputEdgeAddded,
    //! Output edge/arc from specified sc-element removed
    ScEventOutputEdgeRemoved,
    //! Input edge/arc to specified sc-element removed
    ScEventInputEdgeRemoved,
    //! Content of specified sc-link changed
    ScEventContentChanged,
    //! Type of specified sc-element changed
    ScEventTypeChanged,
    //! Specified sc-element deleted from memory
    ScEventDeleted,

    //! Output edge/arc from specified sc-element will be added
    ScEventPreOutputEdgeAdded,
    //! Input edge/arc to specified sc-element will be added
    ScEventPreInputEdgeAdded,
    //! Output edge/arc from specified sc-element will be removed
    ScEventPreOutputEdgeRemoved,
    //! Input edge/arc to specified sc-element will be removed
    ScEventPreInputEdgeRemoved,
    //! Content of specified sc-link will be changed
    ScEventPreContentChanged,
    //! Type of specified sc-element will be changed
    ScEventPreTypeChanged,
    //! Specified sc-element will be deleted from memory
    ScEventPreDeleted
}ScEventType;

/*! SC-memory event. It used to pass data into event callback.
  * It contains uri of listened sc-element that can be get with ScEvent::uri() function.
  * Also you can get type of ScEvent with ScEvent::type() function.
  */
class ScEvent
{
public:
    /*! Construct event
      * @param type Event type.
      * @param _uri ScUri of listened sc-element.
      * @param _templ ScTemplate that contains event arguments.
      * @param _memory Pointer to used sc-memory interface, that will be passed into callback
      */
    explicit ScEvent(ScEventType type, ScUri _uri, const ScTemplate &_templ, ScMemoryInterface *_memory) :
        m_type(type),
        m_uri(_uri),
        m_template(_templ),
        m_memory_interface(_memory)
    {
        Q_ASSERT(m_memory_interface != 0);
    }

    virtual ~ScEvent() {}

    //! Return uri of sc-element that was listened for event
    const ScUri& uri() const { return m_uri; }

    //! Return template that contains arguments
    const ScTemplate& scTemplate() const { return m_template; }

    //! Return memory interface, that must be used to work with sc-memory
    ScMemoryInterface* memory() { return m_memory_interface; }

protected:
    //! Event type
    ScEventType m_type;
    //! Uri of sc-element that was listened for event
    ScUri m_uri;
    //! Event arguments
    ScTemplate m_template;
    //! Pointer to sc-memory interface that need to be used for work in callback
    ScMemoryInterface *m_memory_interface;
};

/*! Event callback interface
  * It used for callback any events in sc-memory
  */
class ScEventCallbackInterface
{
public:
    virtual ~ScEventCallbackInterface() {}

    /*! Event callback function
      * @param event ScEvent structure, that contains whole information about handled event
      * @return Return true, if event processed; otherwise return false.
      */
    virtual bool eventCallBack(const ScEvent &event) = 0;

};



/*! Interface for sc-memory models
  */
class ScMemoryInterface
{

protected:
    virtual ~ScMemoryInterface() {}

public:

    /*! Print debug informtaion about specified sc-element
      */
    virtual void _printEl(const ScUri &uri) = 0;


    /*! Initialize sc-memory in specified path
      * @param path sc-memory storage path
      * @return Return true, if storage initalized wihtout errors; ohterwise return false.
      */
    virtual bool initialize(const QString &path) = 0;

    /*! Shutdown sc-memory
      */
    virtual void shutdown() = 0;

    /*! Create new sc-element with specified type.
      * Mixing of types in groups (sc-element type, sc-element constant,
      * sc-element positivity, sc-element premanently) will get you an error.
      * @param type New sc-element type.
      *
      * @return sc-uri of created element. If element wasn't created, then
      * return ScUriEmpty.
      * @see ScMemoryInterface::erase_el
      */
    virtual ScUri gen_el(const ScElementType &type) = 0;

    /*! Erase element with specified identifier from sc-memory.
      * @note sc-element will be removed imideately. Anoother words,
      * it wouldn't exists after returning from that method.
      * @param uri sc-uri of element that need to be erased.
      * @return Return true, if element was erased; otherwise return false
      * @see ScMemoryInterface::gen_el
      */
    virtual bool erase_el(const ScUri &uri) = 0;

    /*! Set begin element for sc-arc (sc-edge).
      * @param uri sc-uri of sc-arc (sc-edge).
      * @param beg_el sc-uri of begin sc-element.
      * @return Return true, if begin element for \p uri changed; otherwise return false
      * @attention Parameter \p uri can just be a sc-element with
      * ScEdgeCommon, ScArcCommon and ScArcMain types. Other type, like
      * ScNode or ScLink will be wrong.
      * @see ScMemoryInterface::set_end, ScMemoryInterface::get_beg, ScMemoryInterface::get_end
      */
    virtual bool set_beg(const ScUri &uri, const ScUri &beg_el) = 0;

    /*! Get begin sc-element for sc-arc (sc-edge)
      * @param uri URI of sc-arc (sc-edge) to get begin sc-element
      * @return Returns uri of begin sc-element for sc-arc (sc-edge) with \p uri.
      * If there are no begin element, then retur empty sc_uri.
      * @see ScMemoryInterface::set_end, ScMemoryInterface::get_end, ScMemoryInterface::set_beg
      */
    virtual ScUri get_beg(const ScUri &uri) = 0;


    /*! Set end element for sc-arc (sc-edge)
      * @param uri sc-uri of sc-arc (sc-edge).
      * @param end_el sc-uri of end sc-element.
      * @return Return true, if end element for \p uri changed; otherwise return false
      * @attention Parameter \p uri can just be a sc-element with
      * ScEdgeCommon, ScArcCommon and ScArcMain types. Other type, like
      * ScNode or ScLink will be wrong.
      * @see ScMemoryInterface::set_beg, ScMemoryInterface::get_end
      * @see ScMemoryInterface::get_end, ScMemoryInterface::get_beg, ScMemoryInterface::set_beg
      */
    virtual bool set_end(const ScUri &uri, const ScUri &end_el) = 0;

    /*! Get end sc-element for sc-rc (sc-edge)
      * @param uri URI of sc-arc (sc-edge) to get end sc-element
      * @return Returns uri of end sc-element for sc-arc (sc-edge) with \p uri.
      * If there are no end element, then retur empty sc_uri.
      * @throw ScExceptionInvalidType Throws if type of sc-element with \p uri is invalid. It must be one of three types:
      * ScEdgeCommon, ScArcCommon, ScArcMain
      * @throw ScExceptionElementNotExist Throws if sc-element with \p uri doesn't exist
      * @see ScMemoryInterface::set_end, ScMemoryInterface::get_beg, ScMemoryInterface::set_beg
      */
    virtual ScUri get_end(const ScUri &uri) = 0;

    /*! Set content for sc-link
      * @param uri sc-uri of sc-link to change content
      * @param device Device to read content data
      * @return Return true, if content for \p uri changed; otherwise return false
      * @attention \p uri must point to sc-link.
      * @see ScMemoryInterface::open_content, ScMemoryInterface::close_content, ScMemoryInterface::is_content_opened
      */
    virtual bool set_content(const ScUri &uri, QIODevice &device) = 0;

    /*! Open sc-link content for reading
      * @param uri URI of sc-link to open content
      * @return Returns pointer to IODevice interface for content data reading(writing).
      * @note Do not use delete function to destroy IODevice object. Use ScMemoryInterface::close_content
      * function.
      * @throw ScExceptionInvalidType Throws if sc-element with \p uri isn't sc-link
      * @throw ScExceptionElementNotExist Throws if s-element with \p uri doesn't exist
      * @see ScMemoryInterface::set_content, ScMemoryInterface::close_content, ScMemoryInterface::is_content_opened
      */
    virtual QIODevice* open_content(const ScUri &uri) = 0;

    /*! Close sc-link content
      * @param device Pointer to IODevice that was returned by open_content function.
      * @return Return true, if content closed; otherwise return false.
      */
    virtual bool close_content(QIODevice *device) = 0;

    /*! Check if content of sc-link with specified \p uri is opened
      * @return Returns true if content is opened; otherwise return false.
      */
    virtual bool is_content_opened(const ScUri &uri) const = 0;

    /*! Find sc-link with specified data
      * @param device IO device interface to read content data for finding
      * @param result List that contains search result
      * @return True if any contents was founded; otherwise return false.
      */
    virtual bool find_content(QIODevice &device, ScUriList &result) = 0;

    /*! Find sc-link that contains string. That function is equivalent to
      * find_content, but it convert string data into specified encoding.
      * That need, because different realizations of ScMemory can use different
      * string encoding in sources.
      * @param str String to find.
      * @param result List that contains search result
      *
      * @see ScMemoryInterface::find_content
      */
    virtual bool find_str_content(const QString &str, ScUriList &result) = 0;

    /*! Get string from IODevice. This function represent IODevice data into
      * QString. It used, because different realizations of ScMemory can use different
      * string encoding in sources.
      * @param device IO device interface to read content data for deconde
      * @return Return decoded string, if it can be decoded; otherwise return empty string
      */
    virtual QString decode_str_content(QIODevice &device) = 0;

    /*! Set type for specified element
      * @param uri sc-uri of sc-element to change type
      * @param type New type of sc-element with specified \p uri
      * @param Return true, if type for \p uri changed; otherwise return false.
      * @see ScMemoryInterface::get_el_type
      */
    virtual bool set_el_type(const ScUri &uri, const ScElementType &type) = 0;

    /*! Get type of element with specified uri
      * @param uri sc-uri of sc-element to get type
      * @return Return type of sc-element with specified \p uri
      * @see ScMemoryInterface::set_el_type
      */
    virtual ScElementType get_el_type(const ScUri &uri) const = 0;

    /*! Create iterator with results of 3 elements construction search.
      * Template: 0 ----1----> 2
      *                 ^
      *                 |
      *                 3
      *                 |
      *                 4
      * Each parameter in template can be one of two values: sc-element uri, sc-element type.
      * If you set parameter with sc-element type values, then it will be any element (with any uri).
      * Otherwise if you set paramater with specified uri, then it will be constant in search template.
      * @param templ Search template
      * @see ScMemoryInterface::destroy_iterator, ScMemoryInterface::create_iterator5
      */
    virtual ScIteratorInterface* create_iterator(const ScTemplate &templ) = 0;

    /*! Destroys iterator
      * @param it Pointer to iterator that need to be destroyed
      * @return Return ture, if iterator destroyed; otherwise return false
      * @attention Iterator will be destoyed and memory will be free. So you
      * can't use it any more./
      * @see ScMemoryInterface::create_iterator3, ScMemoryInterface::create_iterator5
      */
    virtual bool destroy_iterator(ScIteratorInterface *it) = 0;


    /*! Connects callback to specified event
      * @param eventType Event type @see ScEventType
      * @param uri sc-element uri that we want to listen
      * @param callback Pointer to callback interface
      * @return Return true, if callback connected; otherwise return false.
      */
    virtual bool connect_callback(const ScEventType &eventType,
                                  const ScUri &uri,
                                  ScEventCallbackInterface *callback) = 0;

    /*! Disconnect callback from specified event
      * @param eventType Event type @see ScEventType
      * @param uri ScUri of sc-element that doesn't need to be listened more
      * @param callback Pointer to callback interface that need to be deisconnected
      * @return Return true, if specified \p callback was disconnected; otherwise return false.
      */
    virtual bool disconnect_callback(const ScEventType &eventType,
                                     const ScUri &uri,
                                     ScEventCallbackInterface *callback) = 0;

    /*! Disconnect callback from all events
      * @param callback Pointer to callback interface, that need to be disconnected
      * @return Return true, if callback disconnected; otherwise return false
      */
    virtual bool disconnect_callback(ScEventCallbackInterface *callback) = 0;
};

class ScMemoryFactoryInterface
{
public:
    virtual ~ScMemoryFactoryInterface() {}

    /*! Create new instance of sc-ememory
      * @return Return pointer to created instance
      */
    virtual ScMemoryInterface* createInstance() = 0;
};

/*! Class that wrap iterator and make it safe on exceptions throw.
  * It destroy iterator automaticaly when object destroys.
  */
class ScSafeIterator
{
public:
    explicit ScSafeIterator(ScMemoryInterface *memory,
                            const ScTemplate &templ) :
        mMemory(memory),
        mIterator(0)
    {
        Q_ASSERT(mMemory != 0);
        mIterator = mMemory->create_iterator(templ);
    }

    virtual ~ScSafeIterator() { mMemory->destroy_iterator(mIterator); }

    //! @copydoc ScIteratorInterface::value
    ScUri value(int num) const { return mIterator->value(num); }
    //! @copydoc ScIteratorInterface::is_over
    bool is_over() const { return mIterator->is_over(); }
    //! @copydoc ScIteratorInterface::next
    void next() { mIterator->next(); }

private:
    // pointer to sc memory interface
    ScMemoryInterface *mMemory;
    // pointer to iterator
    ScIteratorInterface *mIterator;
};

Q_DECLARE_INTERFACE(ScMemoryInterface,
                    "com.OSTIS.sc.ScMemoryInterface/1.0");
Q_DECLARE_INTERFACE(ScIteratorInterface,
                    "com.OSTIS.sc.ScIteratorInterface/1.0");
Q_DECLARE_INTERFACE(ScEventCallbackInterface,
                    "com.OSTIS.sc.ScEventCallbackInterface/1.0");
Q_DECLARE_INTERFACE(ScMemoryFactoryInterface,
                    "com.OSTIS.sc.ScMemoryFactoryInterface/1.0");

#endif // SC_INTERFACES_H
