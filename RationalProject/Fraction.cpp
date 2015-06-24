/*
* File: Fraction.cpp
* Author: Ryan Johnson
* Email: johnsonrw82@csu.fullerton.edu
*
* Implementation for class Fraction
* Additional capability such as lowest terms reduction on an object and some static functions has been added
*/

#include "Fraction.h"
#include <algorithm>

using namespace rational::exception;

// default constructor
Fraction::Fraction() : numerator(0), denominator(1) {}

// integer constructor
Fraction::Fraction(const int numerator, const int denominator) : numerator( (denominator < 0) ? numerator*-1 : numerator), denominator(std::abs(denominator)) {}

// copy constructor
Fraction::Fraction(const Fraction& fraction) : numerator((fraction.denominator < 0) ? fraction.numerator*-1 : fraction.numerator), denominator(std::abs(fraction.denominator)) {}

// set numerator
void Fraction::setNumerator(const int numerator) {
	this->numerator = numerator;
}

// set denominator
void Fraction::setDenominator(const int denominator) {
	// if the denominator is negative, multiply the numerator by -1
	if (denominator < 0) {
		setNumerator(getNumerator() * -1);
	}
	this->denominator = std::abs(denominator);
}

// get numerator
int Fraction::getNumerator() const {
	return numerator;
}

// get denominator
int Fraction::getDenominator() const {
	return denominator;
}

// operator overloads
// overloaded equals operator that sets the fraction to a given integer value
Fraction& Fraction::operator=(const int integerValue) {
	// copy and swap
	Fraction tmp(integerValue, 1);

	std::swap(numerator, tmp.numerator);
	std::swap(denominator, tmp.denominator);

	return *this;
}
// overloaded equals operator that sets the fraction to a given fraction
Fraction& Fraction::operator=(Fraction fraction) {
	// copy and swap
	Fraction tmp(fraction);

	std::swap(numerator, tmp.numerator);
	std::swap(denominator, tmp.denominator);

	return *this;
}

// addition of another fraction
Fraction Fraction::operator+(const Fraction& fraction) {
	Fraction fraction1(*this);
	Fraction fraction2(fraction);

	// convert fractions to common denominators
	toCommonDenominator(fraction1, fraction2);

	// add them together (by adding the numerators)
	fraction1.setNumerator(fraction1.getNumerator() + fraction2.getNumerator());

	return fraction1;
}

// subtraction of another fraction
Fraction Fraction::operator-(const Fraction& fraction) {
	Fraction tmp(fraction);
	tmp = tmp * -1;
	
	return *this + tmp;
}

// multiplication by another fraction
Fraction Fraction::operator*(const Fraction& fraction) {
	Fraction tmp(*this);

	tmp.setNumerator(tmp.getNumerator() * fraction.getNumerator());

	// divide by zero (masked in a multiply)
	if (tmp.getDenominator() == 0 || fraction.getDenominator() == 0) {
		throw DivideByZeroException(__FILE__, __LINE__);
	}
	tmp.setDenominator(tmp.getDenominator() * fraction.getDenominator());

	return tmp;
}

// division by another fraction
Fraction Fraction::operator/(const Fraction& fraction) {
	Fraction tmp(fraction);

	// divide by zero -- if argument fraction is zero, then it's a DBZ
	if (fraction.getNumerator() == 0) {
		throw DivideByZeroException(__FILE__, __LINE__);
	}

	// invert the fraction - dividing a fraction by a fraction is multiplying by the inverse
	tmp = tmp.inv();

	return *this * tmp;
}

// equality operators
// return true if these Fractions are equal
bool Fraction::operator==(const Fraction& fraction) const {
	return getNumerator() == fraction.getNumerator() && getDenominator() == fraction.getDenominator();
}

// return true if these fractions are not equal
bool Fraction::operator!=(const Fraction& fraction) const {
	return !(*this == fraction);
}

// overload of the << operator.
// implemented as a non-member function since the lhs of the parameter list doesn't belong to Fraction
std::ostream& operator<<(std::ostream& os, const Fraction& fraction) {
	if (fraction.getNumerator() == 0) {
		return os << 0;
	}
	else if (fraction.getDenominator() == 1) {
		return os << fraction.getNumerator();
	}
	else if (fraction.getDenominator() == 0) {
		return os << "Fraction " << fraction.getNumerator() << "/" << fraction.getDenominator() << " is invalid";
	}

	return os << fraction.getNumerator() << "/" << fraction.getDenominator();
}

// print the fraction in lowest terms;
void Fraction::printFractionInLowestTerms() {
	// print the fraction in lowest terms
	std::cout << toLowestTermsString().c_str();
}

// output the value of the fraction as a double
double Fraction::toDouble() const {
	// return 0 when denominator is 0
	if ( getDenominator() == 0 ) {
		throw DivideByZeroException(__FILE__, __LINE__);
	}

	return (double)getNumerator()/(double)getDenominator();
}

// return the inverse of this fraction
Fraction Fraction::inv() const {
	if (getNumerator() == 0 ){
		return Fraction(0);
	}
	return Fraction(getDenominator(), getNumerator());
}

// private function to find the GCD between numerator and denominator
int Fraction::getGcd(const int divisor, const int remainder) {
	// use Euclid's algorithm to find the gcd
	// find the remainder by modding dividend by divisor
	// repeat until remainder is 0, then return the divisor
	return ( remainder == 0 ) ? divisor : getGcd(remainder, divisor % remainder);
}

// get the LCM (least common multiple of two numbers
int Fraction::getLcm(const int num1, const int num2) {

	// find the GCD
	// divisor is the min of the two numbers
	int divisor = std::min(num1, num2);
	// dividend is the max of the two numbers
	int dividend = std::max(num1, num2);
	// get the GCD -- prevent divide by zero
	if (divisor == 0) {
		throw DivideByZeroException(__FILE__, __LINE__);
	}

	int gcd = getGcd(divisor, dividend % divisor);

	// divide by zero exception
	if (gcd == 0) {
		throw DivideByZeroException(__FILE__, __LINE__);
	}

	// the LCM is the product of the two numbers, divided by GCD
	int lcm = (num1 / gcd) * num2;

	return lcm;
}

// private function returning a string representation of the fraction in lowest terms
// this does not modify the fraction to be in lowest terms, only returns the string representing it
std::string Fraction::toLowestTermsString() {
	std::string result;

	// invalid fraction
	if (getDenominator() == 0) {
		result = "Fraction " + numToString(getNumerator());
		result += "/" + numToString(getDenominator());
		result += " is invalid.";
	}

	// this will be true for 0 fractions
	else if (getNumerator() == 0) {
		result = numToString(getNumerator());
	}
	// else - perform the math
	else {
		// find the GCD
		// divisor is the min of the two numbers
		int divisor = std::min(getNumerator(), getDenominator());
		// dividend is the max of the two numbers
		int dividend = std::max(getNumerator(), getDenominator());
		// get the GCD
		int gcd = getGcd(divisor, dividend % divisor);

		// divide each term by the gcd
		int newNumerator = numerator / gcd;
		int newDenominator = getDenominator() / gcd;		

		newNumerator = (newDenominator < 0) ? newNumerator * -1 : newNumerator;
		newDenominator = std::abs(newDenominator);

		// denominator of 1 is just the numerator
		if (newDenominator == 1) {
			result = numToString(newNumerator);
		}
		// valid fraction
		else {
			result = numToString(newNumerator) + "/";
			result += numToString(newDenominator);
		}
	}

	return result;
}

// this function will reduce the fraction to lowest terms, and will keep it that way
void Fraction::toLowestTerms(Fraction& fractionObj) {
	if (fractionObj.getNumerator() == 0) {
		fractionObj.setDenominator(1); // set to 1, since it's a zero fraction
	}
	else if (fractionObj.getDenominator() != 0) {
		// find the GCD
		// divisor is the min of the two numbers
		int divisor = std::min(fractionObj.getNumerator(), fractionObj.getDenominator());
		// dividend is the max of the two numbers
		int dividend = std::max(fractionObj.getNumerator(), fractionObj.getDenominator());
		// get the GCD
		int gcd = getGcd(divisor, dividend % divisor);

		// divide each term by the gcd
		int newNumerator = fractionObj.getNumerator() / gcd;
		int newDenominator = fractionObj.getDenominator() / gcd;

		newNumerator = (newDenominator < 0) ? newNumerator * -1 : newNumerator;
		newDenominator = std::abs(newDenominator);

		// set the numerator and denominator
		fractionObj.setNumerator(newNumerator);
		fractionObj.setDenominator(newDenominator);
	}
	else {
		throw DivideByZeroException(__FILE__, __LINE__);
	}
}

// function that will modify the fraction references to have common denominators (supports things like add/sub and comparison)
void Fraction::toCommonDenominator(Fraction& fraction1, Fraction& fraction2) {
	// get the lcm of the denominators
	try {
		int lcm = getLcm(fraction1.getDenominator(), fraction2.getDenominator());


		// use the LCM to determine how much to multiply each fraction by in order to get the denominators equal to the LCM
		// no divide by zero can happen here since getLcm() will throw it if possible
		int mult1 = lcm / fraction1.getDenominator();
		int mult2 = lcm / fraction2.getDenominator();

		// multiply each fraction by the amount needed to make the denominators equal to LCM
		fraction1 = fraction1 * Fraction(mult1, mult1);
		fraction2 = fraction2 * Fraction(mult2, mult2);
	}
	catch (DivideByZeroException &ex) {
		throw ex;
	}
}
