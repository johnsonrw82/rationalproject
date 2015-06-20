/*
* File: RationalTest.cpp
* Author: Ryan Johnson
* Email: johnsonrw82@csu.fullerton.edu
* 
* Rational class unit tests - written for use with the GoogleTest framework
*/

#include "Rational.h"
#include "RationalException.h"

#include <gtest/gtest.h>
using namespace rational;
using namespace rational::exception;

// test fixture class
class RationalTest : public ::testing::Test {
protected:
	virtual void SetUp() {
		half = Rational(1, 2);
		twoThirds = Rational(2, 3);
		one = Rational(1, 1);
	}

	Rational half;
	Rational twoThirds;
	Rational one;
};

// test equality
TEST_F(RationalTest, TestEqual) {
	// test equality
	Rational r(4, 4);
	Rational r2(4, 6);
	Rational r3(0.5);

	ASSERT_TRUE(r.equal(one));
	EXPECT_EQ(r, one);
	EXPECT_EQ(r2, twoThirds);
	EXPECT_EQ(r3, half);

	Rational r4(0.6666);
	EXPECT_NE(r4, twoThirds);
	EXPECT_NE(r, half);

	Fraction f(3);
	f = 5;
	EXPECT_EQ(Fraction(5), f);

	Fraction f2(-5);
	EXPECT_NE(f, f2);
}

// test less than
TEST_F(RationalTest, TestLessThan) {
	// test equality
	Rational r(4, 4);
	Rational r2(-4, 6);
	Rational r3(0.5);

	// half less than one
	EXPECT_TRUE(r3 < one); 
	EXPECT_TRUE(r3.lessThan(one));
	// negative number
	EXPECT_TRUE(r2 < 0);
	EXPECT_TRUE(r2.lessThan(0));
	// less than, not equal
	EXPECT_FALSE(r < one);
	EXPECT_FALSE(r.lessThan(one));
}

// test less than equal
TEST_F(RationalTest, TestLessThanOrEqual) {
	// test equality
	Rational r(4, 4);
	Rational r2(-4, 6);
	Rational r3(0.5);

	// half less than one
	EXPECT_TRUE(r3 <= one);
	EXPECT_TRUE(r3.lessThanEqual(one));
	// negative number
	EXPECT_TRUE(r2 <= 0);
	EXPECT_TRUE(r2.lessThanEqual(0));
	// less than, equal
	EXPECT_TRUE(r <= one);
	EXPECT_TRUE(r.lessThanEqual(one));
}

// test greater than
TEST_F(RationalTest, TestGreaterThan) {
	// test equality
	Rational r(4, 4);
	Rational r2(-4, 6);
	Rational r3(0.5);

	// half less than one
	EXPECT_FALSE(r3 > one);
	EXPECT_FALSE(r3.greaterThan(one));
	// negative number
	EXPECT_FALSE(r2 > 0);
	EXPECT_FALSE(r2.greaterThan(0));

	// greater than
	EXPECT_TRUE(r > half);
	EXPECT_TRUE(r.greaterThan(half));
}

// test greater than equal
TEST_F(RationalTest, TestGreaterThanOrEqual) {
	// test equality
	Rational r(4, 4);
	Rational r2(-4, 6);
	Rational r3(0.5);

	// half less than one
	EXPECT_FALSE(r3 >= one);
	EXPECT_FALSE(r3.greaterThanEqual(one));
	// negative number
	EXPECT_FALSE(r2 >= 0);
	EXPECT_FALSE(r2.greaterThanEqual(0));

	// greater than equal
	EXPECT_TRUE(r >= one);
	EXPECT_TRUE(r.greaterThanEqual(one));
}

// test assignment
TEST_F(RationalTest, TestAssignment) {
	Rational r = 2;
	Rational r2 = (float) 2.0;
	Rational r3 = (double) 2.0;
	Rational r4 = r;

	EXPECT_EQ(Rational(2), r);
	EXPECT_EQ(Rational((float)2.0), r2);
	EXPECT_EQ(Rational((double)2.0), r3);
	EXPECT_EQ(Rational(r), r4);
}

// test set
TEST_F(RationalTest, TestSet) {
	Rational r;
	r.set(2);
	Rational r2;
	r2.set((float) 2.0);
	Rational r3;
	r3.set((double) 2.0);
	Rational r4;
	r4.set(r);
	Rational r5;
	r5.set(1, 2);
	Rational r6;
	r6.set(1, -2);
	Rational r7;
	r7.set(-1, -2);

	EXPECT_EQ(Rational(2), r);
	EXPECT_EQ(Rational((float)2.0), r2);
	EXPECT_EQ(Rational((double)2.0), r3);
	EXPECT_EQ(Rational(r), r4);
	EXPECT_EQ(half, r5);
	EXPECT_EQ(half.negate(), r6);
	EXPECT_EQ(half, r7);

	Fraction f(2, 3);
	r7.set(f);
	EXPECT_EQ(twoThirds, r7);
}

// test set denominator - negative to negative, neg to pos
TEST_F(RationalTest, TestSetDenominatorNegative) {
	Rational r(-1,2);
	r.setDenominator(-4);
	Rational expected(1, 4);

	EXPECT_EQ(expected, r);

	r = Rational(1, 3);
	r.setDenominator(-3);

	expected = Rational(-1, 3);
	EXPECT_EQ(expected, r);

	r = Rational(-1, 3);
	r.setDenominator(4);
	expected = Rational(-1, 4);
	EXPECT_EQ(expected, r);
}


// test add
TEST_F(RationalTest, TestAdd) {
	Rational r(2);
	Rational r2(1, 2);
	Rational r3(-2, 3);

	EXPECT_EQ(r.add(r), 4);
	ASSERT_NE(r, 4);  // assert non mutating
	EXPECT_EQ(r.add(2), 4);
	EXPECT_EQ(r + r, 4);
	EXPECT_EQ(r + 2, 4);

	EXPECT_EQ(r2.add(half), one);
	EXPECT_EQ(r2 + half, one);

	EXPECT_EQ(r3.add(twoThirds), 0);
	EXPECT_EQ(r3 + twoThirds, 0);

	// add float
	EXPECT_EQ(Rational(1.5), one + (float)0.5);
	EXPECT_EQ(Rational(1.5), one.add((float)0.5));

	// add double
	EXPECT_EQ(Rational(1.5), one + (double)0.5);
	EXPECT_EQ(Rational(1.5), one.add((double)0.5));
}

// test subtract
TEST_F(RationalTest, TestSubtract) {
	Rational r(2);
	Rational r2(1, 2);
	Rational r3(-2, 3);

	EXPECT_EQ(r.subtract(r), 0);
	ASSERT_NE(r, 0);  // assert non mutating
	EXPECT_EQ(r.subtract(2), 0);
	EXPECT_EQ(r - r, 0);
	EXPECT_EQ(r - 2, 0);

	EXPECT_EQ(r2.subtract(half), 0);
	EXPECT_EQ(r2 - half, 0);

	// subtract from a negative
	EXPECT_EQ(r3.subtract(twoThirds), Rational(-4,3));
	EXPECT_EQ(r3 - twoThirds, Rational(-4,3));

	// subtract float
	EXPECT_EQ(half, one - (float)0.5);
	EXPECT_EQ(half, one.subtract((float)0.5));

	// subtract double
	EXPECT_EQ(half, one - (double)0.5);
	EXPECT_EQ(half, one.subtract((double)0.5));

	Fraction f(1, 4);
	Fraction actual = f - half;
	Fraction expected = Fraction(-1, 4);
	EXPECT_EQ(expected, actual);
}

// test muliply
TEST_F(RationalTest, TestMultiply) {
	Rational r(2);
	Rational r2(1, 2);
	Rational r3(-2, 3);

	EXPECT_EQ(r.multiply(r), 4);
	ASSERT_NE(r, 4);  // assert non mutating
	EXPECT_EQ(r.multiply(2), 4);
	EXPECT_EQ(r * r, 4);
	EXPECT_EQ(r * 2, 4);

	EXPECT_EQ(r2.multiply(half), Rational(1,4));
	EXPECT_EQ(r2 * half, Rational(1,4));

	// multiply by negative
	EXPECT_EQ(r3.multiply(twoThirds), Rational(-4, 9));
	EXPECT_EQ(r3 * twoThirds, Rational(-4, 9));

	// multiply by float
	EXPECT_EQ(Rational(1,3), twoThirds * (float)0.5);
	EXPECT_EQ(Rational(1,3), twoThirds.multiply((float)0.5));

	// multiply by double
	EXPECT_EQ(Rational(1,3), twoThirds * (double)0.5);
	EXPECT_EQ(Rational(1,3), twoThirds.multiply((double)0.5));
}

// test divide by zero with multiply - and caught exceptions
TEST_F(RationalTest, TestMultiplyDivideByZeroException) {
	Rational r(1, 4); // fraction
	r.setDenominator(0); // make invalid

	try {
		half.multiply(r);
		FAIL();
	}
	catch (DivideByZeroException &ex) {
		std::cout << ex << std::endl;
	}
	catch (std::exception) {
		FAIL();
	}

	try {
		half *= r;
		FAIL();
	}
	catch (DivideByZeroException &ex) {
		std::cout << ex << std::endl;
	}
	catch (std::exception) {
		FAIL();
	}

	try {
		Rational r2 = half * r;
		FAIL();
	}
	catch (DivideByZeroException &ex) {
		std::cout << ex << std::endl;
	}
	catch (std::exception) {
		FAIL();
	}
}

// test divide by zero - and caught exceptions
TEST_F(RationalTest, TestDivideByZeroException) {
	Rational r(0);

	try {
		one / r;		
		FAIL();
	}
	catch (DivideByZeroException &ex) {
		std::cout << ex << std::endl;
	}
	catch (std::exception) {
		FAIL();
	}

	try {
		one.divide(r);
		FAIL();
	}
	catch (DivideByZeroException &ex) {
		std::cout << ex << std::endl;
	}
	catch (std::exception) {
		FAIL();
	}

	try {
		one.divide(0);
		FAIL();
	}
	catch (DivideByZeroException &ex) {
		std::cout << ex << std::endl;
	}
	catch (std::exception) {
		FAIL();
	}

	r = Rational(0.0);
	try {
		one.divide(r);
		FAIL();
	}
	catch (DivideByZeroException &ex) {
		std::cout << ex << std::endl;
	}
	catch (std::exception) {
		FAIL();
	}

	try {
		one.divide((float)0.0);
		FAIL();
	}
	catch (DivideByZeroException &ex) {
		std::cout << ex << std::endl;
	}
	catch (std::exception) {
		FAIL();
	}

	try {
		one.divide((double)0.0);
		FAIL();
	}
	catch (DivideByZeroException &ex) {
		std::cout << ex << std::endl;
	}
	catch (std::exception) {
		FAIL();
	}
}

// test divide
TEST_F(RationalTest, TestDivide) {
	Rational r(2);
	Rational r2(1, 2);
	Rational r3(-2, 3);

	EXPECT_EQ(r.divide(r), 1);
	ASSERT_NE(r, 1);  // assert non mutating
	EXPECT_EQ(r.divide(2), 1);
	EXPECT_EQ(r / 2, 1);
	EXPECT_EQ(r / r, 1);

	EXPECT_EQ(r2.divide(half), 1);
	EXPECT_EQ(r2 / half, 1);

	// divide by negative
	EXPECT_EQ(r3.divide(twoThirds), -1);
	EXPECT_EQ(r3 / twoThirds, -1);

	// divide by float
	EXPECT_EQ(Rational(4,3), twoThirds / (float)0.5);
	EXPECT_EQ(Rational(4,3), twoThirds.divide((float)0.5));

	// divide by double
	EXPECT_EQ(Rational(4,3), twoThirds / (double)0.5);
	EXPECT_EQ(Rational(4,3), twoThirds.divide((double)0.5));
}

// test pow
TEST_F(RationalTest, TestPow) {
	EXPECT_EQ(Rational(1, 4), half.pow(2));
	ASSERT_NE(half, Rational(1,4));  // assert non mutating
	
	EXPECT_EQ(Rational(8, 27), twoThirds.pow(3));

	// raise to 0
	EXPECT_EQ(Rational(1), half.pow(0));
	// raise to 1
	EXPECT_EQ(half, half.pow(1));

	// raise to negative
	Rational r(1, 4);
	EXPECT_EQ(Rational(16), r.pow(-2));

	Rational actual = twoThirds.pow(-2);
	Rational expected = Rational(9, 4);
	EXPECT_EQ(expected, actual);
}

// test pow - exception
TEST_F(RationalTest, TestPowDivideByZeroException) {
	Rational r(1, 4);
	r.setDenominator(0); // make invalid
	try {
		r.pow(2);
		FAIL();
	}
	catch (DivideByZeroException &ex) {
		std::cout << ex << std::endl;
	}
	catch (std::exception) {
		FAIL();
	}
}

// test negate
TEST_F(RationalTest, TestNegate) {
	Rational r(-1, 2);
	EXPECT_EQ(half, r.negate());
	ASSERT_NE(r, half); // assert non mutating

	Rational r2(2, 3);
	EXPECT_EQ(Rational(-2, 3), r2.negate());
}


// test abs
TEST_F(RationalTest, TestAbs) {
	Rational r(-1, 2);
	EXPECT_EQ(r.abs(), half);
	ASSERT_NE(r, half); // assert non mutating

	Rational r2(2, 3);
	EXPECT_EQ(r2.abs(), twoThirds);
}

// test square
TEST_F(RationalTest, TestSquare) {
	Rational r(-1, 2);
	EXPECT_EQ(Rational(1,4), r.square());
	ASSERT_NE(r, half); // assert non mutating

	Rational r2(2, 3);
	EXPECT_EQ(Rational(4,9), r2.square());
}

// test inv
TEST_F(RationalTest, TestInv) {
	EXPECT_EQ(Rational(2), half.inv());
	ASSERT_NE(half, Rational(2)); // assert non mutating

	Rational r(2, 3);
	EXPECT_EQ(Rational(3, 2), r.inv());

	// invert zero should be zero
	Rational r2(0);
	EXPECT_EQ(r2, r2.inv());

	Rational r3(-1, 2);
	EXPECT_EQ(Rational(-2), r3.inv());
}

// test get numerator/denominator
TEST_F(RationalTest, TestGet) {	
	EXPECT_EQ(1, half.getNumerator());
	EXPECT_EQ(2, half.getDenominator());

	Rational r(0);
	EXPECT_EQ(0, r.getNumerator());
	EXPECT_EQ(1, r.getDenominator());

	Rational r2(-1, 4);
	EXPECT_EQ(-1, r2.getNumerator());
	EXPECT_EQ(4, r2.getDenominator());

	Rational r3(4, -3);
	EXPECT_EQ(-4, r3.getNumerator());
	EXPECT_EQ(3, r3.getDenominator());
}

// test to double
TEST_F(RationalTest, TestToDouble) {
	EXPECT_DOUBLE_EQ(0.5, half.toDouble());

	Rational r(30);
	EXPECT_DOUBLE_EQ(30.0, r.toDouble());

	// test that it's "close enough"
	EXPECT_NEAR(0.666666666, twoThirds.toDouble(), 0.0000001);
}

// test to double - divide by zero exception
TEST_F(RationalTest, TestToDoubleDivideByZeroException) {
	Rational r(1, 4);
	r.setDenominator(0); // make invalid

	try {
		r.toDouble();
		FAIL();
	}
	catch (DivideByZeroException &ex) {
		std::cout << ex << std::endl;
	}
	catch (std::exception) {
		FAIL();
	}
}

// test write
TEST_F(RationalTest, TestWrite) {
	std::stringstream ss;
	std::stringstream ss2;

	std::string expected = "1/2";
	half.write(ss);
	ss2 << half;

	std::string actual = ss.str();
	std::string actual2 = ss2.str();

	EXPECT_EQ(expected, actual);
	EXPECT_EQ(expected, actual2);

	expected = "0.5";
	ss.str("");
	ss2.str("");

	half.write(ss, Rational::DECIMAL);
	ss2 << usedecimal << half;
	actual = ss.str();
	actual2 = ss2.str();

	EXPECT_EQ(expected, actual);
	EXPECT_EQ(expected, actual2);

	Rational r(-3,4);
	expected = "-3/4";
	ss.str("");
	r.write(ss);
	actual = ss.str();
	EXPECT_EQ(expected, actual);

	expected = "-0.75";
	ss.str("");
	r.write(ss, Rational::DECIMAL);
	actual = ss.str();
	EXPECT_EQ(expected, actual);

	Rational r2(20);
	expected = "20";
	ss.str("");
	r2.write(ss);
	actual = ss.str();
	EXPECT_EQ(expected, actual);

	expected = "20";
	ss.str("");
	r2.write(ss, Rational::DECIMAL);
	actual = ss.str();
	EXPECT_EQ(expected, actual);

	// test fraction's stream operator
	Fraction f(0);
	expected = "0";
	ss.str("");
	ss << f;
	actual = ss.str();
	EXPECT_EQ(expected, actual);

	// make invalid
	f.setNumerator(1);
	f.setDenominator(0);
	expected = "Fraction 1/0 is invalid";
	ss.str("");
	ss << f;
	actual = ss.str();
	EXPECT_EQ(expected, actual);
}

// test write - exception
TEST_F(RationalTest, TestWriteDivideByZeroException) {
	Rational r(1, 4);
	r.setDenominator(0);
	try {
		// this should throw an exception
		r.write(std::cout, Rational::DECIMAL);
		FAIL();
	}
	catch (DivideByZeroException &ex) {
		std::cout << ex << std::endl;
	}
	catch (std::exception) {
		FAIL();
	}

	try {
		// this should throw an exception
		std::cout << usedecimal << r << std::endl;
		FAIL();
	}
	catch (DivideByZeroException &ex) {
		std::cout << ex << std::endl;
	}
	catch (std::exception) {
		FAIL();
	}
}

// test to-string
TEST_F(RationalTest, TestToString) {
	std::string expected = "1/2";
	std::string actual = half.toString();
	EXPECT_EQ(expected, actual);
}

// test read
TEST_F(RationalTest, TestRead) {
	Rational actual;
	Rational actual2;
	std::stringstream ss;
	std::stringstream ss2;
	ss.str("4/3");
	ss2.str("4/3");
	actual.read(ss);
	ss2 >> actual2;

	EXPECT_EQ(Rational(4, 3), actual);
	EXPECT_EQ(Rational(4, 3), actual2);

	ss.clear();
	ss.str("30");
	ss2.clear();
	ss2.str("30");
	actual.read(ss);
	ss2 >> actual2;

	EXPECT_EQ(Rational(30), actual);
	EXPECT_EQ(Rational(30), actual2);

	ss.clear();
	ss.str("-30/60");
	ss2.clear();
	ss2.str("-30/60");
	actual.read(ss);
	ss2 >> actual2;

	EXPECT_EQ(half.negate(), actual);
	EXPECT_EQ(half.negate(), actual2);

	ss.clear();
	ss.str("0.75");
	ss2.clear();
	ss2.str("0.75");
	actual.read(ss);
	ss2 >> actual2;

	EXPECT_EQ(Rational(3,4), actual);
	EXPECT_EQ(Rational(3,4), actual2);

	ss.clear();
	ss.str("12.5/2.5");   // this is a valid rational number -- comes out to 5
	ss2.clear();
	ss2.str("12.5/2.5");
	actual.read(ss);
	ss2 >> actual2;

	EXPECT_EQ(Rational(5), actual);
	EXPECT_EQ(Rational(5), actual2);

	ss.clear();
	ss.str("12/3 ");
	ss2.clear();
	ss2.str("12/3 ");
	actual.read(ss);
	ss2 >> actual2;

	EXPECT_EQ(Rational(4), actual);
	EXPECT_EQ(Rational(4), actual2);
	
}

// test read -- invalid format exception
TEST_F(RationalTest, TestReadInvalidFormatException) {
	Rational actual;
	Rational actual2;
	std::stringstream ss;
	std::stringstream ss2;
	std::string expected = "4/"; // set to an invalid format
	ss.str(expected);  
	ss2.str(expected);

	try {
		actual.read(ss);
		FAIL();
	}
	catch (InvalidFormatException &ex) {
		std::cout << ex << std::endl;		
	}
	catch (std::exception) {
		FAIL();
	}

	try {
		ss2 >> actual2;
		FAIL();
	}
	catch (InvalidFormatException &ex) {
		std::cout << ex << std::endl;
	}
	catch (std::exception) {
		FAIL();
	}

	expected = "12.";
	ss.clear();
	ss.str(expected); 
	ss2.clear();
	ss2.str(expected);

	try {
		actual.read(ss);
		FAIL();
	}
	catch (InvalidFormatException &ex) {
		std::cout << ex << std::endl;
	}
	catch (std::exception) {
		FAIL();
	}

	try {
		ss2 >> actual2;
		FAIL();
	}
	catch (InvalidFormatException &ex) {
		std::cout << ex << std::endl;
	}
	catch (std::exception) {
		FAIL();
	}

	expected = "12/12/43";
	ss.clear();
	ss.str(expected);   
	ss2.clear();
	ss2.str(expected);

	try {
		actual.read(ss);
		FAIL();
	}
	catch (InvalidFormatException &ex) {
		std::cout << ex << std::endl;
	}
	catch (std::exception) {
		FAIL();
	}

	try {
		ss2 >> actual2;
		FAIL();
	}
	catch (InvalidFormatException &ex) {
		std::cout << ex << std::endl;
	}
	catch (std::exception) {
		FAIL();
	}

	expected = "abcd";
	ss.clear();
	ss.str(expected);
	ss2.clear();
	ss2.str(expected);

	try {
		actual.read(ss);
		FAIL();
	}
	catch (InvalidFormatException &ex) {
		std::cout << ex << std::endl;
	}
	catch (std::exception) {
		FAIL();
	}

	try {
		ss2 >> actual2;
		FAIL();
	}
	catch (InvalidFormatException &ex) {
		std::cout << ex << std::endl;
	}
	catch (std::exception) {
		FAIL();
	}

	expected = "";
	ss.clear();
	ss.str(expected);
	ss2.clear();
	ss2.str(expected);

	try {
		actual.read(ss);
		FAIL();
	}
	catch (InvalidFormatException &ex) {
		std::cout << ex << std::endl;
	}
	catch (std::exception) {
		FAIL();
	}

	try {
		ss2 >> actual2;
		FAIL();
	}
	catch (InvalidFormatException &ex) {
		std::cout << ex << std::endl;
	}
	catch (std::exception) {
		FAIL();
	}

	expected = "12/3 12";
	ss.clear();
	ss.str(expected);
	ss2.clear();
	ss2.str(expected);

	try {
		actual.read(ss);
		FAIL();
	}
	catch (InvalidFormatException &ex) {
		std::cout << ex << std::endl;
	}
	catch (std::exception) {
		FAIL();
	}

	try {
		ss2 >> actual2;
		FAIL();
	}
	catch (InvalidFormatException &ex) {
		std::cout << ex << std::endl;
	}
	catch (std::exception) {
		FAIL();
	}
}

// test read -- divide by zero exeption
TEST_F(RationalTest, TestReadDivideByZeroException) {
	Rational actual;
	Rational actual2;
	std::stringstream ss;
	std::stringstream ss2;
	ss.str("4/0");
	ss2.str("4/0");

	try {
		actual.read(ss);
		FAIL();
	}
	catch (DivideByZeroException &ex) {
		std::cout << ex << std::endl;
	}
	catch (std::exception) {
		FAIL();
	}

	try {
		ss2 >> actual2;
		FAIL();
	}
	catch (DivideByZeroException &ex) {
		std::cout << ex << std::endl;
	}
	catch (std::exception) {
		FAIL();
	}
}

// test to lowest terms - exception
TEST_F(RationalTest, TestToLowestTermsDivideByZeroException) {
	Rational r(1, 4);
	r.setDenominator(0);
	try {
		Rational::toLowestTerms(r);
	}
	catch (DivideByZeroException &ex) {
		std::cout << ex << std::endl;
	}
	catch (std::exception) {
		FAIL();
	}
}

// test to common denominator - exception
TEST_F(RationalTest, TestToCommonDenominatorDivideByZeroException) {
	Rational r(1, 4);
	Rational r2(1, 6);
	r.setDenominator(0);
	try {
		Rational::toCommonDenominator(r, r2);
	}
	catch (DivideByZeroException &ex) {
		std::cout << ex << std::endl;
	}
	catch (std::exception) {
		FAIL();
	}
}

// print to lowest terms -- this just guarantees code coverage no possible way to throw exception
TEST_F(RationalTest, TestPrintInLowestTerms) {
	Rational r(4, 8);
	r.printFractionInLowestTerms();
	std::cout << std::endl;

	r.setDenominator(0);
	r.printFractionInLowestTerms();
	std::cout << std::endl;
}

// test create rational - exception
TEST_F(RationalTest, TestCreateRationalDivideByZeroException) {
	try {
		// create a rational that will throw an exception in constructor
		Rational r(1, 0); // from two ints
		FAIL();
	}
	catch (DivideByZeroException &ex) {
		std::cout << ex << std::endl;
	}
	catch (std::exception) {
		FAIL();
	}

	// create a rational that will throw an exception in constructor
	Rational r(1, 4);
	r.setDenominator(0); // make invalid
	try {
		Rational r2(r); // throw exception
		FAIL();
	}
	catch (DivideByZeroException &ex) {
		std::cout << ex << std::endl;
	}
	catch (std::exception) {
		FAIL();
	}

	Fraction f(1, 4);
	f.setDenominator(0);
	try {
		Rational r2(f); // throw exception
		FAIL();
	}
	catch (DivideByZeroException &ex) {
		std::cout << ex << std::endl;
	}
	catch (std::exception) {
		FAIL();
	}
}
