/**
 * File: Rational.h
 * Author: Ryan Johnson
 * Email: johnsonrw82@csu.fullerton.edu
 * 
 * This class provides an implementation of a Rational number
 * It is built on the basics of the Fraction class that was implemented earlier.
 * This class provides comparison, assignment capability, and arithmetic for all rational numbers, including float/double values.
 */

#ifndef RATIONAL_H
#define RATIONAL_H

// superclass header file
#include "Fraction.h"
#include <regex>

// namespace -- this class will define functions that may clash with std namespace (such as pow)
namespace rational {
	// this class is a fraction, but with more capability
	class Rational : public Fraction {
	public:
		// enum declaring print type
		enum RationalPrintType {
			DECIMAL, FRACTION
		};

		// Constructors
		// empty constructor
		Rational();
		// construct a Rational with a numerator and an optional denominator
		Rational(const int numerator, const int denominator = 1);
		// construct a rational from a float value
		Rational(const float floatVal);
		// construct a rational from a double value
		Rational(const double doubleVal);
		// construct a rational from a Fraction
		Rational(const Fraction& fractionObj);
		// copy constructor - from another Rational
		Rational(const Rational& rationalObj);

		// assignment operators
		// assign a numerator only
		Rational operator=(const int numerator);
		// assign another Rational
		Rational operator=(const Rational& rationalObj);
		// assign a Fraction
		Rational operator=(const Fraction& fractionObj);
		// assign a floating point value
		Rational operator=(const float value);
		// assign a double value
		Rational operator=(const double value);


		// binary arithmetic operations
		// add an int to this rational and return result - non mutating
		Rational add(const int value);
		// add a double to this rational and return result - non mutating
		Rational add(const double value);
		// add a float to this rational and return result - non mutating
		Rational add(const float value);
		// add another Rational to this rational and return result - non mutating
		Rational add(const Rational& rationalObj);
		// subtract an int from this rational and return result
		Rational subtract(const int value);
		// subtract a double from this rational and return result
		Rational subtract(const double value);
		// subtract a float from this rational and return result
		Rational subtract(const float value);
		// subtract another Rational from this rational and return result
		Rational subtract(const Rational& rationalObj);
		// multiply this rational by an int and return result
		Rational multiply(const int value);
		// multiply this rational by a double and return result
		Rational multiply(const double value);
		// multiply this rational by a float and return result
		Rational multiply(const float value);
		// multiply this rational by another rational and return result
		Rational multiply(const Rational& rationalObj);
		// divide this rational by an int and return result
		Rational divide(const int value);
		// divide this rational by a double and return result
		Rational divide(const double value);
		// divide this rational by a float and return result
		Rational divide(const float value);
		// divide this rational by another Rational and return result
		Rational divide(const Rational& rationalObj);
		// raise this rational to an integral power and return the result
		Rational pow(const int value);

		// operator overloads
		// add an int to this rational and return result - non mutating
		Rational operator+(const int value);
		// add a float to this rational and return result - non mutating
		Rational operator+(const float value);
		// add a double to this rational and return result - non mutating
		Rational operator+(const double value);
		// add another Rational to this rational and return result - non mutating
		Rational operator+(const Rational& rationalObj);
		// subtract an int from this rational and return result
		Rational operator-(const int value);
		// subtract a float from this rational and return result
		Rational operator-(const float value);
		// subtract a double from this rational and return result
		Rational operator-(const double value);
		// subtract another Rational from this rational and return result
		Rational operator-(const Rational& rationalObj);
		// multiply this rational by an int and return result
		Rational operator*(const int value);
		// multiply this rational by a float and return result
		Rational operator*(const float value);
		// multiply this rational by a double and return result
		Rational operator*(const double value);
		// multiply this rational by another rational and return result
		Rational operator*(const Rational& rationalObj);
		// divide this rational by an int and return result
		Rational operator/(const int value);
		// divide this rational by a float and return result
		Rational operator/(const float value);
		// divide this rational by a double and return result
		Rational operator/(const double value);
		// divide this rational by another Rational and return result
		Rational operator/(const Rational& rationalObj);

		// mutating overloads
		// modify this rational by adding the specified int
		Rational operator+=(const int value);
		// modify this rational by adding the specified float
		Rational operator+=(const float value);
		// modify this rational by adding the specified double
		Rational operator+=(const double value);
		// modify this rational by adding the specified Rational
		Rational operator+=(const Rational& rationalObj);
		// modify this rational by subtracting the specified int
		Rational operator-=(const int value);
		// modify this rational by subtracting the specified float
		Rational operator-=(const float value);
		// modify this rational by subtracting the specified double
		Rational operator-=(const double value);
		// modify this rational by subtracting the specified Rational
		Rational operator-=(const Rational& rationalObj);
		// modify this rational by muliplying by the specified int
		Rational operator*=(const int value);
		// modify this rational by muliplying by the specified float
		Rational operator*=(const float value);
		// modify this rational by muliplying by the specified double
		Rational operator*=(const double value);
		// modify this rational by muliplying by the specified Rational
		Rational operator*=(const Rational& rationalObj);
		// modify this rational by dividing by the specified int
		Rational operator/=(const int value);
		// modify this rational by muliplying by the specified float
		Rational operator/=(const float value);
		// modify this rational by muliplying by the specified double
		Rational operator/=(const double value);
		// modify this rational by muliplying by the specified Rational
		Rational operator/=(const Rational& rationalObj);

		// unary arithmetic operations
		// return the negation of this rational object
		Rational negate() const;
		// return the absolute value of this rational object
		Rational abs() const;
		// return the square of this rational object
		Rational square() const;
		// return the inverse (reciprocal) of this rational object
		Rational inv() const;

		// logical operations
		// return true if this rational is less than the supplied rational
		bool lessThan(const Rational& rationalObj) const;
		// return true if this rational is less than or equal to the supplied rational
		bool lessThanEqual(const Rational& rationalObj) const;
		// return true if this rational is greater than the supplied rational
		bool greaterThan(const Rational& rationalObj) const;
		// return true if this rational is greater than or equal to the supplied rational
		bool greaterThanEqual(const Rational& rationalObj) const;
		// return true if this rational is equal to the supplied rational
		bool equal(const Rational& rationalObj) const;

		// logical operator overloads
		// return true if this rational is less than the supplied rational
		bool operator<(const Rational& rationalObj) const;
		// return true if this rational is less than or equal to the supplied rational
		bool operator<=(const Rational& rationalObj) const;
		// return true if this rational is greater than the supplied rational
		bool operator>(const Rational& rationalObj) const;
		// return true if this rational is greater than or equal to the supplied rational
		bool operator>=(const Rational& rationalObj) const;
		// return true if this rational is equal to the supplied rational
		bool operator==(const Rational& rationalObj) const;
		// return true if this rational is not equal to the supplied rational
		bool operator!=(const Rational& rationalObj) const;

		// assignment operations
		// set the numerator of this rational to the int value
		void set(const int value);
		// set the numerator and denominator of this rational
		void set(const int numerator, const int denominator);
		// set this rational to the specified float
		void set(const float value);
		// set this rational to the specified double
		void set(const double value);
		// set this rational to the Fraction object
		void set(const Fraction& fractionObj);
		// set this Rational to the Rational object
		void set(const Rational& rationalObj);

		// retreival operations are provided by the superclass - Fraction
		// int getNumerator()
		// int getDenominator()
		// double toDouble()

		// read/write operations
		// read Rational object from the specified input stream
		void read(std::istream& is);
		// write the Rational object to the specified output stream, in the specified format (default is FRACTION form)
		void write(std::ostream& os, const RationalPrintType type = Rational::FRACTION) const;

		// read/write operators
		// set flag to use decimal format on << operations
		friend std::ostream& usedecimal(std::ostream& os);
		// i/o operators -- these are used to read/write from a stream using << and >>
		// write this Rational object to the specified output stream
		friend std::ostream& operator<<(std::ostream& os, const Rational& rationalObj);
		// read the Rational object from the specified input stream
		friend std::istream& operator>>(std::istream& is, Rational& rationalObj);

		// to-std::string function for this rational object
		std::string toString() const;

	private:
		static RationalPrintType defaultPrintType; // default variable for determining the method to print the rational

		// private function that converts a double to fraction (directly using the number of decimal digits defined)
		Fraction doubleToFraction(const double value);
	};
}

#endif