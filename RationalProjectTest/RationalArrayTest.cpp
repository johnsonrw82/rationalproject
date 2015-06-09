/*
* File: RationalArrayTest.cpp
* Author: Ryan Johnson
* Email: johnsonrw82@csu.fullerton.edu
*
* RationalArray class unit tests - written for use with the GoogleTest framework
*/

#include "RationalArray.h"

#include <gtest/gtest.h>
using namespace rational;

// rational array class test fixture
class RationalArrayTest : public ::testing::Test {
protected:
	virtual void SetUp() {
		
	}

	// clear the array on teardown
	virtual void TearDown() {
		ra.clear();
	}

	RationalArray ra;
};

// test empty
TEST_F(RationalArrayTest, TestEmpty) {
	EXPECT_EQ(0, ra.size());
}

// test size
TEST_F(RationalArrayTest, TestSize) {
	ra.add(Rational(1, 2));
	EXPECT_EQ(1, ra.size());
}

// test clear
TEST_F(RationalArrayTest, TestClear) {
	ra.add(Rational(1, 2));
	ra.add(Rational(1, 2));
	ra.add(Rational(1, 2));

	ASSERT_EQ(3, ra.size()); // assert has elements

	ra.clear();
	EXPECT_EQ(0, ra.size());
}

// test adding
TEST_F(RationalArrayTest, TestAdd) {
	ra.add(Rational(1, 2));
	ra.add(Rational(1, 3));
	ra.add(Rational(1, 4));

	EXPECT_EQ(3, ra.size()); // expect the proper number of elements
}

// test adding by pointer
TEST_F(RationalArrayTest, TestAddPtr) {
	ra.add(new Rational(1, 2));
	ra.add(new Rational(1, 3));
	ra.add(new Rational(1, 4));

	EXPECT_EQ(3, ra.size()); // expect the proper number of elements

	ra.add(nullptr); // disallowed
	EXPECT_EQ(3, ra.size()); // expect the proper number of elements
}

// test retrieval
TEST_F(RationalArrayTest, TestRetrieve) {
	ra.add(Rational(1, 2));
	ra.add(Rational(1, 3));
	ra.add(Rational(1, 4));

	ASSERT_EQ(3, ra.size()); // expect the proper number of elements

	Rational actual = ra.retrieve(1);
	EXPECT_EQ(Rational(1, 3), actual);

	actual = ra.retrieve(-1); // out of range, get 0
	EXPECT_EQ(Rational(0), actual);

	actual = ra.retrieve(ra.size()); // out of range, get 0
	EXPECT_EQ(Rational(0), actual);
}

// test replacing
TEST_F(RationalArrayTest, TestReplace) {
	ra.add(Rational(1, 2));
	ra.add(Rational(1, 3));
	ra.add(Rational(1, 4));

	ASSERT_EQ(3, ra.size()); // expect the proper number of elements

	Rational actual = ra.retrieve(1);
	ASSERT_EQ(Rational(1, 3), actual);  // assert that we can get the second element

	ra.replace(1, Rational(5, 6));

	actual = ra.retrieve(1);
	ASSERT_EQ(3, ra.size()); // assert same size
	EXPECT_EQ(Rational(5, 6), actual);
}

// test replacing by pointer
TEST_F(RationalArrayTest, TestReplaceptr) {
	ra.add(Rational(1, 2));
	ra.add(Rational(1, 3));
	ra.add(Rational(1, 4));

	ASSERT_EQ(3, ra.size()); // expect the proper number of elements

	Rational actual = ra.retrieve(1);
	ASSERT_EQ(Rational(1, 3), actual);  // assert that we can get the second element

	ra.replace(1, new Rational(5, 6));

	actual = ra.retrieve(1);
	ASSERT_EQ(3, ra.size()); // assert same size
	EXPECT_EQ(Rational(5, 6), actual);
}

// test removal
TEST_F(RationalArrayTest, TestRemove) {
	ra.add(Rational(1, 2));
	ra.add(Rational(1, 3));
	ra.add(Rational(1, 4));

	ASSERT_EQ(3, ra.size()); // expect the proper number of elements

	Rational actual = ra.remove(1);
	EXPECT_EQ(Rational(1, 3), actual); // remove the second element
	ASSERT_EQ(2, ra.size()); // assert proper size

	actual = ra.remove(1);
	EXPECT_EQ(Rational(1, 4), actual); // remove the new second element
	ASSERT_EQ(1, ra.size()); // assert proper size

	actual = Rational(0);
	ra.remove(-1); // disallowed
	ASSERT_EQ(1, ra.size()); // assert proper size
}
