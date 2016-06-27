#include "disjoint_set.hpp"

#include <gtest.h>

TEST(Disjoint_set, can_create_disjoint_set)
{
	ASSERT_NO_THROW(Disjoint_set<int>set = Disjoint_set<int>(5));
}

TEST(Disjoint_set, throws_when_set_size_negative)
{
	ASSERT_ANY_THROW(Disjoint_set<int>set(-2));
}

TEST(Disjoint_set, can_create_singleton)
{
	Disjoint_set<int>set(5);
	ASSERT_NO_THROW(set.CreateSet(1));
}

TEST(Disjoint_set, throws_when_singleton_size_negative)
{
	Disjoint_set<int>set(5);
	ASSERT_ANY_THROW(set.CreateSet(-1));
}


TEST(Disjoint_set, can_find_set)
{
	Disjoint_set<int>set(5);
	set.CreateSet(0);
	set.CreateSet(1);
	ASSERT_NO_THROW(set.FindSet(0));
}

TEST(Disjoint_set, throws_when_find_set_with_negative_size)
{
	Disjoint_set<int>set(2);
	set.CreateSet(0);
	set.CreateSet(1);
	ASSERT_ANY_THROW(set.FindSet(-2));
}

TEST(Disjoint_set, throws_when_find_nonexisting_element)
{
	Disjoint_set<int>set(2);
	set.CreateSet(0);
	set.CreateSet(1);
	ASSERT_ANY_THROW(set.FindSet(20));
}

TEST(Disjoint_set, throws_when_find_set_with_size_too_large)
{
	Disjoint_set<int>set(4);
	set.CreateSet(0);
	set.CreateSet(1);
	ASSERT_ANY_THROW(set.FindSet(100));
}


TEST(Disjoint_set, can_union)
{
	Disjoint_set<int>set(6);
	set.CreateSet(0);
	set.CreateSet(1);
	ASSERT_NO_THROW(set.UnionSet(0, 1));
}


TEST(Disjoint_set, throws_when_union_with_negative_size)
{
	Disjoint_set<int>set(3);
	set.CreateSet(0);
	set.CreateSet(1);
	ASSERT_ANY_THROW(set.UnionSet(0, -1));
}

TEST(Disjoint_set, throws_when_union_with_size_too_large)
{
	Disjoint_set<int>set(2);
	set.CreateSet(0);
	set.CreateSet(1);
	ASSERT_ANY_THROW(set.UnionSet(0, 10));
}

TEST(Disjoint_set, throws_when_get_set_with_incorrect_element_or_size)
{
	Disjoint_set<int>set(2);
	set.CreateSet(0);
	set.CreateSet(1);
	ASSERT_ANY_THROW(set.GetSet(47));
	ASSERT_ANY_THROW(set.GetSet(-47));
}