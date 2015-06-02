#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>


/*
 * class definition for Fraction
 *
 * Fractions can be initialized in 3 ways:
 *   Default - no args				Fraction()
 *   To a numerator/denominator		Fraction(int, int)
 *   From another fraction			Fraction(Fraction&)
 * Fractions also support the = operator to:
 *   An integer			Fraction f1 = 12;
 *   Another Fraction	Fraction f2 = f1;
 * Fractions can be retreived as a double (num / denom)
 * Fractions can be printed to the screen in lowest terms
 */
class Fraction {
public:	
	// default constructor
	Fraction();
	// numerator/denominator constructor
	Fraction(const int numerator, const int denominator = 1);
	// copy constructor
	Fraction(const Fraction& fraction);

	// set numerator
	void setNumerator(const int numerator);
	// set denominator
	void setDenominator(const int denominator);
	// get numerator
	int getNumerator() const;
	// get denominator
	int getDenominator() const;

	// operator overloads
	Fraction operator+(const Fraction& fraction);
	Fraction operator-(const Fraction& fraction);
	Fraction operator*(const Fraction& fraction);
	Fraction operator/(const Fraction& fraction);

	Fraction& operator=(const int integerValue);
	Fraction& operator=(Fraction fraction);
	// overload for <<, declared as friend
	friend std::ostream& operator<<(std::ostream& os, const Fraction& fraction);

	// get double representation
	double toDouble() const;
	// print in lowest terms
	void printFractionInLowestTerms();
	// function that will modify the fraction to remain in lowest terms
	// this is a static function that operates on a reference
	static void toLowestTerms(Fraction& fractionObj);
	// this function will modify each fraction argument such that the denominators are common
	static void toCommonDenominator(Fraction& fraction1, Fraction& fraction2);

	// inverse of fraction
	Fraction inv() const; 

private:
	int numerator;
	int denominator;


	// get the gcd of the numerator/denominator
	static int getGcd(const int dividend, const int remainder );
	// get least common multiple of two numbers
	static int getLcm(const int num1, const int num2);
	// get fraction in lowest terms
	std::string toLowestTermsString();
};

// this function is a helper function that will convert a number to a std::string
// this function is needed because some compilers in the Cygwin/MinGW toolset have
// a bug that results in std::to_string producing an error that says:
// "to_string is not a member of std", even when using the C++11 standard
template<typename T>
inline std::string numToString(T num) {
	std::ostringstream ss;
	ss << num;
	return ss.str();
}
