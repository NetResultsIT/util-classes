#ifndef STATSVARIABLE_H
#define STATSVARIABLE_H
/*
 *  StatsVariable.h
 *  (c) 2017 NetResults Srl
 */

#include <stdint.h>

#include <QDebug>

/*!
 *  Template Class to manage a variable that stores min, max and avg values of a variable
 *  Each time a new value is stored, the stats are updated
 */
template<class T>
class StatsVariable
{
    bool m_initialized;
    uint64_t m_numberOfValues;

    T m_minVal;
    T m_maxVal;
    double m_avgVal;
    T m_firstVal;
    T m_lastVal;

protected:
    void init(T aVal) {
        this->m_minVal   = aVal;
        this->m_maxVal   = aVal;
        this->m_firstVal = aVal;
        this->m_lastVal  = aVal;
        this->m_avgVal   = aVal;
        m_numberOfValues = 1;
        m_initialized    = true;
    }

    void updateStats(T aVal) {
        if (aVal < m_minVal) m_minVal = aVal;
        if (aVal > m_maxVal) m_maxVal = aVal;
        m_lastVal = aVal;
        m_numberOfValues++;

        //newavg: oldavg + ((newval - oldavg) / oldsize+1))
        m_avgVal = m_avgVal + ((aVal - m_avgVal) / m_numberOfValues);
    }

public:
    StatsVariable()
       : m_initialized(false)
       , m_numberOfValues(0)
    { /* empty ctor */ }
    StatsVariable(T aVal)
    { init(aVal); }

    /*
     *  assignement
     */
    const T& operator =(const T& rhs)
    {
        if ( !m_initialized ) {
            init(rhs);
        } else {
            updateStats(rhs);
        }
        return rhs;
    }

    /*
     *  comparison
     */
    bool operator ==(const T& rhs) const
    {
        return ( this->m_lastVal == rhs ) ? true : false;
    }



    /*
     *  stream
     */
    std::ostream& operator <<(std::ostream &os) const
    {
        return os << this->m_lastVal;
    }


    inline T last() const   { return m_lastVal;  }
    inline T first() const  { return m_firstVal; }
    inline T max() const    { return m_maxVal;   }
    inline T min() const    { return m_minVal;   }

    inline double avg() const    { return m_avgVal;   }
    inline uint64_t numValues() const   { return m_numberOfValues;   }
};


#ifdef QT_CORE_LIB_REMOVEME
    QDebug operator<< (QDebug dbg, const StatsVariable<T>& rhs)
    {
        dbg.nospace() << rhs.m_lastVal;
        return dbg;
    }
#endif


#endif // STATSVARIABLE_H
