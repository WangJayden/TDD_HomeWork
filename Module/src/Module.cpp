#include "Module.h"

std::map< unsigned int, unsigned int > g_kMonthDaysMap = { {  1, 31 },
                                                           {  2, 28 },
                                                           {  3, 31 },
                                                           {  4, 30 },
                                                           {  5, 31 },
                                                           {  6, 30 },
                                                           {  7, 31 },
                                                           {  8, 31 },
                                                           {  9, 30 },
                                                           { 10, 31 },
                                                           { 11, 30 },
                                                           { 12, 31 } };

unsigned int CBudgetSearch::GetTotalBudget()
{
    m_uTotalBudget = 0;

    for ( unsigned int y = m_uStartYear; y <= m_uEndYear; ++y )
    {
        for ( unsigned int m = m_uStartMonth; m <= m_uEndMonth; ++m )
        {
            unsigned int uDate = y * 100 + m;
            auto it = m_kBudgetMap.find( uDate );
            if ( m_kBudgetMap.end() == it )
            {
                continue;
            }
            unsigned int uBudget = m_kBudgetMap[ uDate ];
            
            unsigned int uStartDay;
            if ( y == m_uStartYear && m == m_uStartMonth )
            {
                uStartDay = m_uStartDay;
            }
            else
            {
                uStartDay = 1;
            }

            unsigned int uEndDay;
            if ( y == m_uEndYear && m == m_uEndMonth )
            {
                uEndDay = m_uEndDay;
            }
            else
            {
                uEndDay = g_kMonthDaysMap[ m ];
            }

            unsigned int uPeriodDay = uEndDay - uStartDay + 1;
            m_uTotalBudget += ( uBudget / g_kMonthDaysMap[ m ] ) * uPeriodDay;
        }
    }

    return m_uTotalBudget;
}

bool CBudgetSearch::SetBudget( unsigned int uYear, unsigned int uMonth, unsigned int uBudget )
{
    auto it = g_kMonthDaysMap.find( uMonth );
    if ( g_kMonthDaysMap.end() == it )
    {
        return false;
    }
    if ( uBudget % it->second != 0 )
    {
        return false;
    }

    unsigned int uDate = uYear * 100 + uMonth;
    m_kBudgetMap.insert( { uDate, uBudget } );
    return true;
}

bool CBudgetSearch::SetSearchPeriod( unsigned int uStartYear,
                                     unsigned int uStartMonth,
                                     unsigned int uStartDay,
                                     unsigned int uEndYear,
                                     unsigned int uEndMonth,
                                     unsigned int uEndDay )
{
    // 檢查月
    if ( uStartMonth > 12 || uEndMonth > 12 || uStartMonth == 0 || uEndMonth == 0 )
    {
        return false;
    }
    // 檢查天
    if ( uStartDay > g_kMonthDaysMap[ uStartMonth ]
      || uEndDay > g_kMonthDaysMap[ uEndMonth ]
      || uStartDay == 0
      || uEndDay == 0 )
    {
        return false;
    }
    // 檢查 Start End
    unsigned int uStartDate = uStartYear * 10000 + uStartMonth * 100 + uStartDay;
    unsigned int uEndDate   = uEndYear * 10000 + uEndMonth * 100 + uEndDay;
    if ( uStartDate > uEndDate )
    {
        return false;
    }

    m_uStartYear  = uStartYear;
    m_uStartMonth = uStartMonth;
    m_uStartDay   = uStartDay;
    m_uEndYear    = uEndYear;
    m_uEndMonth   = uEndMonth;
    m_uEndDay     = uEndDay;
    return true;
}