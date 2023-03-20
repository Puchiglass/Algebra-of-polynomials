#include <gtest.h>
#include "red_black_tree.h"

 // #include "../gtest/gtest.h"
 // #include "../base/red_black_tree.h"



TEST(RedBlackTree, can_create_table)
{
    ASSERT_NO_THROW(RedBlackTree tab);
}

TEST(RedBlackTree, can_insert_elem_in_tab)
{
    RedBlackTree tab;
    TableBody rec;

    EXPECT_EQ(tab.insert("1", rec), true);
    EXPECT_EQ(tab.get_data_count(), 1);
}

TEST(RedBlackTree, can_insert_elem_in_tab_when_its_not_empty)
{
    RedBlackTree tab;
    TableBody rec1;
    tab.insert("1", rec1);

    EXPECT_EQ(tab.insert("2", rec1), true);
    EXPECT_EQ(tab.get_data_count(), 2);
}

TEST(RedBlackTree, cant_insert_elem_with_same_key)
{
    RedBlackTree tab;
    TableBody rec1;
    tab.insert("1", rec1);

    EXPECT_EQ(tab.insert("1", rec1), false);
    EXPECT_EQ(tab.get_data_count(), 1);
}

TEST(RedBlackTree, cant_find_when_is_empty)
{
    RedBlackTree tab;
    TableBody rec1;

    EXPECT_EQ(tab.find("2"), nullptr);
}

TEST(RedBlackTree, can_find_elem)
{
    RedBlackTree tab;
    TableBody rec1;
    tab.insert("1", rec1);

    EXPECT_EQ(tab.find_str("1")->get_key(), "1");
}

TEST(RedBlackTree, cant_find_elem)
{
    RedBlackTree tab;
    TableBody rec1;
    tab.insert("1", rec1);

    EXPECT_EQ(tab.find_str("2"), nullptr);
}

TEST(RedBlackTree, cant_delete_elem_when_its_empty)
{
    RedBlackTree tab;

    EXPECT_EQ(tab.erase("1"), false);
    EXPECT_EQ(tab.get_data_count(), 0);
}

TEST(RedBlackTree, can_delete_existing_elem)
{
    RedBlackTree tab;
    TableBody rec1;
    tab.insert("1", rec1);
    tab.erase("1");

    EXPECT_EQ(tab.get_data_count(), 0);
}

TEST(RedBlackTree, cant_delete_non_existing_elem)
{
    RedBlackTree tab;
    TableBody rec1;
    tab.insert("1", rec1);

    EXPECT_EQ(tab.erase("2"), false);
    EXPECT_EQ(tab.get_data_count(), 1);
}

TEST(RedBlackTree, can_go_next)
{
    RedBlackTree tab;
    TableBody rec1;
    tab.insert("1", rec1);
    tab.insert("2", rec1);
    tab.reset();
    tab.go_next();

    EXPECT_EQ(tab.get_value()->get_key(), "2");
}

TEST(RedBlackTree, cant_go_next)
{
    RedBlackTree tab;
    TableBody rec1;
    tab.insert("1", rec1);
    tab.reset();

    EXPECT_EQ(tab.go_next(), true);
}

TEST(RedBlackTree, can_reset)
{
    RedBlackTree tab;
    TableBody rec1;

    tab.insert("1", rec1);
    tab.insert("2", rec1);

    tab.reset();
    tab.go_next();
    tab.reset();

    EXPECT_EQ(tab.get_value()->get_key(), "1");
}


TEST(RedBlackTree, can_check_is_tab_ended_1)
{
    RedBlackTree tab;
    TableBody rec1;
    tab.insert("1", rec1);
    tab.insert("2", rec1);
    tab.insert("3", rec1);
    tab.reset();
    tab.go_next();
    tab.go_next();

    EXPECT_EQ(tab.go_next(), true);
}

TEST(RedBlackTree, can_check_is_tab_ended_2)
{
    RedBlackTree tab;

    EXPECT_EQ(tab.reset(), true);
}

TEST(RedBlackTree, can_get_current_pos)
{
    RedBlackTree tab;
    TableBody rec1;

    tab.insert("1", rec1);
    tab.insert("2", rec1);
    tab.insert("3", rec1);

    tab.reset();
    tab.go_next();
    tab.go_next();

    EXPECT_EQ(tab.get_current_pos(), 2);
}


TEST(RedBlackTree, can_set_current_pos)
{
    RedBlackTree tab;
    TableBody rec1;

    tab.insert("1", rec1);
    tab.insert("2", rec1);
    tab.insert("3", rec1);

    EXPECT_EQ(tab.set_current_pos(2), true);

    EXPECT_EQ(tab.get_current_pos(), 2);
    EXPECT_EQ(tab.get_value()->get_key(), "3");
}

TEST(RedBlackTree, cant_set_current_pos)
{
    RedBlackTree tab;
    TableBody rec1;

    tab.insert("1", rec1);
    tab.insert("2", rec1);
    tab.insert("3", rec1);

    tab.set_current_pos(3);


    EXPECT_EQ(tab.set_current_pos(3), false);
}
//
//TEST(RedBlackTree, can_get_value)
//{
//    RedBlackTree tab;
//    TableBody rec1;
//    tab.insert("1", rec1);
//    tab.reset();
//
//    EXPECT_EQ(tab.get_value()->get_key(), "1");
//}
//
