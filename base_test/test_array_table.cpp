
 #include <gtest.h>
 #include "array_table.h"

 /*#include "../gtest/gtest.h"
 #include "../base/array_table.h"*/
//

TEST(ArrayTable, can_create_table)
{
	ASSERT_NO_THROW(ArrayTable tab);
}

TEST(ArrayTable, can_insert_elem_in_tab)
{
    ArrayTable tab(2);
    TableBody rec;

    EXPECT_EQ(tab.insert("1", rec), true);
    EXPECT_EQ(tab.get_data_count(), 1);
}

TEST(ArrayTable, can_insert_elem_in_tab_when_its_not_empty)
{
    ArrayTable tab(2);
    TableBody rec1;
    tab.insert("1", rec1);

    EXPECT_EQ(tab.insert("2", rec1), true);
    EXPECT_EQ(tab.get_data_count(), 2);
}

TEST(ArrayTable, cant_insert_elem_with_same_key)
{
    ArrayTable tab(2);
    TableBody rec1;
    tab.insert("1", rec1);

    EXPECT_EQ(tab.insert("1", rec1), false);
    EXPECT_EQ(tab.get_data_count(), 1);
}

TEST(ArrayTable, cant_find_when_is_empty)
{
    ArrayTable tab(2);
    TableBody rec1;

    EXPECT_EQ(tab.find("2"), nullptr);
}

TEST(ArrayTable, can_find_elem)
{
    ArrayTable tab(2);
    TableBody rec1;
    tab.insert("1", rec1);

    EXPECT_EQ(tab.find_str("1")->get_key(), "1");
}

TEST(ArrayTable, cant_find_elem)
{
    ArrayTable tab(2);
    TableBody rec1;
    tab.insert("1", rec1);
    
    EXPECT_EQ(tab.find_str("2"), nullptr);
}

TEST(ArrayTable, cant_delete_elem_when_its_empty)
{
    ArrayTable tab(2);

    EXPECT_EQ(tab.erase("1"), false);
    EXPECT_EQ(tab.get_data_count(), 0);
}

TEST(ArrayTable, can_delete_existing_elem)
{
    ArrayTable tab(2);
    TableBody rec1;
    tab.insert("1", rec1);
    tab.erase("1");

    EXPECT_EQ(tab.get_data_count(), 0);
}

TEST(ArrayTable, cant_delete_non_existing_elem)
{
    ArrayTable tab(2);
    TableBody rec1;
    tab.insert("1", rec1);

    EXPECT_EQ(tab.erase("2"), false);
    EXPECT_EQ(tab.get_data_count(), 1);
}

TEST(ArrayTable, can_go_next)
{
    ArrayTable tab(2);
    TableBody rec1;
    tab.insert("1", rec1);
    tab.insert("2", rec1);
    tab.reset();
    tab.go_next();

    EXPECT_EQ(tab.get_value()->get_key(), "2");
}

TEST(ArrayTable, cant_go_next)
{
    ArrayTable tab(2);
    TableBody rec1;
    tab.insert("1", rec1);
    tab.reset();

    EXPECT_EQ(tab.go_next(), true);
}

TEST(ArrayTable, can_reset)
{
    ArrayTable tab(2);
    TableBody rec1;

    tab.insert("1", rec1);
    tab.insert("2", rec1);

    tab.reset();
    tab.go_next();
    tab.reset();

    EXPECT_EQ(tab.get_value()->get_key(), "1");
}


TEST(ArrayTable, can_check_is_tab_ended_1)
{
    ArrayTable tab(3);
    TableBody rec1;
    tab.insert("1", rec1);
    tab.insert("2", rec1);
    tab.insert("3", rec1);
    tab.reset();
    tab.go_next();
    tab.go_next();
    
    EXPECT_EQ(tab.go_next(), true);
}


TEST(ArrayTable, can_check_is_tab_ended_2)
{
    ArrayTable tab(2);

    EXPECT_EQ(tab.reset(), true);
}

TEST(ArrayTable, can_get_current_pos)
{
    ArrayTable tab(3);
    TableBody rec1;

    tab.insert("1", rec1);
    tab.insert("2", rec1);
    tab.insert("3", rec1);

    tab.reset();
    tab.go_next();
    tab.go_next();

    EXPECT_EQ(tab.get_current_pos(), 2);
}


TEST(ArrayTable, can_set_current_pos)
{
    ArrayTable tab(3);
    TableBody rec1;

    tab.insert("1", rec1);
    tab.insert("2", rec1);
    tab.insert("3", rec1);

    EXPECT_EQ(tab.set_current_pos(2), true);
    
    EXPECT_EQ(tab.get_current_pos(), 2);
    EXPECT_EQ(tab.get_value()->get_key(), "3");
}


TEST(ArrayTable, cant_set_current_pos)
{
    ArrayTable tab(3);
    TableBody rec1;

    tab.insert("1", rec1);
    tab.insert("2", rec1);
    tab.insert("3", rec1);

    tab.set_current_pos(3);


    EXPECT_EQ(tab.set_current_pos(3), false);
}

TEST(ArrayTable, can_get_value)
{
    ArrayTable tab(2);
    TableBody rec1;
    tab.insert("1", rec1);
    tab.reset();

    EXPECT_EQ(tab.get_value()->get_key(), "1");
}

