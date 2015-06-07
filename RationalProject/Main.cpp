/*
* File: Main.cpp
* Author: Ryan Johnson
* Email: johnsonrw82@csu.fullerton.edu
*
* This is a simple main function that will create some Rationals, add them to a RationalArray, and print them out to show results
*/

#include "Rational.h"
#include "RationalArray.h"

using namespace rational;

int main() {
	RationalArray ra;  // create a rational array
	// create some rationals
	Rational r(1, 2);
	Rational r2(2, 3);
	Rational r3(3, 4);

	// add two of them to the array
	ra.add(r);
	ra.add(r3);
	// replace one of them
	ra.replace(1,r2);

	// print the array contents
	ra.printArray();

	// print out the rationals to ensure they haven't been modified
	std::cout << "The rationals created are: " << std::endl;
	std::cout << r << std::endl;
	std::cout << r2 << std::endl;
	std::cout << r3 << std::endl;
	return 0;
}