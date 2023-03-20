#include <gtest.h>
#include "list.h"

// #include "../gtest/gtest.h"
// #include "../base/list.h"


TEST(List, can_create_list)
{
  ASSERT_NO_THROW(List<int> List);
}

TEST(List, can_push_back)
{
  List<int> List;
  ASSERT_NO_THROW(List.add(5));
}

TEST(List, can_pop_front)
{
  List<int> List;
  List.add(5);
  ASSERT_NO_THROW(List.get_node(0));
}

TEST(List, can_compare_two_lists_by_value)
{
  List<int> List1, List2;
  List1.add(10);
  List2.add(10);
  EXPECT_EQ(1, List1[0] == List2[0]);
}

TEST(List, two_lists_with_different_size_are_not_equal)
{
  List<int> List1, List2;

  List1.add(1); List1.add(2);
  List2.add(1);

  EXPECT_FALSE(List1.get_node(0) == List2.get_node(0));
}

TEST(List, can_create_copied_list)
{
  List<int> List1, List2;
  List1.add(5);
  List2 = List1;
  EXPECT_TRUE(List1[0] == List2[0]);
}

TEST(List, can_assign_list)
{
  List<int> List1, List2;
  List1.add(5);
  ASSERT_NO_THROW(List2 = List1);
}

TEST(List, method_get_return_value)
{
  List<int> List;
  List.add(10);
  EXPECT_EQ(10, List[0]);
}

TEST(List, can_check_for_empty)
{
  List<int> List;
  EXPECT_TRUE(List.is_empty());
}

TEST(List, two_lists_with_different_sizes_are_not_equal)
{
  List<int> List1, List2;
  List1.add(1); List1.add(1);
  List2.add(1);
  EXPECT_FALSE(List1 == List2);
}

TEST(List, two_lists_are_not_equal)
{
  List<int> List1, List2;
  List1.add(1);
  List2.add(2);
  EXPECT_TRUE(List1 != List2);
}

TEST(List, can_return_size_of_list)
{
  List<int> List;
  for (int i = 0; i < 3; i++) {
      List.add(i);
  }
  EXPECT_EQ(3, List.get_size());
}

TEST(List, method_del_delete_all_values_of_list)
{
  List<int> List;
  for (int i = 0; i < 5; i++) {
    List.add(i);
  }
  List.erase_list();
  EXPECT_TRUE(List.is_empty());
}

TEST(List, can_erace_elem_by_iterator)
{
  List<int> List;
  List.add(10);
  ListIterator<int> i = List.begin();
  ASSERT_NO_THROW(List.erase(i));
}

TEST(List, can_insert_elem_by_iterator)
{
  List<int> List;
  ListIterator<int> i = List.begin();
  List.insert(i, 3);
  EXPECT_EQ(1, List.get_size());
}

// ITERATOR TESTS

TEST(Iterator, can_create_iterator)
{
  List<int> List;
  ASSERT_NO_THROW(ListIterator<int> i = List.begin());
}

TEST(Iterator, can_create_copied_iterator)
{
  List<int> List;
  ListIterator<int> i1 = List.begin();
  ASSERT_NO_THROW(ListIterator<int> i2(i1));
}

TEST(Iterator, can_assign_iterator)
{
  List<int> List1, List2;
  List<int>::iterator i1 = List1.begin();
  List<int>::iterator i2 = List2.begin();
  ASSERT_NO_THROW(i2 = i1);
}

TEST(Iterator, can_dereference_iterator)
{
  List<int> List;
  List.add(1);
  ListIterator<int> i = List.begin();
  EXPECT_EQ(1, *(i));
}

TEST(Iterator, can_increment_iterator)
{
  List<int> List;
  List.add(1);
  List.add(2);
  ListIterator<int> i = List.begin();
  ++i;
  EXPECT_EQ(2, *(i));
}
