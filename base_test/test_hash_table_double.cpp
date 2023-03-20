#include <gtest.h>
#include "hash_table_double.h"

// #include "../gtest/gtest.h"
// #include "../base/hash_table_list.h"


TEST(HashTableDouble, can_create_table)
{
    ASSERT_NO_THROW(HashTableDouble tab);
}


TEST(HashTableDouble, can_insert_elem_in_tab)
{
    HashTableDouble tab;
    TableBody rec;

    EXPECT_EQ(tab.insert("1", rec), true);
    EXPECT_EQ(tab.get_data_count(), 1);
}

TEST(HashTableDouble, can_insert_elem_in_tab_when_its_not_empty)
{
    HashTableDouble tab;
    TableBody rec1;
    tab.insert("1", rec1);

    EXPECT_EQ(tab.insert("2", rec1), true);
    EXPECT_EQ(tab.get_data_count(), 2);
}

TEST(HashTableDouble, cant_insert_elem_with_same_key)
{
    HashTableDouble tab;
    TableBody rec1;
    tab.insert("1", rec1);

    EXPECT_EQ(tab.insert("1", rec1), false);
    EXPECT_EQ(tab.get_data_count(), 1);
}

TEST(HashTableDouble, cant_find_when_is_empty)
{
    HashTableDouble tab;
    TableBody rec1;

    EXPECT_EQ(tab.find("2"), nullptr);
}

TEST(HashTableDouble, can_find_elem)
{
    HashTableDouble tab;
    TableBody rec1;
    tab.insert("1", rec1);

    EXPECT_EQ(tab.find_str("1")->get_key(), "1");
}

TEST(HashTableDouble, cant_find_elem)
{
    HashTableDouble tab;
    TableBody rec1;
    tab.insert("1", rec1);

    EXPECT_EQ(tab.find_str("2"), nullptr);
}

TEST(HashTableDouble, cant_delete_elem_when_its_empty)
{
    HashTableDouble tab;

    EXPECT_EQ(tab.erase("1"), false);
    EXPECT_EQ(tab.get_data_count(), 0);
}

TEST(HashTableDouble, can_delete_existing_elem)
{
    HashTableDouble tab;
    TableBody rec1;
    tab.insert("1", rec1);
    tab.erase("1");

    EXPECT_EQ(tab.get_data_count(), 0);
}

TEST(HashTableDouble, cant_delete_non_existing_elem)
{
    HashTableDouble tab;
    TableBody rec1;
    tab.insert("1", rec1);

    EXPECT_EQ(tab.erase("2"), false);
    EXPECT_EQ(tab.get_data_count(), 1);
}

TEST(HashTableDouble, can_go_next)
{
    HashTableDouble tab;
    TableBody rec1;
    tab.insert("1", rec1);
    tab.insert("2", rec1);
    tab.reset();
    tab.go_next();

    EXPECT_EQ(tab.get_value()->get_key(), "2");
}

TEST(HashTableDouble, cant_go_next)
{
    HashTableDouble tab;
    TableBody rec1;
    tab.insert("1", rec1);
    tab.reset();

    EXPECT_EQ(tab.go_next(), true);
}

TEST(HashTableDouble, can_check_is_tab_ended_1)
{
    HashTableDouble tab;
    TableBody rec1;
    tab.insert("1", rec1);
    tab.insert("2", rec1);
    tab.insert("3", rec1);
    tab.reset();
    tab.go_next();
    tab.go_next();

    EXPECT_EQ(tab.go_next(), true);
}
