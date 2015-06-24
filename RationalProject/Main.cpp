/*
* File: Main.cpp
* Author: Ryan Johnson
* Email: johnsonrw82@csu.fullerton.edu
*
* This is a simple main function that will create some Rationals, add them to a RationalArray, and print them out to show results
*/

#include "Rational.h"
#include "RationalArray.h"
#include "DivideByZeroException.h"
#include "InvalidFormatException.h"

using namespace rational;
using namespace rational::exception;

int main() {
	Rational aRational;
	std::istringstream iss;
	iss.str("4/3");
	aRational.read(iss);

	// write back out to std::cout
	aRational.write(std::cout, Rational::FRACTION);

	// test invalid argument (negative initial size)
	try {
		RationalArray ra1(-10);
	}
	catch (InvalidArgumentException &e) {
		std::cerr << e.what() << std::endl;
	}

	// test a divide by zero exception
	try {
		Rational r1(3);
		Rational r2(0, 0);
		Rational r3 = r1 / r2;
		std::cout << r3 << std::endl;
	}
	catch (DivideByZeroException &ex) {
		std::cerr << ex << std::endl; // try with stream overload
	}

	// test invalid format
	try {
		iss.clear();
		iss.str("4/x"); // invalid format
		Rational r4;
		r4.read(iss);
	}
	catch (InvalidFormatException &ex) {
		std::cerr << ex << std::endl;
	}

	RationalArray ra2;  // create a rational array
	// create some rationals
	Rational r(1, 2); // object
	Rational* r2 = new Rational(2, 3); // pointer references
	Rational* r3 = new Rational(3, 4);

	// add them to the array
	ra2.add(r);
	ra2.add(r3);
	ra2.add(r2);	 

	// try invalid index
	try {
		ra2.retrieve(-1);
	}
	catch (ArrayIndexOutOfBoundsException& e) {
		std::cerr << e.what() << std::endl;
	}

	// print the array contents
	std::cout << "Rational array contents:" << std::endl;
	ra2.printArray();

	// replace one with another
	ra2.replace(1, Rational(5, 6));

	// print again
	std::cout << "Rational array contents:" << std::endl;
	ra2.printArray();

	// print out the rationals to ensure they haven't been modified
	std::cout << "The rationals created were: " << std::endl;
	std::cout << r << std::endl;
	std::cout << *r2 << std::endl;
	std::cout << *r3 << std::endl;

	// no longer needed
	delete r2;
	delete r3;

	return 0;
}