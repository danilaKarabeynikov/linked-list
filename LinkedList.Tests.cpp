#include "pch.h"
#include <iterator>
#include "LinkedList.h"

TEST(LinkedList, Constructors)
{
	LinkedList<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);

	EXPECT_EQ(1, list.Get(0));
	EXPECT_EQ(2, list.Get(1));
	EXPECT_EQ(3, list.Get(2));
	EXPECT_EQ(0, list.Get(3));
	EXPECT_EQ(1, list.Get(4));
	EXPECT_EQ(2, list.Get(5));
	EXPECT_EQ(3, list.Get(6));
	EXPECT_EQ(0, list.Get(7));
	EXPECT_EQ(1, list.Get(8));
	EXPECT_EQ(2, list.Get(9));

	LinkedList<int> list2(list);

	EXPECT_EQ(1, list2.Get(0));
	EXPECT_EQ(2, list2.Get(1));
	EXPECT_EQ(3, list2.Get(2));

	LinkedList<int> list3;
	list3 = list2;

	EXPECT_EQ(1, list3.Get(0));
	EXPECT_EQ(2, list3.Get(1));
	EXPECT_EQ(3, list3.Get(2));

	list.clear();
	EXPECT_TRUE(list.empty());
}

TEST(LinkedList, insert)
{
	LinkedList<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);

	LinkedList<int>::iterator it(list.begin());
	list.insert(it, 10);
	EXPECT_EQ(10, list.Get(0));
}

TEST(LinkedList, pushfront)
{
	LinkedList<int> list;
	list.push_front(1);
	list.push_front(2);
	list.push_front(3);

	EXPECT_EQ(3, list.Get(0));
	EXPECT_EQ(2, list.Get(1));
	EXPECT_EQ(1, list.Get(2));
}

TEST(LinkedList, erase)
{
	LinkedList<int> list;
	list.push_front(1);
	list.push_front(2);
	list.push_front(3);

	LinkedList<int>::iterator it(list.begin());
	list.erase(it);
	EXPECT_EQ(2, list.Get(0));
	EXPECT_EQ(1, list.Get(1));
	EXPECT_EQ(0, list.Get(2));
	EXPECT_EQ(2, list.Get(3));
}

TEST(LinkedList, remove)
{
	LinkedList<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);

	list.remove(2);
	EXPECT_EQ(1, list.Get(0));
	EXPECT_EQ(3, list.Get(1));
	EXPECT_EQ(0, list.Get(2));
}

TEST(LinkedList, reverse)
{
	LinkedList<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);

	list.reverse();
	EXPECT_EQ(3, list.Get(0));
	EXPECT_EQ(2, list.Get(1));
	EXPECT_EQ(1, list.Get(2));
}

TEST(LinkedList, begin_And_Rbegin)
{
	LinkedList<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);

	EXPECT_EQ(1, *(list.begin()));
	EXPECT_EQ(3, *(list.rbegin()));
}

TEST(LinkedList, End_And_Rend)
{
	LinkedList<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);

	EXPECT_EQ(0, *(list.end()));
	EXPECT_EQ(0, *(list.rend()));
}

TEST(LinkedList, Const_Begin_And_Rbegin)
{
	LinkedList<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);

	const LinkedList<int> list2(list);

	EXPECT_EQ(1, *(list2.begin()));
	EXPECT_EQ(3, *(list2.rbegin()));
}

TEST(LinkedList, Const_End_And_Rend)
{
	LinkedList<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);

	const LinkedList<int> &list2 = list;

	EXPECT_EQ(3, *(--list2.end()));
	EXPECT_EQ(1, *(--list2.rend()));
}

TEST(LinkedList, End_Of_List)
{
	LinkedList<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);		
	auto it = list.end();
	ASSERT_THROW(++it, std::runtime_error);
}

TEST(LinkedList, Begin_Of_List)
{
	LinkedList<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	auto it = list.begin();
	ASSERT_THROW(--it, std::runtime_error);
}