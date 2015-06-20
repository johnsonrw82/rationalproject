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
	Rational r12;
	r12.read(std::cin);


	//RationalArray ra1(10000000);
	//RationalArray ra2(10000000); 
	//RationalArray ra3(10000000); 
	//RationalArray ra4(10000000); 
	try {
		RationalArray ra5(-10);
	}
	catch (InvalidArgumentException &e) {
		std::cerr << e.what() << std::endl;
	}

	try {
		throw DivideByZeroException("test", 12);
	}
	catch (DivideByZeroException &ex) {
		std::cerr << ex << std::endl;
	}

	try {
		throw InvalidFormatException("because you ugly" ,"test", 12);
	}
	catch (InvalidFormatException &ex) {
		std::cerr << ex << std::endl;
	}

	RationalArray ra;  // create a rational array
	// create some rationals
	Rational r(1, 2);
	Rational* r2 = new Rational(2, 3);
	Rational* r3 = new Rational(3, 4);

	// add two of them to the array
	ra.add(r);
	ra.add(r3);
	ra.add(r2);

	try {
		ra.retrieve(-1);
	}
	catch (ArrayIndexOutOfBoundsException& e) {
		std::cerr << e.what() << std::endl;
	}

	//std::cout << *(ra.retrieve(2)) << std::endl;
	// replace one of them
	//ra.replace(1,r2);

	// print the array contents
	ra.printArray();

	// print out the rationals to ensure they haven't been modified
	std::cout << "The rationals created are: " << std::endl;
	std::cout << r << std::endl;
	std::cout << *r2 << std::endl;
	std::cout << *r3 << std::endl;
	return 0;
}