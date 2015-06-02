#ifndef RATIONAL_H
#define RATIONAL_H

#include "Fraction.h"

// namespace -- this class will define functions that may clash with std namespace (such as pow)
namespace rational {
	class Rational {
	public:
		// enum declaring print type
		enum RationalPrintType {
			DECIMAL, FRACTION
		};

		// Constructors
		Rational();
		Rational(const int numerator, const int denominator = 1);
		Rational(const float floatVal);
		Rational(const double doubleVal);
		Rational(const Fraction& fractionObj);
		Rational(const Rational& rationalObj);

		// assignment operators
		Rational operator=(const int numerator);
		Rational operator=(const Rational& rationalObj);
		Rational operator=(const Fraction& fractionObj);
		Rational operator=(const float value);
		Rational operator=(const double value);


		// binary arithmetic operations
		Rational add(const int value);
		Rational add(const double value);
		Rational add(const float value);
		Rational add(const Rational& rationalObj);
		Rational subtract(const int value);
		Rational subtract(const double value);
		Rational subtract(const float value);
		Rational subtract(const Rational& rationalObj);
		Rational multiply(const int value);
		Rational multiply(const double value);
		Rational multiply(const float value);
		Rational multiply(const Rational& rationalObj);
		Rational divide(const int value);
		Rational divide(const double value);
		Rational divide(const float value);
		Rational divide(const Rational& rationalObj);
		Rational pow(const int value);

		// operator overloads
		Rational operator+(const int value);
		Rational operator+(const float value);
		Rational operator+(const double value);
		Rational operator+(const Rational& rationalObj);
		Rational operator-(const int value);
		Rational operator-(const float value);
		Rational operator-(const double value);
		Rational operator-(const Rational& rationalObj);
		Rational operator*(const int value);
		Rational operator*(const float value);
		Rational operator*(const double value);
		Rational operator*(const Rational& rationalObj);
		Rational operator/(const int value);
		Rational operator/(const float value);
		Rational operator/(const double value);
		Rational operator/(const Rational& rationalObj);

		// mutating overloads
		Rational operator+=(const int value);
		Rational operator+=(const float value);
		Rational operator+=(const double value);
		Rational operator+=(const Rational& rationalObj);
		Rational operator-=(const int value);
		Rational operator-=(const float value);
		Rational operator-=(const double value);
		Rational operator-=(const Rational& rationalObj);
		Rational operator*=(const int value);
		Rational operator*=(const float value);
		Rational operator*=(const double value);
		Rational operator*=(const Rational& rationalObj);
		Rational operator/=(const int value);
		Rational operator/=(const float value);
		Rational operator/=(const double value);
		Rational operator/=(const Rational& rationalObj);

		// unary arithmetic operations
		Rational negate() const;
		Rational abs() const;
		Rational square() const;
		Rational inv() const;

		// logical operations
		bool lessThan(const Rational& rationalObj) const;
		bool lessThanEqual(const Rational& rationalObj) const;
		bool greaterThan(const Rational& rationalObj) const;
		bool greaterThanEqual(const Rational& rationalObj) const;
		bool equal(const Rational& rationalObj) const;

		// logical operator overloads
		bool operator<(const Rational& rationalObj) const;
		bool operator<=(const Rational& rationalObj) const;
		bool operator>(const Rational& rationalObj) const;
		bool operator>=(const Rational& rationalObj) const;
		bool operator==(const Rational& rationalObj) const;
		bool operator!=(const Rational& rationalObj) const;

		// assignment operations
		void set(const int value);
		void set(const int numerator, const int denominator);
		void set(const float value);
		void set(const double value);
		void set(const Fraction& fractionObj);
		void set(const Rational& rationalObj);

		// retreival operations
		int getNumerator() const;
		int getDenominator() const;
		double toDouble() const;

		// read/write operations
		void read(std::istream& is);
		void write(std::ostream& os, const RationalPrintType type = Rational::FRACTION);

		// read/write operators
		// set flag to use decimal format
		friend std::ostream& usedecimal(std::ostream& os);
		// i/o operators -- these are used to read/write from a stream using << and >>
		friend std::ostream& operator<<(std::ostream& os, const Rational& rationalObj);
		friend std::istream& operator>>(std::istream& is, Rational& rationalObj);

	private:
		Fraction rationalFraction; // this is the fraction that will be used to represent the rational objects
		static RationalPrintType defaultPrintType; // default variable for determining the method to print the rational

		// private function that converts a double to fraction (directly using the number of decimal digits defined)
		Fraction doubleToFraction(const double value);

		// private getter for fraction object
		inline Fraction getRationalFraction() const { return rationalFraction; }
		// private setter for fraction object
		inline void setRationalFraction(const Fraction& fraction) { rationalFraction = fraction; }
	};
}

#endif