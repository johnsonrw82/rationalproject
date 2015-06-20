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
using namespace rational::exception;

// rational array class test fixture
class RationalArrayTest : public ::testing::Test {
protected:
	virtual void SetUp() {
		ra.add(Rational(1, 2));
		ra.add(Rational(1, 3));
		ra.add(Rational(1, 4));
	}

	// clear the array on teardown
	virtual void TearDown() {
		ra.clear();
	}

	RationalArray ra;
};

// test create invalid size
TEST_F(RationalArrayTest, TestCreateInvalidArgumentException) {
	ra.clear();
	try {
		ra = RationalArray(-1); // throw exception
		FAIL();
	}
	catch (InvalidArgumentException &ex) {
		std::cout << ex << std::endl;		
	}
	catch (std::exception) {
		FAIL();
	}
}

// test empty
TEST_F(RationalArrayTest, TestEmpty) {
	ra.clear();
	EXPECT_EQ(0, ra.size());
}

// test size
TEST_F(RationalArrayTest, TestSize) {
	EXPECT_EQ(3, ra.size());
}

// test clear
TEST_F(RationalArrayTest, TestClear) {
	ASSERT_EQ(3, ra.size()); // assert has elements

	ra.clear();
	EXPECT_EQ(0, ra.size());
}

// test adding
TEST_F(RationalArrayTest, TestAdd) {
	EXPECT_EQ(3, ra.size()); // expect the proper number of elements
}

// test adding by pointer
TEST_F(RationalArrayTest, TestAddPtr) {
	ra.clear();
	ra.add(new Rational(1, 2));
	ra.add(new Rational(1, 3));
	ra.add(new Rational(1, 4));

	EXPECT_EQ(3, ra.size()); // expect the proper number of elements

	ra.add(nullptr); // disallowed
	EXPECT_EQ(3, ra.size()); // expect the proper number of elements
}

// test retrieval
TEST_F(RationalArrayTest, TestRetrieve) {
	ASSERT_EQ(3, ra.size()); // expect the proper number of elements

	Rational actual = ra.retrieve(1);
	EXPECT_EQ(Rational(1, 3), actual);
}

// test retrieval - array index out of bounds
TEST_F(RationalArrayTest, TestRetrieveArrayIndexOutOfBoundsException) {
	ASSERT_EQ(3, ra.size()); // expect the proper number of elements
	Rational actual;

	try {
		actual = ra.retrieve(-1); // out of range
		FAIL();
	}
	catch (ArrayIndexOutOfBoundsException &ex) {
		std::cout << ex << std::endl;
		ASSERT_EQ(-1, ex.getIndex());
	}
	catch (std::exception) {
		FAIL();
	}

	try {
		actual = ra.retrieve(ra.size()); // out of range
		FAIL();
	}
	catch (ArrayIndexOutOfBoundsException &ex) {
		std::cout << ex << std::endl;
		ASSERT_EQ(3, ex.getIndex());
	}
	catch (std::exception) {
		FAIL();
	}
}

// test replacing
TEST_F(RationalArrayTest, TestReplace) {
	ASSERT_EQ(3, ra.size()); // expect the proper number of elements

	Rational actual = ra.retrieve(1);
	ASSERT_EQ(Rational(1, 3), actual);  // assert that we can get the second element

	ra.replace(1, Rational(5, 6));

	actual = ra.retrieve(1);
	ASSERT_EQ(3, ra.size()); // assert same size
	EXPECT_EQ(Rational(5, 6), actual);
}

// test replacing - exception
TEST_F(RationalArrayTest, TestReplaceArrayIndexOutOfBoundsException) {
	ASSERT_EQ(3, ra.size()); // expect the proper number of elements

	Rational actual = ra.retrieve(1);
	ASSERT_EQ(Rational(1, 3), actual);  // assert that we can get the second element

	try {
		ra.replace(-1, Rational(5, 6));
		FAIL();
	}
	catch (ArrayIndexOutOfBoundsException &ex) {
		std::cout << ex << std::endl;
		ASSERT_EQ(-1, ex.getIndex());
	}
	catch (std::exception) {
		FAIL();
	}

	try {
		ra.replace(ra.size(), Rational(5, 6));
		FAIL();
	}
	catch (ArrayIndexOutOfBoundsException &ex) {
		std::cout << ex << std::endl;
		ASSERT_EQ(3, ex.getIndex());
	}
	catch (std::exception) {
		FAIL();
	}
}

// test replacing by pointer
TEST_F(RationalArrayTest, TestReplaceptr) {
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
	ASSERT_EQ(3, ra.size()); // expect the proper number of elements

	Rational actual = ra.remove(1);
	EXPECT_EQ(Rational(1, 3), actual); // remove the second element
	ASSERT_EQ(2, ra.size()); // assert proper size

	actual = ra.remove(1);
	EXPECT_EQ(Rational(1, 4), actual); // remove the new second element
	ASSERT_EQ(1, ra.size()); // assert proper size
}

// test removal - exception
TEST_F(RationalArrayTest, TestRemoveArrayIndexOutOfBoundsException) {
	ASSERT_EQ(3, ra.size()); // expect the proper number of elements

	Rational actual;
	try {
		ra.remove(-1); // disallowed
		FAIL();
	}
	catch (ArrayIndexOutOfBoundsException &ex) {
		std::cout << ex << std::endl;
		ASSERT_EQ(-1, ex.getIndex());
	}
	catch (std::exception) {
		FAIL();
	}

	try {
		ra.remove(ra.size()); // disallowed
		FAIL();
	}
	catch (ArrayIndexOutOfBoundsException &ex) {
		std::cout << ex << std::endl;
		ASSERT_EQ(3, ex.getIndex());
	}
	catch (std::exception) {
		FAIL();
	}
}

// test add and resize
TEST_F(RationalArrayTest, TestAddAndResize) {
	ra = RationalArray(3); // initial capacity of 3
	ASSERT_EQ(3, ra.capacity()); // assert the capacity is what we said
	ASSERT_EQ(0, ra.size()); // assert the size is 0

	for (int i = 1; i <= 3; i++) {
		Rational r(1, i);
		ra.add(r);
	}
	ASSERT_EQ(3, ra.capacity()); // assert the capacity is unchanged
	ASSERT_EQ(ra.capacity(), ra.size()); // assert the size is capacity

	// add another, force a resize
	ra.add(Rational(5, 6));
	ASSERT_TRUE(ra.capacity() > 3); // assert greater than what we started with
	ASSERT_EQ(4, ra.size()); // ensure we added our element
}

// test equality
TEST_F(RationalArrayTest, TestEqual) {
	RationalArray ra2;
	ra2.add(Rational(1, 2));
	ra2.add(Rational(1, 3));
	ra2.add(Rational(1, 4));

	EXPECT_EQ(ra, ra2);

	ra.replace(2, Rational(1, 5));
	EXPECT_NE(ra, ra2);

	RationalArray ra3 = ra;
	EXPECT_EQ(ra, ra3);

	// make it almost like r2
	RationalArray ra4(4);
	ra4.add(Rational(1, 2));
	ra4.add(Rational(1, 3));
	ra4.add(Rational(1, 4));
	
	EXPECT_NE(ra4, ra2);
}

// test print array -- code coverage + no exception
TEST_F(RationalArrayTest, TestPrintArray) {
	try {
		ra.printArray();
	}
	catch (std::exception) {
		FAIL();
	}
}
