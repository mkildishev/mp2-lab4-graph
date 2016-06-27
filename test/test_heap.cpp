#include <gtest.h>
#include "d-heap.hpp"

TEST(D_heap, can_create_heap)
{
	ASSERT_NO_THROW(D_heap<int> *a = new D_heap<int>(3, 10));
}

TEST(D_heap, throws_when_size_negative)
{
	ASSERT_ANY_THROW(D_heap<int> * heap = new D_heap<int>(3, -10));
}

TEST(D_heap, throws_when_arity_is_negative)
{
	ASSERT_ANY_THROW(D_heap<int> *heap = new D_heap<int>(-3, 10));
}

TEST(D_heap, can_copy_heap)
{
	D_heap<int> *a = new D_heap<int>(3, 10);
	ASSERT_NO_THROW(D_heap<int> *b = new D_heap<int>(*a));
}

TEST(D_heap, GetParent_works_properly)
{
	D_heap<int>*a = new D_heap<int>(3, 11);
	int c = a->GetParent(6);
	EXPECT_EQ(c, 1);
}

TEST(D_heap, Swap_works_properly)
{
	int c;
	D_heap<int>*a = new D_heap<int>(3, 0);
	a->Push(5);
	a->Push(8);
	D_heap<int>*b = new D_heap<int>(3, 0);
	b->Push(8);
	b->Push(5);

	b->Swap(0, 1);
	c = a->operator==(*b);
	EXPECT_EQ(c, 1);
}

TEST(D_heap, throws_when_swap_wrong_elements)
{
	D_heap<int>*a = new D_heap<int>(3, 13);
	ASSERT_ANY_THROW(a->Swap(15, 17));
}

TEST(D_heap, can_sift_up)
{
	D_heap<int>*a = new D_heap<int>(3, 0);
	a->Push(5);
	a->Push(8);
	ASSERT_NO_THROW(a->SiftUp(1));
}

TEST(D_heap, SiftUp_works_properly)
{
	int c;
	D_heap<int>*a = new D_heap<int>(3, 0);
	a->Push(5);
	a->Push(8);
	a->Push(7);
	a->Push(14);
	a->Push(15);
	a->Push(12);
	a->Push(18);
	a->Push(8);
	a->Push(10);
	a->Push(12);
	a->Push(14);
	a->Push(15);
	a->Push(13);
	a->SiftUp(12);

	D_heap<int>*b = new D_heap<int>(3, 0);
	b->Push(5);
	b->Push(8);
	b->Push(7);
	b->Push(13);
	b->Push(15);
	b->Push(12);
	b->Push(18);
	b->Push(8);
	b->Push(10);
	b->Push(12);
	b->Push(14);
	b->Push(15);
	b->Push(14);
	c = a->operator==(*b);
	EXPECT_EQ(c, 1);
}

TEST(D_heap, throws_when_SiftUp_nonexisting_element)
{
	D_heap<int>*a = new D_heap<int>(3, 13);
	ASSERT_ANY_THROW(a->SiftUp(16));
}

TEST(D_heap, MinChild_works_properly)
{
	D_heap<int>*a = new D_heap<int>(3, 0);
	a->Push(5);
	a->Push(8);
	a->Push(7);
	a->Push(14);
	a->Push(15);
	a->Push(12);
	a->Push(18);
	a->Push(8);
	a->Push(10);
	a->Push(12);
	a->Push(14);
	a->Push(15);
	a->Push(13);
	int b = a->MinChild(0);
	EXPECT_EQ(b, 2);
}



TEST(D_heap, SiftDown_works_properly)
{
	D_heap<int>*a = new D_heap<int>(3, 0);
	a->Push(5);
	a->Push(30);
	a->Push(7);
	a->Push(12);
	a->Push(15);
	a->Push(12);
	a->Push(18);
	a->Push(8);
	a->Push(10);
	a->Push(12);
	a->Push(14);
	a->Push(15);
	a->Push(13);
	a->SiftDown(1);

	D_heap<int>*b = new D_heap<int>(3, 0);
	b->Push(5);
	b->Push(12);
	b->Push(7);
	b->Push(12);
	b->Push(15);
	b->Push(30);
	b->Push(18);
	b->Push(8);
	b->Push(10);
	b->Push(12);
	b->Push(14);
	b->Push(15);
	b->Push(13);
	int c = a->operator==(*b);
	EXPECT_EQ(c, 1);
}




TEST(D_heap, throws_when_SiftDown_nonexisting_elements)
{
	D_heap<int>*a = new D_heap<int>(3, 13);
	ASSERT_ANY_THROW(a->SiftDown(20));
}

TEST(D_heap, RemiveMin_works_properly)
{
	D_heap<int>*a = new D_heap<int>(3, 0);
	a->Push(5);
	a->Push(8);
	a->Push(7);
	a->Push(12);
	a->Push(15);
	a->Push(12);
	a->Push(18);
	a->Push(8);
	a->Push(10);
	a->Push(12);
	a->Push(14);
	a->Push(15);
	a->Push(13);
	a->RemoveMin();

	D_heap<int>*b = new D_heap<int>(3, 0);
	b->Push(7);
	b->Push(8);
	b->Push(8);
	b->Push(12);
	b->Push(15);
	b->Push(12);
	b->Push(18);
	b->Push(13);
	b->Push(10);
	b->Push(12);
	b->Push(14);
	b->Push(15);
	int c = a->operator==(*b);
	EXPECT_EQ(c, 1);
}

TEST(D_heap, Remove_works_properly)
{
	D_heap<int>*a = new D_heap<int>(3, 0);
	a->Push(5);
	a->Push(8);
	a->Push(7);
	a->Push(12);
	a->Push(15);
	a->Push(12);
	a->Push(18);
	a->Push(8);
	a->Push(10);
	a->Push(12);
	a->Push(14);
	a->Push(15);
	a->Push(13);
	a->Remove(2);

	D_heap<int>*b = new D_heap<int>(3, 0);
	b->Push(5);
	b->Push(8);
	b->Push(8);
	b->Push(12);
	b->Push(15);
	b->Push(12);
	b->Push(18);
	b->Push(13);
	b->Push(10);
	b->Push(12);
	b->Push(14);
	b->Push(15);
	int c = a->operator==(*b);
	EXPECT_EQ(c, 1);
}

TEST(D_heap, throws_when_remove_nonexisting_element)
{
	D_heap<int>*a = new D_heap<int>(3, 13);
	ASSERT_ANY_THROW(a->Remove(16));
}

TEST(D_heap, removing_decreases_count)
{
	D_heap<int>*a = new D_heap<int>(3, 0);
	a->Push(5);
	a->Push(8);
	int c = a->GetCount();
	a->Remove(1);
	EXPECT_EQ(a->GetCount(),c-1);
}

TEST(D_heap, Heapify_works_properly)
{
	D_heap<int>*a = new D_heap<int>(3, 0);
	a->Push(5);
	a->Push(8);
	a->Push(7);
	a->Push(12);
	a->Push(15);
	a->Push(12);
	a->Push(18);
	a->Push(8);
	a->Push(10);
	a->Push(12);
	a->Push(14);
	a->Push(15);
	a->Push(13);
	a->Heapify();
	int c = a->operator==(*a);
	EXPECT_EQ(c, 1);
}

TEST(D_heap, throws_when_heap_is_empty)
{
	D_heap<int>*a = new D_heap<int>(3, 0);
	ASSERT_ANY_THROW(a->Heapify());
}


TEST(D_heap, insertion_increases_count)
{
	D_heap<int>*a = new D_heap<int>(3, 13);
	int c = a->GetCount();
	a->Push(15);
	EXPECT_EQ(a->GetCount(), c + 1);
}

