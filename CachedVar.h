/*
 *  cachedVar.h
 *  (c) 2106 NetResults Srl
 */

#ifndef NR_UTILCLASSES_CACHED_VAR_H_
#define NR_UTILCLASSES_CACHED_VAR_H_

/*!
 *  Class to manage a variable that caches the old value
 *  Each time a new value is stored, the previous one is cached
 *  It is possible to query the variable to know if the two values are the same
 */
template<class T>
class CachedVariable
{
    bool m_initialized;

    T m_currentVal;
    T m_previousVal;

public:
    CachedVariable() :
        m_initialized(false)
    {}
    CachedVariable(T aVal) :
        m_initialized(true),
        m_currentVal(aVal),
        m_previousVal(aVal)
    {}

    /*
     *  assignement
     */
    const T& operator =(const T& rhs)
    {
        if ( !m_initialized )
        {
            this->m_currentVal = this->m_previousVal = rhs;
            m_initialized = true;
        }
        else
        {
            this->m_previousVal = this->m_currentVal;
            this->m_currentVal = rhs;
        }
        return rhs;
    }

    /*
     *  comparison
     */
    bool operator ==(const T& rhs) const
    {
        return ( this->m_currentVal == rhs ) ? true : false;
    }

    inline bool isEmpty() const { return !m_initialized; }
    inline bool changed() const
    {
        return (this->m_previousVal == this->m_currentVal) ? false : true;
    }
    bool restore()
    {
        if (!m_initialized) return false;
        m_currentVal = m_previousVal;
    }

    operator T() const        { return m_currentVal;  }
    inline T current() const  { return m_currentVal;  }
    inline T old() const      { return m_previousVal; }
    inline T previous() const { return m_previousVal; }
};

#endif /* NR_UTILCLASSES_CACHED_VAR_H_ */
