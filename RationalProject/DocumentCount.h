/**
* File: DocumentCount.h
* Author: Ryan Johnson
* Email: johnsonrw82@csu.fullerton.edu
*
* Class definition for a document counter. This class stores character counts for a document in an array of Rational objects.
*/

#ifndef DOCUMENT_COUNT_H
#define DOCUMENT_COUNT_H

#include "Rational.h"
#include "RationalArray.h"
#include <stdexcept>
#include <vector>
#include <string>

using namespace rational;
using namespace rational::exception;

class DocumentCount {
public:
	// constructor, initialized from a vector of strings
	explicit DocumentCount(const std::vector<std::string>& document);
	// destructor
	~DocumentCount();

	// return true if the sum of lowercase and uppercase characters is equal to the total of alphabetic characters
	// throws CountsNotEqualException if not
	bool isUpperLowerEqualToAlpha() const;
	// get total characters
	int getTotalChars() const;

	// print character counts
	void printCounts() const;

	// get the alpha character count
	Rational getAlpha() const;
	// get the lowercase character count
	Rational getLowercase() const;
	// get the uppercase character count
	Rational getUppercase() const;
	// get the decimal character count
	Rational getDecimal() const;
	// get the punctuation character count
	Rational getPunctuation() const;
	// get the other character count
	Rational getOther() const;
private:
	int totalCharacters;
	RationalArray* characterCountArray;

	// enum definition for indices
	enum CharType {
		ALPHABETIC = 0,
		DECIMAL = 1,
		PUNCTUATION = 2,
		LOWERCASE = 3,
		UPPERCASE = 4,
		OTHER = 5
	};

	// private functions that will add to each respective count
	void addToAlphabetic();
	void addToDecimal();
	void addToPunctuation();
	void addToLowercase();
	void addToUppercase();
	void addToOther();

	// initializer function
	void fillArray(const std::vector<std::string>& document );
	
	// get character type
	CharType getType(const char c) const;	
};

/*
Exception class for when counts do not equal each other
*/
class CountsNotEqualException : public RationalException {
public:
	// construct excepton and supertype
	CountsNotEqualException(const std::string fileName, const int lineNum, const Rational& lower, const Rational& upper, const Rational& total);

	// destructor
	virtual ~CountsNotEqualException();

	// what caused the exception
	virtual const char* what() const throw();
	// stream overload
	friend std::ostream& operator<<(std::ostream& os, const CountsNotEqualException& ex);
private:
	Rational lower;
	Rational upper;
	Rational total;
};

#endif