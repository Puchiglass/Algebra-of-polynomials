#include <gtest.h>
#include "eq_exception.h"
TEST(EqException, can_create_default_exception)
{
    ASSERT_NO_THROW(EqException eq);
}
TEST(EqException, can_create_exception_by_error_codess)
{
    ASSERT_NO_THROW(EqException eq(error_codes::k_NO_ERROR));
}
TEST(EqException, can_get_error_codess)
{
    EqException eq(error_codes::k_UNDEFINED_EXCEPTION);
    EXPECT_EQ(error_codes::k_UNDEFINED_EXCEPTION, eq.get_error());
}
TEST(EqException, can_error_comment)
{
    EqException eq(error_codes::k_UNDEFINED_EXCEPTION);
    EXPECT_EQ("UNDEFINED EXCEPTION", eq.get_comment());
}