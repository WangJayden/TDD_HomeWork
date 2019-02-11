// Module test code

#include <gmock/gmock.h>

#include "Module/Module.h"

using namespace testing;

// Classic Assertion:
//   Fatal assertion          Nonfatal assertion      Verifies
// ASSERT_EQ(val1, val2);   EXPECT_EQ(val1, val2);   val1 == val2
// ASSERT_NE(val1, val2);   EXPECT_NE(val1, val2);   val1 != val2
// ASSERT_LT(val1, val2);   EXPECT_LT(val1, val2);   val1 < val2
// ASSERT_LE(val1, val2);   EXPECT_LE(val1, val2);   val1 <= val2
// ASSERT_GT(val1, val2);   EXPECT_GT(val1, val2);   val1 > val2
// ASSERT_GE(val1, val2);   EXPECT_GE(val1, val2);   val1 >= val2
// 
// Test Case:
//   TEST( TestSuiteName, TestName ) {...}
//
// or using test fixture:
//   class TestSuiteName : public Test
//   {
//   protected:
//        virtual void SetUp() {}
// 	      CModule	m_kModule;    // your test module
//   };
//   TEST_F( TestSuiteName, TestName ) {...}

TEST( BudgetSearch, DefaultValue )
{
    CBudgetSearch kBudgetSearch;
    EXPECT_EQ( kBudgetSearch.GetTotalBudget(), 0 );
}

TEST( BudgetSearch, SetBudget_20190131_true )
{
    CBudgetSearch kBudgetSearch;
    EXPECT_EQ( kBudgetSearch.SetBudget( 2019, 1, 31 ), true );
}

TEST( BudgetSearch, SetBudget_20191330_false )
{
    CBudgetSearch kBudgetSearch;
    EXPECT_EQ( kBudgetSearch.SetBudget( 2019, 13, 30 ), false );
}

TEST( BudgetSearch, SetBudget_20190130_false )
{
    CBudgetSearch kBudgetSearch;
    EXPECT_EQ( kBudgetSearch.SetBudget( 2019, 1, 30 ), false );
}

TEST( BudgetSearch, SetSearchPeriod_20190101to20190131_true )
{
    CBudgetSearch kBudgetSearch;
    EXPECT_EQ( kBudgetSearch.SetSearchPeriod( 2019, 1, 1, 2019, 1, 31 ), true );
}

TEST( BudgetSearch, SetSearchPeriod_20190101to20190101_true )
{
    CBudgetSearch kBudgetSearch;
    EXPECT_EQ( kBudgetSearch.SetSearchPeriod( 2019, 1, 1, 2019, 1, 1 ), true );
}

TEST( BudgetSearch, SetSearchPeriod_20190131to20190130_false )
{
    CBudgetSearch kBudgetSearch;
    EXPECT_EQ( kBudgetSearch.SetSearchPeriod( 2019, 1, 31, 2019, 1, 30 ), false );
}

TEST( BudgetSearch, GetTotalBudget_Budget20190131Period20190101to20190131_31 )
{
    CBudgetSearch kBudgetSearch;
    EXPECT_EQ( kBudgetSearch.SetBudget( 2019, 1, 31 ), true );
    EXPECT_EQ( kBudgetSearch.SetSearchPeriod( 2019, 1, 1, 2019, 1, 31 ), true );
    EXPECT_EQ( kBudgetSearch.GetTotalBudget(), 31 );
}

TEST( BudgetSearch, GetTotalBudget_Budget20190228Period20190201to20190228_28 )
{
    CBudgetSearch kBudgetSearch;
    EXPECT_EQ( kBudgetSearch.SetBudget( 2019, 2, 28 ), true );
    EXPECT_EQ( kBudgetSearch.SetSearchPeriod( 2019, 2, 1, 2019, 2, 28 ), true );
    EXPECT_EQ( kBudgetSearch.GetTotalBudget(), 28 );
}

TEST( BudgetSearch, GetTotalBudget_Budget20190228Period20190215to20190315_14 )
{
    CBudgetSearch kBudgetSearch;
    EXPECT_EQ( kBudgetSearch.SetBudget( 2019, 2, 28 ), true );
    EXPECT_EQ( kBudgetSearch.SetSearchPeriod( 2019, 2, 15, 2019, 3, 15 ), true );
    EXPECT_EQ( kBudgetSearch.GetTotalBudget(), 14 );
}

TEST( BudgetSearch, GetTotalBudget_Budget20190331Period20190301to20190301_1 )
{
    CBudgetSearch kBudgetSearch;
    EXPECT_EQ( kBudgetSearch.SetBudget( 2019, 3, 31 ), true );
    EXPECT_EQ( kBudgetSearch.SetSearchPeriod( 2019, 3, 1, 2019, 3, 1 ), true );
    EXPECT_EQ( kBudgetSearch.GetTotalBudget(), 1 );
}

TEST( BudgetSearch, GetTotalBudget_Budget20190228And20190393Period20190228to20190301_4 )
{
    CBudgetSearch kBudgetSearch;
    EXPECT_EQ( kBudgetSearch.SetBudget( 2019, 2, 28 ), true );
    EXPECT_EQ( kBudgetSearch.SetBudget( 2019, 3, 93 ), true );
    EXPECT_EQ( kBudgetSearch.SetSearchPeriod( 2019, 2, 28, 2019, 3, 1 ), true );
    EXPECT_EQ( kBudgetSearch.GetTotalBudget(), 4 );
}

TEST( BudgetSearch, GetTotalBudget_Budget20190460And201906120Period20190430to20190715_122 )
{
    CBudgetSearch kBudgetSearch;
    EXPECT_EQ( kBudgetSearch.SetBudget( 2019, 4, 60 ), true );
    EXPECT_EQ( kBudgetSearch.SetBudget( 2019, 6, 120 ), true );
    EXPECT_EQ( kBudgetSearch.SetSearchPeriod( 2019, 4, 30, 2019, 7, 15 ), true );
    EXPECT_EQ( kBudgetSearch.GetTotalBudget(), 122 );
}

TEST( BudgetSearch, GetTotalBudget_Budget20190131And202001310Period20190131to20200101_2 )
{
    CBudgetSearch kBudgetSearch;
    EXPECT_EQ( kBudgetSearch.SetBudget( 2019, 1, 31 ), true );
    EXPECT_EQ( kBudgetSearch.SetBudget( 2020, 1, 31 ), true );
    EXPECT_EQ( kBudgetSearch.SetSearchPeriod( 2019, 1, 31, 2020, 1, 1 ), true );
    EXPECT_EQ( kBudgetSearch.GetTotalBudget(), 2 );
}
