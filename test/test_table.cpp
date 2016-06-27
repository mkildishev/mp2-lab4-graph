#include <gtest.h>
#include "table.hpp"

TEST(Table, can_create_Table)
{
	ASSERT_NO_THROW(Scan_table<int>*a = new Scan_table<int>(5));
}

TEST(Table, created_Table_is_empty)
{
	Scan_table<int>*a = new Scan_table<int>(5);
	EXPECT_EQ(1, a->IsEmpty());
}

TEST(Table, can_Push_record_to_Table)
{
	Scan_table<int>*a = new Scan_table<int>(5);
	ASSERT_NO_THROW(a->Push(1, 2));
}

TEST(Table, can_Remove_record_from_Table)
{
	Scan_table<int>*a = new Scan_table<int>(5);
	a->Push(1, 2);
	ASSERT_NO_THROW(a->Remove(1));
}

TEST(Table, can_Remove_record_from_Table2)
{
	Scan_table<int>*a = new Scan_table<int>(5);
	a->Push(1, 2);
	EXPECT_EQ(a->IsEmpty(), 0);
}



TEST(Table, can_find_record)
{
	Scan_table<int>*a = new Scan_table<int>(5);
	a->Push(1, 2);
	a->Push(2, 3);
	a->Push(3, 4);
	EXPECT_EQ(a->FindKey(2)->GetData(), 3);
}

TEST(Table, throws_when_push_to_full_table)
{
	Scan_table<int>*a = new Scan_table<int>(5);
	a->Push(1, 2);
	a->Push(2, 3);
	a->Push(3, 4);
	a->Push(4, 5);
	a->Push(5, 6);
	ASSERT_ANY_THROW(a->Push(6, 7));
}

TEST(Table, can_check_fullness)
{
	Scan_table<int>*a = new Scan_table<int>(5);
	a->Push(1, 2);
	a->Push(2, 3);
	a->Push(3, 4);
	a->Push(4, 5);
	a->Push(5, 6);
	EXPECT_EQ(a->IsFull(), 1);
}

TEST(Table, can_get_count)
{
	Scan_table<int>*a = new Scan_table<int>(5);
	a->Push(1, 2);
	a->Push(2, 3);
	a->Push(3, 4);
	a->Push(4, 5);
	EXPECT_EQ(a->GetCount(), 4);
}

TEST(Table, throws_when_GoNext_in_full_table)
{
	Scan_table<int>*a = new Scan_table<int>(5);
	a->Push(1, 2);
	a->Push(2, 3);
	a->Push(3, 4);
	a->Push(4, 5);
	a->Push(5, 6);
	EXPECT_EQ(a->GoNext(), 1);
}

TEST(Table, can_create_Sort_table)
{
	ASSERT_NO_THROW(Sort_table<int>*a = new Sort_table<int>(5));
}

TEST(Table, can_copy_Scan_table_to_Sort_table)
{
	Scan_table<int>*a = new Scan_table<int>(5);
	ASSERT_NO_THROW(Sort_table<int>*b = new Sort_table<int>(*a));
}

TEST(Table, can_FindKey_in_Sort_table)
{
	Sort_table<int>*a = new Sort_table<int>(5);
	a->Push(1, 2);
	a->Push(2, 3);
	a->Push(3, 4);
	a->Push(4, 5);
	a->Push(5, 6);
	EXPECT_EQ(a->FindKey(3)->GetData(), 4);
}

TEST(Table, can_Remove_in_Sort_table)
{
	Sort_table<int>*a = new Sort_table<int>(5);
	a->Push(1, 2);
	a->Push(2, 3);
	a->Push(3, 4);
	a->Push(4, 5);
	a->Push(5, 6);
	ASSERT_NO_THROW(a->Remove(3));
}

TEST(Table, can_sort_table)
{
	Sort_table<int>*a = new Sort_table<int>(5);
	a->Push(1, 2);
	a->Push(2, 3);
	a->Push(3, 4);
	a->Push(4, 5);
	a->Push(5, 6);
	ASSERT_NO_THROW(a->Sort());
}

TEST(Table, can_getmin)
{
	Sort_table<int>*a = new Sort_table<int>(5);
	a->Push(1, 2);
	a->Push(2, 3);
	a->Push(3, 4);
	a->Push(4, 5);
	a->Push(5, 6);
	EXPECT_EQ(a->Min()->GetData(), 2);
}

TEST(Scan_table, insertion_increases_count)
{
	Scan_table<int>*a = new Scan_table<int>(5);
	int c = a->GetCount();
	a->Push(1, 2);
	EXPECT_EQ(a->GetCount(), c + 1);
}

TEST(Sort_table, insertion_increases_count)
{
	Sort_table<int>*a = new Sort_table<int>(5);
	int c = a->GetCount();
	a->Push(1, 2);
	EXPECT_EQ(a->GetCount(), c + 1);
}

TEST(Scan_table, removing_decreases_count)
{
	Scan_table<int>*a = new Scan_table<int>(5);
	a->Push(1, 2);
	a->Push(2, 3);
	a->Push(3, 4);
	a->Push(4, 5);
	a->Push(5, 6);
	int c = a->GetCount();
	a->Remove(3);
	EXPECT_EQ(a->GetCount(), (c - 1));
}

TEST(Sort_table, removing_decreases_count)
{
	Sort_table<int>*a = new Sort_table<int>(5);
	a->Push(1, 2);
	a->Push(2, 3);
	a->Push(3, 4);
	a->Push(4, 5);
	a->Push(5, 6);
	int c = a->GetCount();
	a->Remove(3);
	EXPECT_EQ(a->GetCount(), (c - 1));
}

TEST(Sort_table, throws_when_remove_nonexisting_element)
{
	Sort_table<int>*a = new Sort_table<int>(5);
	a->Push(1, 2);
	ASSERT_ANY_THROW(a->Remove(8));
}