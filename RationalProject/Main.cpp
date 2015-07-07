/*
* File: Main.cpp
* Author: Ryan Johnson
* Email: johnsonrw82@csu.fullerton.edu
*
* This is a simple main function that will create some Rationals, test the functionality, create a RationalArray and test the functionality, and
* finally analyze a document read from stdin and print out the character counts and ratios.
*/

#include "Rational.h"
#include "RationalArray.h"
#include "DivideByZeroException.h"
#include "InvalidFormatException.h"
#include "DocumentCount.h"
#include "DocumentRatio.h"

#include <regex>
#include <string>
#include <iostream>

using namespace rational;
using namespace rational::exception;

// function prototypes
std::vector<std::string> split(const std::string &input);
void testRational();
void testRationalArray();
void analyzeDocument();

int main() {
	// test Rational
	testRational();

	std::cout << "\n\n";
	
	// test Rational Array
	testRationalArray();

	std::cout << "\n\n";

	// process input
	analyzeDocument();

	return 0;
}

void testRational() {
	std::cout << "Testing class Rational..." << std::endl;

	// create a rational
	Rational aRational;
	// stringstream
	std::istringstream iss;
	// read in a number
	iss.str("4/3");
	aRational.read(iss);

	// write back out to std::cout
	aRational.write(std::cout, Rational::FRACTION);
	std::cout << "\n";

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

	std::cout << "\n";
	// test addition and equality
	Rational n1(5, 3);
	Rational n2(6, 5);
	Rational expectedResult(43, 15);  // 25/15 + 18/15 = 43/15
	if (n1 + n2 == expectedResult) {
		std::cout << n1 << " + " << n2 << " == " << expectedResult << std::endl;
	}
	else {
		std::cout << "Rational addition result incorrect" << std::endl;
	}

	std::cout << "\n";
	// test pow and equality
	n1 = Rational(1, 2);
	int pow = 3;
	expectedResult = Rational(1, 8);  // 1/2 ^ 3 = 1/8
	if (n1.pow(pow) == expectedResult) {
		std::cout << n1 << " ^ " << pow << " == " << expectedResult << std::endl;
	}
	else {
		std::cout << "Rational pow result incorrect" << std::endl;
	}

	std::cout << "\n";
	// test inverse and equality
	n1 = Rational(-5, 6);
	expectedResult = Rational(-6, 5);  // 1 / -5/6 = -6/5
	if (n1.inv() == expectedResult) {
		std::cout << "Inverse of " << n1 << " == " << expectedResult << std::endl;
	}
	else {
		std::cout << "Rational inverse result incorrect" << std::endl;
	}

	std::cout << "\n";
	// test divide and equality
	n1 = Rational(3, 4);
	n2 = Rational(6, 5);
	expectedResult = Rational(15, 24); // 3/4 / 6/5 = 3/4 * 5/6 = 15/24
	if (n1 / n2 == expectedResult) {
		std::cout << n1 << " / " << n2 << " == " << expectedResult << std::endl;
	}
	else {
		std::cout << "Rational division result incorrect" << std::endl;
	}

	std::cout << "\n";

	// test inequality
	n1 = Rational(5, 6);
	n2 = Rational(-6, 5);
	if (n2.inv() != n1) {
		std::cout << "Inverse of " << n2 << " (" << n2.inv() << ") != " << n1 << std::endl;
	}
	else {
		std::cout << "Inequality result incorrect" << std::endl;
	}

	std::cout << "\n";
	// test print + create rational from double
	double d = 0.875;
	n1 = Rational(d);
	std::cout << "Rational created from double value " << d << ":\n";
	std::cout << "As a fraction = ";
	n1.write(std::cout, Rational::FRACTION);
	std::cout << "\nAs a floating point value = ";
	n1.write(std::cout, Rational::DECIMAL);
}

void testRationalArray() {
	std::cout << "Testing class RationalArray..." << std::endl;

	RationalArray ra(3);  // create a rational array
	// create some rationals
	Rational r(1, 2); // object
	Rational* r2 = new Rational(2, 3); // pointer references
	Rational* r3 = new Rational(3, 4);

	// initial size/capacity
	std::cout << "The size of the array is: " << ra.size() << " and the capacity is: " << ra.capacity() << std::endl;

	// add them to the array
	ra.add(r);
	ra.add(r3);
	ra.add(r2);

	// try invalid index
	try {
		ra.retrieve(-1);
	}
	catch (ArrayIndexOutOfBoundsException& e) {
		std::cerr << e.what() << std::endl;
	}

	// test retrieval
	Rational fromArray = ra.retrieve(2);
	if (fromArray == *r2) {
		std::cout << "The Rational retreived from the array should have been " << *r2 << " and it was" << std::endl;
	}
	else {
		std::cout << "Got the wrong Rational from the array at specified index" << std::endl;
	}

	// print the array contents
	std::cout << "\nRational array contents:" << std::endl;
	ra.printArray();

	// replace one with another
	Rational newRational(5, 6);
	std::cout << "Replacing " << *r3 << " at index 1 with " << newRational << std::endl;
	ra.replace(1, newRational);

	// print again
	std::cout << "\nRational array contents:" << std::endl;
	ra.printArray();

	// the size/capacity now that it's been filled
	unsigned int oldSize = ra.size();
	unsigned int oldCap = ra.capacity();
	std::cout << "\nThe size of the array is: " << oldSize << " and the capacity is: " << oldCap << std::endl;

	// add another object and test the capacity growth
	ra.add(Rational(10, 13));
	if (ra.size() > oldSize && ra.capacity() > oldCap) {
		std::cout << "\nThe new size of the array is: " << ra.size() << " and the new capacity is: " << ra.capacity() << std::endl;
	}
	else {
		std::cout << "\nThe size and capacity of the array should have increased, but didn't" << std::endl;
	}

	// print out the rationals to ensure they haven't been modified
	std::cout << "\nThe first three rationals created were, and they haven't been modified: " << std::endl;
	std::cout << r << std::endl;
	std::cout << *r2 << std::endl;
	std::cout << *r3 << std::endl;

	// no longer needed
	delete r2;
	delete r3;
}

// function that will analyze a document read from stdin
void analyzeDocument() {
	std::cout << "Analyzing document from stdin..." << std::endl;

	std::string line;
	std::vector<std::string> words;

	// read from stdin
	while (std::cin) {
		if (std::cin.eof()) {
			break;
		}

		getline(std::cin, line);	// buffer in the line
		std::vector<std::string> lineWords;
		// split the line on whitespace
		lineWords = split(line);
		// add to the vector containing all other words
		std::move(lineWords.begin(), lineWords.end(), std::back_inserter(words));
	}

	if (words.size() > 0) {
		std::cout << "For document containing the words:\n";
		for (auto word : words) {
			std::cout << word << "\n";
		}
		std::cout << "\nThe character counts and ratios are:" << std::endl;
	}
	else {
		std::cout << "There was no input processed" << std::endl;
	}

	// create a document count class object
	DocumentCount docCount(words);
	// print the character counts
	docCount.printCounts();
	std::cout << "\n";
	// verify character counts are equal
	try {
		if (docCount.isUpperLowerEqualToAlpha()) {
			std::cout << "Uppercase and Lowercase character count sum == total alphabetic characters" << std::endl;
		}
	}
	catch (CountsNotEqualException &ex) {
		std::cerr << ex << std::endl;
	}

	// construct ratio class object
	DocumentRatio ratio(docCount);

	// print the character ratios
	ratio.printRatios();

	// verify 1:1 ratios
	try {
		if (ratio.isOneToOne()) {
			std::cout << "Sum of ratios for alphabetic, decimal digits, punctuation, and other characters to total characters is 1" << std::endl;
		}
	}
	catch (RatiosNotEqualException &ex) {
		std::cerr << ex << std::endl;
	}
}

// helper function to split words on whitespace
std::vector<std::string> split(const std::string &input) {
	// initialize an istringstream
	std::istringstream iss(input);
	// result vector
	std::vector<std::string> result;

	// copy the stream results into the vector
	std::copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(), std::back_inserter(result));

	// return
	return result;
}