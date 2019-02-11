#pragma once
#include <map>

class CBudgetSearch
{
public:
    CBudgetSearch() = default;
    virtual ~CBudgetSearch() = default;

    unsigned int GetTotalBudget();
    bool SetBudget( unsigned int uYear, unsigned int uMonth, unsigned int uBudget );
    bool SetSearchPeriod( unsigned int uStartYear,
                          unsigned int uStartMonth,
                          unsigned int uStartDay,
                          unsigned int uEndYear,
                          unsigned int uEndMonth,
                          unsigned int uEndDay );
protected:
    unsigned int m_uTotalBudget = 0;

    unsigned int m_uStartYear = 0;
    unsigned int m_uStartMonth = 0;
    unsigned int m_uStartDay = 0;
    unsigned int m_uEndYear = 0;
    unsigned int m_uEndMonth = 0;
    unsigned int m_uEndDay = 0;

    std::map< unsigned int/*Date*/, unsigned int/*Budget*/ > m_kBudgetMap;
};