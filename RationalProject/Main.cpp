#include "Rational.h"

using namespace rational;

int main() {
	Rational r(-10,30);
	std::cout << r << std::endl;
	//std::cout << usedecimal << r << std::endl;
	std::cout << r << std::endl;

	std::cout << r.toString() << std::endl;
	return 0;
}