#include <gtest.h>
#include "table.h"

// #include <gtest.h>
 #include "list_table.h"

//#include "../gtest/gtest.h"
//#include "../base/array_table.h"

TEST(ListTable, can_create_table)
{
    ASSERT_NO_THROW(ListTable tab);
}
TEST(ListTable, can_create_table_by_vector)
{
    std::vector<TableString> a(4);
    ASSERT_NO_THROW(ListTable tab(a));
}
TEST(ListTable, can_insert_elem_in_tab)
{
    ListTable tab;
    TableBody rec;
    EXPECT_EQ(tab.insert("1", rec), true);
}

TEST(ListTable, can_insert_elem_in_tab_when_its_not_empty)
{
    ListTable tab;
    TableBody rec1;
    tab.insert("1", rec1);
    EXPECT_EQ(tab.insert("2", rec1), true);
}

TEST(ListTable, cant_insert_elem_with_same_key)
{
    ListTable tab;
    TableBody rec1;
    TableBody rec2;
    tab.insert("1", rec1);

    EXPECT_EQ(tab.insert("1", rec1), false);
}

TEST(ListTable, cant_find_when_is_empty)
{
    ListTable tab;
    TableBody rec1;

    EXPECT_EQ(tab.find("2"), nullptr);
}

TEST(ListTable, can_find_elem)
{
    ListTable tab;
    Polynom poly("x+y");
    TableBody rec1(poly);
    tab.insert("1", rec1);

    EXPECT_EQ(tab.find("1")->poly_string, "+1x+1y");
}

TEST(ListTable, cant_find_elem)
{
    ListTable tab;
    Polynom poly("x+y");
    TableBody rec1(poly);
    tab.insert("1", rec1);

    EXPECT_EQ(tab.find("2"), nullptr);
}

TEST(ListTable, cant_delete_elem_when_its_empty)
{
    ListTable tab;

    EXPECT_EQ(tab.erase("1"), false);
}

TEST(ListTable, can_delete_existing_elem)
{
    ListTable tab;
    TableBody rec1;
    tab.insert("1", rec1);
    tab.erase("1");

    EXPECT_EQ(tab.get_data_count(), 0);
}

TEST(ListTable, cant_delete_non_existing_elem)
{
    ListTable tab;
    TableBody rec1;
    tab.insert("1", rec1);

    EXPECT_EQ(tab.erase("2"), false);
}

TEST(ListTable, can_check_is_tab_ended_1)
{
    ListTable tab;
    TableBody rec1;
    tab.insert("1", rec1);
    tab.insert("2", rec1);
    tab.insert("3", rec1);
    tab.reset();
    tab.go_next();
    tab.go_next();
    tab.go_next();

    EXPECT_EQ(tab.is_tab_ended(), true);
}

TEST(ListTable, can_go_next)
{
    ListTable tab;
    TableBody rec1;
    tab.insert("1", rec1);
    tab.insert("2", rec1);
    tab.reset();
    tab.go_next();

    EXPECT_EQ(tab.get_value()->get_key(), "2");
}

TEST(ListTable, cant_go_next)
{
    ListTable tab;
    TableBody rec1;
    tab.insert("1", rec1);
    tab.reset();
    
    EXPECT_EQ(tab.go_next(), true);
    tab.reset();
    tab.insert("2", rec1);
    EXPECT_EQ(tab.go_next(), false);
}

TEST(ListTable, can_reset)
{
    ListTable tab;
    TableBody rec1;

    tab.insert("1", rec1);
    tab.insert("2", rec1);
    tab.insert("3", rec1);

    tab.reset();
    tab.go_next();
    tab.go_next();
    tab.reset();

    EXPECT_EQ(tab.get_value()->get_key(), "1");
}

TEST(ListTable, can_check_is_tab_ended_2)
{
    ListTable tab;

    EXPECT_EQ(tab.reset(), true);
}

//TEST(ArrayTable, can_get_current_pos)
//{
//    ListTable tab;
//    TableBody rec1;
//
//    tab.insert("1", rec1);
//    tab.insert("2", rec1);
//    tab.insert("3", rec1);
//
//    tab.reset();
//    tab.go_next();
//    tab.go_next();
//
//    EXPECT_EQ(tab.get_current_pos(), 2);
//}
//
//
//TEST(ArrayTable, can_set_current_pos)
//{
//    ListTable tab;
//    TableBody rec1;
//
//    tab.insert("1", rec1);
//    tab.insert("2", rec1);
//    tab.insert("3", rec1);
//
//    EXPECT_EQ(tab.set_current_pos(2), true);
//
//    EXPECT_EQ(tab.get_current_pos(), 2);
//    EXPECT_EQ(tab.get_value()->key, "3");
//}


//TEST(ArrayTable, cant_set_current_pos)
//{
//    ListTable tab;
//    TableBody rec1;
//
//    tab.insert("1", rec1);
//    tab.insert("2", rec1);
//    tab.insert("3", rec1);
//
//    tab.set_current_pos(3);
//
//    EXPECT_EQ(tab.set_current_pos(3), false);
//}

TEST(ListTable, can_get_value)
{
    ListTable tab;
    TableBody rec1;
    tab.insert("1", rec1);
    tab.reset();

    EXPECT_EQ(tab.get_value()->get_key(), "1");
}






//////////////////////////////////////////////////
// UPD TESTS





//
//
//TEST(ListTable, can_create_table)
//{
//    ASSERT_NO_THROW(ListTable tab);
//}
//
//
//TEST(ListTable, can_insert_elem_in_tab)
//{
//    ListTable tab;
//    TableBody rec;
//
//    EXPECT_EQ(tab.insert("1", rec), true);
//    EXPECT_EQ(tab.get_data_count(), 1);
//}
//
//TEST(ListTable, can_insert_elem_in_tab_when_its_not_empty)
//{
//    ListTable tab;
//    TableBody rec1;
//    tab.insert("1", rec1);
//
//    EXPECT_EQ(tab.insert("2", rec1), true);
//    EXPECT_EQ(tab.get_data_count(), 2);
//}
//
//TEST(ListTable, cant_insert_elem_with_same_key)
//{
//    ListTable tab;
//    TableBody rec1;
//    tab.insert("1", rec1);
//
//    EXPECT_EQ(tab.insert("1", rec1), false);
//    EXPECT_EQ(tab.get_data_count(), 1);
//}
//
//TEST(ListTable, cant_find_when_is_empty)
//{
//    ListTable tab;
//    TableBody rec1;
//
//    EXPECT_EQ(tab.find("2"), nullptr);
//}
//
//TEST(ListTable, can_find_elem)
//{
//    ListTable tab;
//    TableBody rec1;
//    tab.insert("1", rec1);
//
//    EXPECT_EQ(tab.find_str("1")->get_key(), "1");
//}
//
//TEST(ListTable, cant_find_elem)
//{
//    ListTable tab;
//    TableBody rec1;
//    tab.insert("1", rec1);
//
//    EXPECT_EQ(tab.find_str("2"), nullptr);
//}
//
//TEST(ListTable, cant_delete_elem_when_its_empty)
//{
//    ListTable tab;
//
//    EXPECT_EQ(tab.erase("1"), false);
//    EXPECT_EQ(tab.get_data_count(), 0);
//}
//
//TEST(ListTable, can_delete_existing_elem)
//{
//    ListTable tab;
//    TableBody rec1;
//    tab.insert("1", rec1);
//    tab.erase("1");
//
//    EXPECT_EQ(tab.get_data_count(), 0);
//}
//
//TEST(ListTable, cant_delete_non_existing_elem)
//{
//    ListTable tab;
//    TableBody rec1;
//    tab.insert("1", rec1);
//
//    EXPECT_EQ(tab.erase("2"), false);
//    EXPECT_EQ(tab.get_data_count(), 1);
//}
//
//TEST(ListTable, can_go_next)
//{
//    ListTable tab;
//    TableBody rec1;
//    tab.insert("1", rec1);
//    tab.insert("2", rec1);
//    tab.reset();
//    tab.go_next();
//
//    EXPECT_EQ(tab.get_value()->get_key(), "2");
//}
//
//TEST(ListTable, cant_go_next)
//{
//    ListTable tab;
//    TableBody rec1;
//    tab.insert("1", rec1);
//    tab.reset();
//
//    EXPECT_EQ(tab.go_next(), true);
//}
//
//TEST(ListTable, can_reset)
//{
//    ListTable tab;
//    TableBody rec1;
//
//    tab.insert("1", rec1);
//    tab.insert("2", rec1);
//
//    tab.reset();
//    tab.go_next();
//    tab.reset();
//
//    EXPECT_EQ(tab.get_value()->get_key(), "1");
//}
//
//
//TEST(ListTable, can_check_is_tab_ended_1)
//{
//    ListTable tab;
//    TableBody rec1;
//    tab.insert("1", rec1);
//    tab.insert("2", rec1);
//    tab.insert("3", rec1);
//    tab.reset();
//    tab.go_next();
//    tab.go_next();
//
//    EXPECT_EQ(tab.go_next(), true);
//}
//
//
//TEST(ListTable, can_check_is_tab_ended_2)
//{
//    ListTable tab;
//
//    EXPECT_EQ(tab.reset(), true);
//}
//
//TEST(ListTable, can_get_current_pos)
//{
//    ListTable tab;
//    TableBody rec1;
//
//    tab.insert("1", rec1);
//    tab.insert("2", rec1);
//    tab.insert("3", rec1);
//
//    tab.reset();
//    tab.go_next();
//    tab.go_next();
//
//    EXPECT_EQ(tab.get_current_pos(), 2);
//}
//
//
//TEST(ListTable, can_set_current_pos)
//{
//    ListTable tab;
//    TableBody rec1;
//
//    tab.insert("1", rec1);
//    tab.insert("2", rec1);
//    tab.insert("3", rec1);
//
//    EXPECT_EQ(tab.set_current_pos(2), true);
//
//    EXPECT_EQ(tab.get_current_pos(), 2);
//    EXPECT_EQ(tab.get_value()->get_key(), "3");
//}
//
//
//TEST(ListTable, cant_set_current_pos)
//{
//    ListTable tab;
//    TableBody rec1;
//
//    tab.insert("1", rec1);
//    tab.insert("2", rec1);
//    tab.insert("3", rec1);
//
//    tab.set_current_pos(3);
//
//
//    EXPECT_EQ(tab.set_current_pos(3), false);
//}
//
//TEST(ListTable, can_get_value)
//{
//    ListTable tab;
//    TableBody rec1;
//    tab.insert("1", rec1);
//    tab.reset();
//
//    EXPECT_EQ(tab.get_value()->get_key(), "1");
//}
//
