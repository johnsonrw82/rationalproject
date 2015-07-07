/**
* File: DocumentRatio.cpp
* Author: Ryan Johnson
* Email: johnsonrw82@csu.fullerton.edu
*
* Implementation for a document ratio counter. This class stores character count ratios for a document in an array of Rational objects.
*/

#include "DocumentRatio.h"

// constructor
DocumentRatio::DocumentRatio(const DocumentCount& docCount) : totalCharacters(docCount.getTotalChars()) {
	// construct an array with initial capacity
	characterRatioArray = new RationalArray(8);
	// create Rational objects
	for (unsigned int i = 0; i < characterRatioArray->capacity(); i++) {
		characterRatioArray->add(Rational(0));
	}
	
	// if there are some characters, fill the array
	if ( totalCharacters > 0 ) {
		fillArray(docCount);
	}
}

// Destructor
DocumentRatio::~DocumentRatio() {
	// delete the object
	delete characterRatioArray;
}

// are these ratios one to one? true if so, exception if not
// sum of alpha, decimal, punctuation, and other = 1
bool DocumentRatio::isOneToOne() const {
	Rational alpha = getAlpha();
	Rational decimal = getDecimal();
	Rational punctuation = getPunctuation();
	Rational other = getOther();
	Rational sum = alpha + decimal + punctuation + other;

	// is it true?
	bool isOneToOne = sum.equal(Rational(1));

	// throw exception if not
	if (!isOneToOne) {
		throw RatiosNotEqualException(__FILE__, __LINE__, alpha, decimal, punctuation, other, sum);
	}

	return isOneToOne;
}

// initialize the container
void DocumentRatio::fillArray(const DocumentCount& docCount) {
	// use the document counts to initialize the ratios
	characterRatioArray->replace(ALPHABETIC, Rational(docCount.getAlpha().getNumerator(), totalCharacters));
	characterRatioArray->replace(UPPERCASE, Rational(docCount.getUppercase().getNumerator(), totalCharacters));
	characterRatioArray->replace(LOWERCASE, Rational(docCount.getLowercase().getNumerator(), totalCharacters));
	characterRatioArray->replace(DECIMAL, Rational(docCount.getDecimal().getNumerator(), totalCharacters));
	characterRatioArray->replace(PUNCTUATION, Rational(docCount.getPunctuation().getNumerator(), totalCharacters));
	characterRatioArray->replace(OTHER, Rational(docCount.getOther().getNumerator(), totalCharacters));

	// special ratios that could throw a DBZ exception
	if (docCount.getLowercase() != 0) {
		characterRatioArray->replace(UPPER_TO_LOWER, docCount.getUppercase() / docCount.getLowercase());
	}
	if (docCount.getPunctuation() != 0) {
		characterRatioArray->replace(UPPER_TO_PUNCTUATION, docCount.getUppercase() / docCount.getPunctuation());
	}
}

// print the ratios
void DocumentRatio::printRatios() const {
	std::cout << "Alphabetic to Total = " << getAlpha() << "\n" <<
		"Uppercase to Total = " << getUppercase() << "\n" <<
		"Lowercase to Total = " << getLowercase() << "\n" <<
		"Decimal Digit to Total = " << getDecimal() << "\n" <<
		"Punctuation to Total = " << getPunctuation() << "\n" <<
		"Other to Total = " << getOther() << "\n" << 
		"Upper to Lower = " << getUpperToLower() << "\n" <<
		"Upper to Punctuation = " << getUpperToPunctuation() << std::endl;
}


// get the alpha to total character ratio
Rational DocumentRatio::getAlpha() const {
	return characterRatioArray->retrieve(ALPHABETIC);
}
// get the lowercase to total character ratio
Rational DocumentRatio::getLowercase() const {
	return characterRatioArray->retrieve(LOWERCASE);
}
// get the uppercase to total character ratio
Rational DocumentRatio::getUppercase() const {
	return characterRatioArray->retrieve(UPPERCASE);
}
// get the decimal to total character ratio
Rational DocumentRatio::getDecimal() const {
	return characterRatioArray->retrieve(DECIMAL);
}
// get the punctuation to total character ratio
Rational DocumentRatio::getPunctuation() const {
	return characterRatioArray->retrieve(PUNCTUATION);
}
// get the other to total character ratio
Rational DocumentRatio::getOther() const {
	return characterRatioArray->retrieve(OTHER);
}
// get the uppercase to lowercase character ratio
Rational DocumentRatio::getUpperToLower() const {
	return characterRatioArray->retrieve(UPPER_TO_LOWER);
}
// get the uppercase to punctuation character ratio
Rational DocumentRatio::getUpperToPunctuation() const {
	return characterRatioArray->retrieve(UPPER_TO_PUNCTUATION);
}

/*
Exception class for DocumentRatio
*/
// constructor
RatiosNotEqualException::RatiosNotEqualException(const std::string fileName, const int lineNum, 
	const Rational& alpha, const Rational& decimal, const Rational& punctuation, const Rational& other, const Rational& sum) :
	RationalException("Sum of alphabetic, decimal, punctuation, and other ratios is not equal to 1", fileName, lineNum), 
	alpha(alpha), decimal(decimal), punctuation(punctuation), other(other), sum(sum) {}

// destructor
RatiosNotEqualException::~RatiosNotEqualException() {}

// return the information from the exception, including the ratios
const char* RatiosNotEqualException::what() const throw() {
	std::ostringstream os;
	os << RationalException::what() << "\nAlpha = " << alpha << "\nDecimal = " << decimal << "\nPunctuation = " << punctuation << "\nOther = " << other << "\nSum = " << sum;

	// copy to a char array
	rsize_t size = os.str().length() + 1;
	char* returnVal;
	try {
		returnVal = new char[size];
	}
	catch (std::bad_alloc &ex) {
		std::cerr << ex.what() << std::endl;
		std::terminate();
	}

	// safe copy
	strcpy_s(returnVal, size, os.str().c_str());

	// return char array -- wont work without an explicit copy
	return returnVal;
}

// stream operator overload
std::ostream& operator<<(std::ostream& os, const RatiosNotEqualException& ex) {
	os << ex.what();
	return os;
}
