/**
* File: DocumentRatio.h
* Author: Ryan Johnson
* Email: johnsonrw82@csu.fullerton.edu
*
* Class definition for a document ratio counter. This class stores character count ratios for a document in an array of Rational objects.
*/

#ifndef DOCUMENT_RATIO_H
#define DOCUMENT_RATIO_H

#include "Rational.h"
#include "RationalArray.h"
#include "DocumentCount.h"

using namespace rational;
using namespace rational::exception;

class DocumentRatio {
public:
	// constructor, initialized from a vector of strings
	explicit DocumentRatio(const DocumentCount& docCount);
	// destructor
	~DocumentRatio();

	// return true if the sum of the ratios of alphabetic, decimal, punctuation, and other characters to total is 1:1
	// throws RatiosNotEqualException if not
	bool isOneToOne() const;
	
	// print character ratios
	void printRatios() const;

	// get the alpha to total character ratio
	Rational getAlpha() const;
	// get the lowercase to total character ratio
	Rational getLowercase() const;
	// get the uppercase to total character ratio
	Rational getUppercase() const;
	// get the decimal to total character ratio
	Rational getDecimal() const;
	// get the punctuation to total character ratio
	Rational getPunctuation() const;
	// get the other to total character ratio
	Rational getOther() const;
	// get the uppercase to lowercase character ratio
	Rational getUpperToLower() const;
	// get the uppercase to punctuation character ratio
	Rational getUpperToPunctuation() const;

	// get the character ratios collection
	RationalArray& getCharacterRatios() const;
private:
	int totalCharacters;
	RationalArray* characterRatioArray;

	// enum definition for indices
	enum RatioType {
		ALPHABETIC = 0,
		DECIMAL = 1,
		PUNCTUATION = 2,
		LOWERCASE = 3,
		UPPERCASE = 4,
		OTHER = 5,
		UPPER_TO_LOWER = 6,
		UPPER_TO_PUNCTUATION = 7
	};

	// initializer function
	void fillArray(const DocumentCount& docCount);	
};

/*
Exception class for when ratios do not add up to 1
*/
class RatiosNotEqualException : public RationalException {
public:
	// construct excepton and supertype
	RatiosNotEqualException(const std::string fileName, const int lineNum, 
		const Rational& alpha, const Rational& decimal, const Rational& punctuation, const Rational& other, const Rational& sum);

	// destructor
	virtual ~RatiosNotEqualException();

	// what caused the exception
	virtual const char* what() const throw();
	// stream overload
	friend std::ostream& operator<<(std::ostream& os, const RatiosNotEqualException& ex);
private:
	Rational alpha;
	Rational decimal;
	Rational punctuation;
	Rational other;
	Rational sum;
};

#endif