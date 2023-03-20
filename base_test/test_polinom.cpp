

#include <gtest.h>
#include "polynom.h"




TEST(Monom, can_add_monoms)
{
    Monom m(2, 123);
    ASSERT_NO_THROW(m + m);
}

TEST(Monom, can_sub_monoms)
{
    Monom m1(10, 14);
    Monom m2(9, 14);

    Monom res = m1 - m2;

    ASSERT_EQ(1, res.get_coef());
}

TEST(Monom, can_multiply_monoms)
{
    Monom m1(10, 14);
    Monom m2(10, 14);

    Monom res = m1 * m2;

    ASSERT_EQ(100, res.get_coef());
}

TEST(Monom, can_multiply_monom_by_const)
{
    Monom m1(10, 14);

    Monom res = m1 * 6;

    ASSERT_EQ(60, res.get_coef());
}


TEST(Polynom, can_create_polinom)
{
    ASSERT_NO_THROW(Polynom p("x+y"));
}

TEST(Polynom, can_assign_polinoms)
{
    Polynom p1("x+y");
    Polynom p2("x+y+z");
    ASSERT_NO_THROW(p2 = p1);
}

TEST(Polynom, can_add_pol_1)
{
    std::string pol1 = "x2-y2-z2";
    std::string pol2 = "3x2+y2+z2";

    Polynom p1(pol1);
    Polynom p2(pol2);
    Polynom p3 = p2 + p1;
    EXPECT_EQ(p3, Polynom("4x2"));;
}

TEST(Polynom, can_add_pol_2)
{
    std::string pol1 = "-z2+87x9+0x1-9y2+9y2";
    std::string pol2 = "+z2";

    Polynom p1(pol1);
    Polynom p2(pol2);
    Polynom p3 = p2 + p1;
    EXPECT_EQ(p3, Polynom("87x9"));;
}

TEST(Polynom, can_sub_pol)
{
    std::string pol1 = "-14.88x2y5";
    std::string pol2 = "-14.88x2y5+2";

    Polynom p1(pol1);
    Polynom p2(pol2);
    Polynom p3 = p1 - p2;


    EXPECT_EQ(Polynom("-2"), p3);
}

TEST(Polynom, can_myltiply_pol)
{
    std::string pol1 = "x2-y2";
    std::string pol2 = "x2";

    Polynom p1(pol1);
    Polynom p2(pol2);
    Polynom p3 = p1 * p2;

    EXPECT_EQ(Polynom("x4-x2y2"), p3);
}

TEST(Polynom, can_myltiply_pol_2)
{
    std::string pol1 = "x2+y2";
    std::string pol2 = "x2-y2";

    Polynom p1(pol1);
    Polynom p2(pol2);
    Polynom p3 = p1 * p2;

    EXPECT_EQ(Polynom("x4-y4"), p3);
}

TEST(Polynom, can_multiply_pol_on_const)
{
    std::string pol1 = "2x2y5";

    Polynom p1(pol1);

    EXPECT_EQ(Polynom("6x2y5"), p1 * 3);
}

TEST(Polynom, can_derivative)
{
    std::string pol1 = "x2+y2";
    std::string pol2 = "2x";

    Polynom p1(pol1);
    Polynom p2(pol2);

    EXPECT_EQ( p1.derivative('x'), p2);
}

TEST(Polynom, can_integral)
{
    std::string pol1 = "3x2+y2";
    std::string pol2 = "1x3+xy2";

    Polynom p1(pol1);
    Polynom p2(pol2);

    EXPECT_EQ(p1.integral('x'), p2);
}

