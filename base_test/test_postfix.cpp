

#include "postfix.h"
#include <gtest.h>

TEST(TPostfix, can_create_postfix)
{
  ASSERT_NO_THROW(TPostfix p);
}

TEST(TPostfix, can_get_infix)
{
  TPostfix p;
  std::string form = "dx(as+bsa)";
  p.set_infix(form);
  std::string in = "dx(as+bsa)";
  EXPECT_EQ(in, p.get_infix());
}
TEST(TPostfix, can_get_postfix)
{
  TPostfix p;
  std::string form = "dx(as+bsa)";
  p.set_infix(form);
  p.to_postfix();
  std::string post = "as|bsa|+_|dx|";
  EXPECT_EQ(post, p.get_postfix());
}
