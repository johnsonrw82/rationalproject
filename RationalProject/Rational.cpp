#include "Rational.h"
#include <string>
#include <sstream>
#include <algorithm>

namespace rational {

	Rational::RationalPrintType Rational::defaultPrintType = Rational::FRACTION;

	// constructors - use initializer lists to init all members
	Rational::Rational() {}

	// this constructor provides a default initialization for denominator, allowing it to be used
	// for init with a single numerator, or both
	Rational::Rational(const int numerator, const int denominator) : rationalFraction(numerator, denominator) {
		Fraction::toLowestTerms(rationalFraction);
	}
	// call the double version of this constructor
	Rational::Rational(const float floatVal) : Rational((double)floatVal) {}
	// init from a rational object
	Rational::Rational(const Rational& rationalObj) : rationalFraction(rationalObj.rationalFraction) {
		Fraction::toLowestTerms(rationalFraction);
	}

	// create a Rational from a Fraction
	Rational::Rational(const Fraction& fractionObj) : rationalFraction(fractionObj) {
		Fraction::toLowestTerms(rationalFraction);
	}

	// this constructor will use a double value to create a fraction object using a helper function
	Rational::Rational(const double doubleVal) : rationalFraction(doubleToFraction(doubleVal)) {
		Fraction::toLowestTerms(rationalFraction);
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

		std::swap(rationalFraction, tmp.rationalFraction);

		return *this;
	}
	Rational Rational::operator=(const Fraction& fractionObj) {
		// copy and swap
		Rational tmp(fractionObj);

		std::swap(rationalFraction, tmp.rationalFraction);

		return *this;
	}
	Rational Rational::operator=(const Rational& rationalObj) {
		// copy and swap
		Rational tmp(rationalObj);

		std::swap(rationalFraction, tmp.rationalFraction);

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
		tmp *= rationalObj;
		return tmp;
	}
	Rational Rational::operator/(const int value){
		Rational tmp(*this);
		tmp /= value;
		return tmp;
	}
	Rational Rational::operator/(const float value){
		Rational tmp(*this);
		tmp /= value;
		return tmp;
	}
	Rational Rational::operator/(const double value){
		Rational tmp(*this);
		tmp /= value;
		return tmp;
	}
	Rational Rational::operator/(const Rational& rationalObj){
		Rational tmp(*this);
		tmp /= rationalObj;
		return tmp;
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
		return *this * rationalObj;
	}
	Rational Rational::divide(const int value){
		return *this / value;
	}
	Rational Rational::divide(const double value){
		return *this / value;
	}
	Rational Rational::divide(const float value){
		return *this / value;
	}
	Rational Rational::divide(const Rational& rationalObj){
		return *this / rationalObj;
	}

	// raise this rational to an integral power
	Rational Rational::pow(const int value){
		if (value < 0) {
			// get the positive power of the fraction
			Rational posExp = pow(std::abs(value));
			return posExp.inv();  // return 1 / posExp
		}

		Rational tmp(*this);

		// result is 1
		if (value == 0) {
			return 1;
		}

		// raise to power
		Fraction rationalFraction = tmp.getRationalFraction();

		// compute new values -- since they can yield non-integer results, construct a new Rational from these values
		double newNumerator = std::pow(rationalFraction.getNumerator(), value);
		double newDenominator = std::pow(rationalFraction.getDenominator(), value);

		// construct new rational from numerator over denominator
		Rational rationalNum(newNumerator);  // converts from double
		Rational rationalDenom(newDenominator);  // converts from double
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
		Fraction fraction1 = getRationalFraction();
		Fraction fraction2 = rationalObj.getRationalFraction();

		// add fractions
		fraction1 = fraction1 + fraction2;

		// reduce to lowest terms
		Fraction::toLowestTerms(fraction1);

		// set this rational fraction
		setRationalFraction(fraction1);

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
		// get this rational's fraction
		Fraction fraction = getRationalFraction();

		// multiply these fractions
		fraction = fraction * rationalObj.getRationalFraction();

		// reduce to lowest terms
		Fraction::toLowestTerms(fraction);

		// set this fraction
		setRationalFraction(fraction);

		// return this object
		return *this;
	}

	// division
	Rational Rational::operator/=(const int value) {
		*this /= (double)value;
		return *this;
	}

	Rational Rational::operator/=(const float value) {
		*this /= (double)value;
		return *this;
	}

	Rational Rational::operator/=(const double value) {
		*this /= Rational(value);
		return *this;
	}

	Rational Rational::operator/=(const Rational& rationalObj) {
		Fraction fraction = getRationalFraction();

		// divide this rational's fraction by the object fraction
		fraction = fraction / rationalObj.getRationalFraction();

		// reduce to lowest terms
		Fraction::toLowestTerms(fraction);

		// set the rational fraction
		setRationalFraction(fraction);

		// return this object
		return *this;
	}

	// unary arithmetic operations
	// return the negation of this rational object
	Rational Rational::negate() const {
		Fraction fraction = getRationalFraction();
		// negate by multiplying numerator by -1
		return Rational(fraction.getNumerator() * -1, fraction.getDenominator());
	}
	// return the absolute value of this rational object
	Rational Rational::abs() const {
		Fraction fraction = getRationalFraction();
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
		Fraction fraction = getRationalFraction();

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
		Fraction fraction1 = getRationalFraction();
		Fraction fraction2 = rationalObj.getRationalFraction();

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
		Fraction fraction1 = getRationalFraction();
		Fraction fraction2 = rationalObj.getRationalFraction();

		// convert to common denominators
		Fraction::toCommonDenominator(fraction1, fraction2);

		// return whether fraction1 is greater than or equal to fraction2 ( fraction1 >= fraction2 )
		return fraction1.getNumerator() >= fraction2.getNumerator();
	}
	// equality operator -- returns true if this rationl is equal to the supplied rational
	bool Rational::operator==(const Rational& rationalObj) const {
		Fraction fraction1 = getRationalFraction();
		Fraction fraction2 = rationalObj.getRationalFraction();

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

	// retreival operations
	// get the numerator of this rational
	int Rational::getNumerator() const {
		// return the fraction's numerator
		return getRationalFraction().getNumerator();
	}
	// get the denominator of this rational
	int Rational::getDenominator() const {
		// return the fraction's denominator
		return getRationalFraction().getDenominator();
	}
	// retrive this rational as a double
	double Rational::toDouble() const {
		// return the double representation of the fraction object
		return getRationalFraction().toDouble();
	}

	// read/write operations
	void Rational::read(std::istream& is) {
		std::string line;
		std::getline(is, line);

		int indexOfSlash = line.find_last_of('/');
		// this is a rational fraction
		if (indexOfSlash > 0) {
			std::string numerator = line.substr(0, indexOfSlash);
			std::string denominator = line.substr(indexOfSlash + 1);

			// set using the obtained substrings
			set(std::stoi(numerator), std::stoi(denominator));
		}
		// assume it's numeric (would want to do more error checking here)
		else {
			// use double
			set(std::stod(line));
		}
	}

	// writes to output stream using specified format (default/not specified is fraction)
	void Rational::write(std::ostream& os, const RationalPrintType type) const {
		// determine format type
		switch (type) {
		case Rational::DECIMAL:
			os << toDouble(); // convert to double
			break;
		case Rational::FRACTION:
		default:
			Fraction tmp = getRationalFraction();
			Fraction::toLowestTerms(tmp); // ensure in lowest terms
			os << tmp; // print out the fraction 
		}

		// clear default print flag
		Rational::defaultPrintType = Rational::FRACTION;
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
		tmp.write(os, Rational::defaultPrintType);  // call write (by default, uses fraction format specification)
		return os;
	}

	// read from input stream and write into object
	std::istream& operator>>(std::istream &is, Rational& rationalObj) {
		rationalObj.read(is);

		return is;
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



