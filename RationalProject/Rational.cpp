/**
* File: Rational.cpp
* Author: Ryan Johnson
* Email: johnsonrw82@csu.fullerton.edu
*
* Implementation of Rational number class, derived from Fracion
*/

#include "Rational.h"
#include <string>
#include <sstream>
#include <algorithm>

using namespace rational::exception;

namespace rational {

	Rational::RationalPrintType Rational::defaultPrintType = Rational::FRACTION;

	// constructors - use initializer lists to init all members
	Rational::Rational() {}

	// this constructor provides a default initialization for denominator, allowing it to be used
	// for init with a single numerator, or both
	Rational::Rational(const int numerator, const int denominator) : Fraction(numerator, denominator) {
		try {
			Fraction::toLowestTerms(*this);  // reduce to lowest terms
		}
		catch (DivideByZeroException &ex) {
			throw ex;
		}
	}
	// call the double version of this constructor
	Rational::Rational(const float floatVal) : Rational((double)floatVal) {}
	// init from a rational object
	Rational::Rational(const Rational& rationalObj) : Fraction(rationalObj) {
		try {
			Fraction::toLowestTerms(*this);  // reduce to lowest terms
		}
		catch (DivideByZeroException &ex) {
			throw ex;
		}
	}

	// create a Rational from a Fraction
	Rational::Rational(const Fraction& fractionObj) : Fraction(fractionObj) {
		try {
			Fraction::toLowestTerms(*this);  // reduce to lowest terms
		}
		catch (DivideByZeroException &ex) {
			throw ex;
		}
	}

	// this constructor will use a double value to create a fraction object using a helper function
	Rational::Rational(const double doubleVal) : Fraction(doubleToFraction(doubleVal)) {
		Fraction::toLowestTerms(*this);  // reduce to lowest terms
	}


	// assignment overloads
	Rational Rational::operator=(const int numerator) {
		// copy and swap -- overloaded function
		*this = (double)numerator;

		return *this;
	}
	Rational Rational::operator=(const float value) {
		// copy and swap -- overloaded function
		*this = (double)value;

		return *this;
	}
	Rational Rational::operator=(const double value) {
		// copy and swap
		Rational tmp(value);
		
		this->setNumerator(tmp.getNumerator());
		this->setDenominator(tmp.getDenominator());

		return *this;
	}
	Rational Rational::operator=(const Fraction& fractionObj) {
		// copy and swap
		Rational tmp(fractionObj);

		this->setNumerator(tmp.getNumerator());
		this->setDenominator(tmp.getDenominator());

		return *this;
	}
	Rational Rational::operator=(const Rational& rationalObj) {
		// copy and swap
		Rational tmp(rationalObj);

		this->setNumerator(tmp.getNumerator());
		this->setDenominator(tmp.getDenominator());

		return *this;
	}


	// operator overloads -- these are implemented in terms of their mutating counterparts
	Rational Rational::operator+(const int value) {
		Rational tmp(*this);
		tmp += value;
		return tmp;
	}
	Rational Rational::operator+(const float value){
		Rational tmp(*this);
		tmp += value;
		return tmp;
	}
	Rational Rational::operator+(const double value){
		Rational tmp(*this);
		tmp += value;
		return tmp;
	}
	Rational Rational::operator+(const Rational& rationalObj){
		Rational tmp(*this);
		tmp += rationalObj;
		return tmp;
	}
	Rational Rational::operator-(const int value){
		Rational tmp(*this);
		tmp -= value;
		return tmp;
	}
	Rational Rational::operator-(const float value){
		Rational tmp(*this);
		tmp -= value;
		return tmp;
	}
	Rational Rational::operator-(const double value){
		Rational tmp(*this);
		tmp -= value;
		return tmp;
	}
	Rational Rational::operator-(const Rational& rationalObj){
		Rational tmp(*this);
		tmp -= rationalObj;
		return tmp;
	}
	Rational Rational::operator*(const int value){
		Rational tmp(*this);
		tmp *= value;
		return tmp;
	}
	Rational Rational::operator*(const float value){
		Rational tmp(*this);
		tmp *= value;
		return tmp;
	}
	Rational Rational::operator*(const double value){
		Rational tmp(*this);
		tmp *= value;
		return tmp;
	}
	Rational Rational::operator*(const Rational& rationalObj){
		Rational tmp(*this);
		try {
			tmp *= rationalObj;
			return tmp;
		}
		catch (DivideByZeroException &ex) {
			throw ex;
		}
	}
	Rational Rational::operator/(const int value){
		Rational tmp(*this);
		try {
			tmp /= value;
			return tmp;
		}
		catch (DivideByZeroException &ex) {
			throw ex;
		}
	}
	Rational Rational::operator/(const float value){
		Rational tmp(*this);
		try {
			tmp /= value;
			return tmp;
		}
		catch (DivideByZeroException &ex) {
			throw ex;
		}
	}
	Rational Rational::operator/(const double value){
		Rational tmp(*this);
		try {
			tmp /= value;
			return tmp;
		}
		catch (DivideByZeroException &ex) {
			throw ex;
		}
	}
	Rational Rational::operator/(const Rational& rationalObj){
		Rational tmp(*this);
		try {
			tmp /= rationalObj;
			return tmp;
		}
		catch (DivideByZeroException &ex) {
			throw ex;
		}
	}

	// binary operations -- the four major operations are implemented in terms of their in-fix counterparts
	Rational Rational::add(const int value) {
		return *this + value;
	}
	Rational Rational::add(const double value){
		return *this + value;
	}
	Rational Rational::add(const float value){
		return *this + value;
	}
	Rational Rational::add(const Rational& rationalObj){
		return *this + rationalObj;
	}
	Rational Rational::subtract(const int value){
		return *this - value;
	}
	Rational Rational::subtract(const double value){
		return *this - value;
	}
	Rational Rational::subtract(const float value){
		return *this - value;
	}
	Rational Rational::subtract(const Rational& rationalObj){
		return *this - rationalObj;
	}
	Rational Rational::multiply(const int value){
		return *this * value;
	}
	Rational Rational::multiply(const double value){
		return *this * value;
	}
	Rational Rational::multiply(const float value){
		return *this * value;
	}
	Rational Rational::multiply(const Rational& rationalObj){
		try {
			return *this * rationalObj;
		}
		catch (DivideByZeroException &ex) {
			throw ex;
		}
	}
	Rational Rational::divide(const int value){
		try {
			return *this / value;
		}
		catch (DivideByZeroException &ex) {
			throw ex;
		}
	}
	Rational Rational::divide(const double value){
		try {
			return *this / value;
		}
		catch (DivideByZeroException &ex) {
			throw ex;
		}
	}
	Rational Rational::divide(const float value){
		try {
			return *this / value;
		}
		catch (DivideByZeroException &ex) {
			throw ex;
		}
	}
	Rational Rational::divide(const Rational& rationalObj){
		try {
			return *this / rationalObj;
		}
		catch (DivideByZeroException &ex) {
			throw ex;
		}
	}

	// raise this rational to an integral power
	Rational Rational::pow(const int value){
		if (value < 0) {
			// get the positive power of the fraction
			Rational posExp = pow(std::abs(value));
			return posExp.inv();  // return 1 / posExp
		}

		// make copy
		Rational tmp(*this);

		// result is 1
		if (value == 0) {
			return 1;
		}

		// raise to power
		Fraction rationalFraction = tmp;

		// compute new values -- since they can yield non-integer results, construct a new Rational from these values
		double newNumerator = std::pow(rationalFraction.getNumerator(), value);
		double newDenominator = std::pow(rationalFraction.getDenominator(), value);

		// construct new rational from numerator over denominator
		Rational rationalNum(newNumerator);  // converts from double
		Rational rationalDenom(newDenominator);  // converts from double

		if (rationalDenom == 0) {
			throw DivideByZeroException(__FILE__, __LINE__);
		}
		tmp = rationalNum / rationalDenom;

		// return 
		return tmp;
	}

	// mutating operator overloads
	// addition
	Rational Rational::operator+=(const int value) {
		*this += (double)value;
		return *this;
	}

	Rational Rational::operator+=(const float value) {
		*this += (double)value;
		return *this;
	}

	Rational Rational::operator+=(const double value) {
		*this += Rational(value);
		return *this;
	}

	Rational Rational::operator+=(const Rational& rationalObj) {
		// get the rational fractions representing each rational
		Fraction fraction1 = *this;
		Fraction fraction2 = rationalObj;

		// add fractions
		fraction1 = fraction1 + fraction2;

		// reduce to lowest terms
		Fraction::toLowestTerms(fraction1);

		// set this rational fraction
		*this = fraction1;

		// return
		return *this;
	}

	// subtraction
	Rational Rational::operator-=(const int value) {
		*this -= (double)value;
		return *this;
	}

	Rational Rational::operator-=(const float value) {
		*this -= (double)value;
		return *this;
	}

	Rational Rational::operator-=(const double value) {
		*this -= Rational(value);
		return *this;
	}

	Rational Rational::operator-=(const Rational& rationalObj) {
		// make copy of the rational object
		Rational tmp = Rational(rationalObj);

		// negate
		tmp = tmp.negate();

		// add
		return *this += tmp;
	}

	// multiplication
	Rational Rational::operator*=(const int value) {
		*this *= (double)value;
		return *this;
	}

	Rational Rational::operator*=(const float value) {
		*this *= (double)value;
		return *this;
	}

	Rational Rational::operator*=(const double value) {
		*this *= Rational(value);
		return *this;
	}

	Rational Rational::operator*=(const Rational& rationalObj) {
		try {
			// get this rational's fraction
			Fraction fraction = *this;

			// multiply these fractions
			fraction = fraction * rationalObj;

			// reduce to lowest terms
			Fraction::toLowestTerms(fraction);

			// set this fraction
			*this = fraction;

			// return this object
			return *this;
		}
		catch (DivideByZeroException &ex) {
			throw ex;
		}
	}

	// division
	Rational Rational::operator/=(const int value) {
		try {
			*this /= (double)value;
			return *this;
		}
		catch (DivideByZeroException &ex) {
			throw ex;
		}
	}

	Rational Rational::operator/=(const float value) {
		try {
			*this /= (double)value;
			return *this;
		}
		catch (DivideByZeroException &ex) {
			throw ex;
		}
	}

	Rational Rational::operator/=(const double value) {
		try {
			*this /= Rational(value);
			return *this;
		}
		catch (DivideByZeroException &ex) {
			throw ex;
		}
	}

	Rational Rational::operator/=(const Rational& rationalObj) {
		Fraction fraction = *this;

		// divide this rational's fraction by the object fraction
		try {
			fraction = fraction / rationalObj;

			// reduce to lowest terms
			Fraction::toLowestTerms(fraction);
		}
		catch (DivideByZeroException &ex) {
			throw ex;
		}

		// set the rational fraction
		*this = fraction;

		// return this object
		return *this;
	}

	// unary arithmetic operations
	// return the negation of this rational object
	Rational Rational::negate() const {
		Fraction fraction = *this;
		// negate by multiplying numerator by -1
		return Rational(fraction.getNumerator() * -1, fraction.getDenominator());
	}
	// return the absolute value of this rational object
	Rational Rational::abs() const {
		Fraction fraction = *this;
		// return the abs value by taking the abs value of both num/denom
		return Rational(std::abs(fraction.getNumerator()), std::abs(fraction.getDenominator()));
	}

	// return the square of this rational object
	Rational Rational::square() const {
		Rational result(*this); // make copy

		// return the result of pow(2)
		result = result.pow(2);
		return result;
	}

	// return the inverse (reciprocal) of this rational object
	Rational Rational::inv() const {
		Fraction fraction = *this;

		// fraction's method to invert;
		fraction = fraction.inv();

		// reduce to lowest terms
		Fraction::toLowestTerms(fraction);

		// fraction is already inverted
		return Rational(fraction);
	}

	// logical operator overloads
	// Less-than operator, returns true if the supplied rational is less than this
	bool Rational::operator<(const Rational& rationalObj) const {
		// return whether <= but not equal (not ==)
		return *this <= rationalObj && *this != rationalObj;
	}
	// Less-than-or-equal operator, returns true if the supplied rational is less than or equal to this
	bool Rational::operator<=(const Rational& rationalObj) const {
		Fraction fraction1 = *this;
		Fraction fraction2 = rationalObj;

		// convert to common denominators
		Fraction::toCommonDenominator(fraction1, fraction2);

		// return whether fraction1 is less than or equal fraction2 ( fraction1 <= fraction2 )
		return fraction1.getNumerator() <= fraction2.getNumerator();
	}

	// Greater-than operator, returns true if the supplied rational is greater than this
	bool Rational::operator>(const Rational& rationalObj) const {
		// return whether >= but not equal (not ==)
		return *this >= rationalObj && *this != rationalObj;
	}
	// Greater-than-or-equal operator, returns true if the supplied rational is greater than or equal to this
	bool Rational::operator>=(const Rational& rationalObj) const {
		Fraction fraction1 = *this;
		Fraction fraction2 = rationalObj;

		// convert to common denominators
		Fraction::toCommonDenominator(fraction1, fraction2);

		// return whether fraction1 is greater than or equal to fraction2 ( fraction1 >= fraction2 )
		return fraction1.getNumerator() >= fraction2.getNumerator();
	}
	// equality operator -- returns true if this rationl is equal to the supplied rational
	bool Rational::operator==(const Rational& rationalObj) const {
		Fraction fraction1 = *this;
		Fraction fraction2 = rationalObj;

		// convert to common denominators
		Fraction::toCommonDenominator(fraction1, fraction2);

		// return whether fraction1 == fraction2
		return fraction1.getNumerator() == fraction2.getNumerator();
	}

	// not-equal operator, returns true if this rational is not equal to the supplied rational
	bool Rational::operator!=(const Rational& rationalObj) const {
		// return not ==
		return !(*this == rationalObj);
	}

	// logical operations -- implemented in terms of operator overloaded functions
	bool Rational::lessThan(const Rational& rationalObj) const {
		return *this < rationalObj;
	}
	bool Rational::lessThanEqual(const Rational& rationalObj) const {
		return *this <= rationalObj;
	}
	bool Rational::greaterThan(const Rational& rationalObj) const {
		return *this > rationalObj;
	}
	bool Rational::greaterThanEqual(const Rational& rationalObj) const {
		return *this >= rationalObj;
	}
	bool Rational::equal(const Rational& rationalObj) const {
		return *this == rationalObj;
	}

	// assignment operations
	// these operations are implemented in terms of their overloaded assignment variants
	void Rational::set(const int value) {
		*this = value;  // use overloaded assignment operator
	}
	void Rational::set(const int numerator, const int denominator) {
		*this = Rational(numerator, denominator); // use overloaded assignment operator
	}
	void Rational::set(const float value) {
		*this = value; // use overloaded assignment operator
	}
	void Rational::set(const double value) {
		*this = value; // use overloaded assignment operator
	}
	void Rational::set(const Fraction& fractionObj) {
		*this = fractionObj; // use overloaded assignment operator
	}
	void Rational::set(const Rational& rationalObj) {
		*this = rationalObj; // use overloaded assignment operator
	}

	// read/write operations
	void Rational::read(std::istream& is) {
		std::string line;
		std::getline(is, line);

		// regular expression matching a grouping of numbers, optionally containing a single /, where only one decimal point may occur
		std::regex rationalRegex("^([\\d\\-]*\\.?[\\d]+)(\\/([\\d\\-]*\\.?[\\d]+))?\\s*$");
		std::smatch matchResults; // object that will hold the match results

		// if the line matches, it's a valid rational
		if (std::regex_search(line, matchResults, rationalRegex)) {
			std::string numerator = matchResults[1];  // first capture group contains numerator/single number
			// third capture group contains denominator, if present
			std::string denominator = (matchResults[3] == "") ? (std::string)"1" : matchResults[3];  // make sure there was a denominator (assume 1 otherwise)
			double numValue = std::stod(numerator);
			double denValue = std::stod(denominator);
			Rational n(numValue);
			Rational d(denValue);

			// try to divide
			try {
				*this = n / d;
			}
			catch (DivideByZeroException &ex) {
				throw ex;
			}
			
		}
		else {
			throw InvalidFormatException(line, __FILE__, __LINE__);
		}		
	}

	// writes to output stream using specified format (default/not specified is fraction)
	void Rational::write(std::ostream& os, const RationalPrintType type) const {
		try {
			// determine format type
			switch (type) {
			case Rational::DECIMAL:
				os << toDouble(); // convert to double
				break;
			case Rational::FRACTION:
			default:
				Fraction tmp = *this;
				Fraction::toLowestTerms(tmp); // ensure in lowest terms
				os << tmp; // print out the fraction 
			}

			// clear default print flag
			Rational::defaultPrintType = Rational::FRACTION;
		}
		catch (DivideByZeroException &ex) {
			throw ex;
		}
	}

	// read/write operators
	// set print flag
	// this allows the user to use the << operator and specify the format
	// ex: std::cout << usedecimal << Rational(1,2); will output "0.5"
	std::ostream& usedecimal(std::ostream& os) {
		Rational::defaultPrintType = Rational::DECIMAL;
		return os;
	}

	// read from object and write to outstream
	std::ostream& operator<<(std::ostream& os, const Rational& rationalObj) {
		Rational tmp(rationalObj); // make copy
		try {
			tmp.write(os, Rational::defaultPrintType);  // call write (by default, uses fraction format specification)
			return os;
		}
		catch (DivideByZeroException &ex) {
			throw ex;
		}

	}

	// read from input stream and write into object
	std::istream& operator>>(std::istream &is, Rational& rationalObj) {
		try {
			rationalObj.read(is);
			return is;
		}
		catch (DivideByZeroException &ex) {
			throw ex;
		}
		catch (InvalidFormatException &ex) {
			throw ex;
		}
	}

	// to string implementation
	std::string Rational::toString() const {		
		std::ostringstream oss;
		write(oss);
		return oss.str();
	}

	// convert a double value to a Fraction
	// this will approximate the value given by the double to the fraction value
	// Ex: 2.785 will yield a fraction: 2785/1000 (which will reduce to lowest terms in Fraction form)
	Fraction Rational::doubleToFraction(const double value) {
		// convert the input to a string and use the string to determine the exact fraction
		std::ostringstream oss;
		double newValue = value;

		// stream value to string stream
		oss << newValue;

		// convert to std::string
		std::string numStr = oss.str();

		// string length
		int i = numStr.length();
		// power of ten counter
		int powOfTen = 0;

		// while string length remains, look for '.'
		// start at end of string (or smallest decimal position)
		while (i > 0) {
			if (numStr[i] == '.')
				break;
			powOfTen++; // increment power of 10
			i--; // move index backward
		}
		// increment the new value based on power of 10 counted
		for (int j = 1; j < powOfTen; j++) {
			newValue *= 10.0;
		}

		// return new fraction object with new calculated value as numerator, and 10^powOfTen as denominator
		return Fraction(static_cast<int>(newValue), static_cast<int>(std::pow(10, powOfTen - 1)));
	}
}



