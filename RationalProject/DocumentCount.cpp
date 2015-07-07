/**
* File: DocumentCount.cpp
* Author: Ryan Johnson
* Email: johnsonrw82@csu.fullerton.edu
*
* Implementation of a document counter. This class stores character counts for a document in an array of Rational objects.
*/

#include "DocumentCount.h"

// constructor
DocumentCount::DocumentCount(const std::vector<std::string>& document) : totalCharacters(0) {
	// initialize collection
	characterCountArray = new RationalArray(6);
	// add rational objects to the array
	for (unsigned int i = 0; i < characterCountArray->capacity(); i++) {
		characterCountArray->add(Rational(0));
	}
	
	// populate data
	fillArray(document);
}

// destructor
DocumentCount::~DocumentCount() {
	// delete the object
	delete characterCountArray;
}

// return true if the sum of the lowercase and uppercase equals the alphabetic count, throw CountsNotEqualException otherwise
bool DocumentCount::isUpperLowerEqualToAlpha() const {
	// get rational counts
	Rational alpha = getAlpha();
	Rational lower = getLowercase();
	Rational upper = getUppercase();

	// are they equal?
	bool countsEqual = (lower + upper).equal(alpha);

	// if not, throw exception
	if (!countsEqual) {
		throw CountsNotEqualException(__FILE__, __LINE__, lower, upper, alpha);
	}

	return countsEqual;
}

// get total characters
int DocumentCount::getTotalChars() const {
	return totalCharacters;
}

// fill the collection based on the contents of the vector
void DocumentCount::fillArray(const std::vector<std::string>& document) {
	// count each character in the word
	for (auto word : document) {
		// each character
		for (char c : word) {
			// determine the count to add to
			switch (getType(c)) {
				case UPPERCASE:
					addToUppercase();
					addToAlphabetic();
					break;
				case LOWERCASE:
					addToLowercase();
					addToAlphabetic();
					break;
				case DECIMAL:
					addToDecimal();
					break;
				case PUNCTUATION:
					addToPunctuation();
					break;
				case OTHER:
				default:
					addToOther();
					break;
			}
			// increment total
			totalCharacters++;
		}
	}
}

// Function to return the character type of the input character
DocumentCount::CharType DocumentCount::getType(const char c) const {
	DocumentCount::CharType result;

	// alphabetic
	if (isalpha(c)) {
		// uppercase
		if (isupper(c)) {
			result = UPPERCASE;
		}
		// lowercase
		else {
			result = LOWERCASE;
		}
	}
	// decimal digit
	else if (isdigit(c)) {
		result = DECIMAL;
	}
	// punctuation
	else if (ispunct(c)) {
		result = PUNCTUATION;
	}
	// something else
	else {
		result = OTHER;
	}

	return result;
}

// add one to the alpahbetic count
void DocumentCount::addToAlphabetic() {
	characterCountArray->replace(ALPHABETIC, getAlpha() + 1);
}
// add one to the decimal count
void DocumentCount::addToDecimal() {
	characterCountArray->replace(DECIMAL, getDecimal() + 1);
}
// add one to the punctuation count
void DocumentCount::addToPunctuation() {
	characterCountArray->replace(PUNCTUATION, getPunctuation() + 1);
}

// add one to the lowercase count
void DocumentCount::addToLowercase() {
	characterCountArray->replace(LOWERCASE, getLowercase() + 1);
}

// add one to the uppercase count
void DocumentCount::addToUppercase() {
	characterCountArray->replace(UPPERCASE, getUppercase() + 1);
}

// add one to the other count
void DocumentCount::addToOther() {
	characterCountArray->replace(OTHER, getOther() + 1);
}

// get the alpha character count
Rational DocumentCount::getAlpha() const {
	return characterCountArray->retrieve(ALPHABETIC);
}
// get the lowercase character count
Rational DocumentCount::getLowercase() const {
	return characterCountArray->retrieve(LOWERCASE);
}
// get the uppercase character count
Rational DocumentCount::getUppercase() const {
	return characterCountArray->retrieve(UPPERCASE);
}
// get the decimal character count
Rational DocumentCount::getDecimal() const {
	return characterCountArray->retrieve(DECIMAL);
}
// get the punctuation character count
Rational DocumentCount::getPunctuation() const {
	return characterCountArray->retrieve(PUNCTUATION);
}
// get the other character count
Rational DocumentCount::getOther() const {
	return characterCountArray->retrieve(OTHER);
}

// print the counts in the collection
void DocumentCount::printCounts() const {
	std::cout << "Alphabetic = " << getAlpha() << "\n" <<
		"Uppercase = " << getUppercase() << "\n" <<
		"Lowercase = " << getLowercase() << "\n" <<
		"Decimal Digit = " << getDecimal() << "\n" <<
		"Punctuation = " << getPunctuation() << "\n" <<
		"Other = " << getOther() << std::endl;
}

/*
Exception class for DocumentCount
*/
// constructor
CountsNotEqualException::CountsNotEqualException(const std::string fileName, const int lineNum, const Rational& lower, const Rational& upper, const Rational& total) :
	RationalException("Sum of uppercase and lowercase characters do not equal alphabetic total", fileName, lineNum), lower(lower), upper(upper), total(total) {}

// destructor
CountsNotEqualException::~CountsNotEqualException() {}

// return the information from the exception, including the counts
const char* CountsNotEqualException::what() const throw() {
	std::ostringstream os;
	os << RationalException::what() << "\nUpper = " << upper << "\nLower = " << lower << "\nTotal = " << total;

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
std::ostream& operator<<(std::ostream& os, const CountsNotEqualException& ex) {
	os << ex.what();
	return os;
}