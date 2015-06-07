#include "Rational.h"
#include "RationalArray.h"

using namespace rational;

int main() {
	RationalArray ra;
	Rational r(1, 2);
	Rational r2(2, 3);
	Rational r3(3, 4);

	ra.add(r);
	ra.add(r3);
	ra.replace(1,r2);

	ra.printArray();

	std::cout << "The rationals" << std::endl;
	std::cout << r << std::endl;
	std::cout << r2 << std::endl;
	std::cout << r3 << std::endl;
	return 0;
}