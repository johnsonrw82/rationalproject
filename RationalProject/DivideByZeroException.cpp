#include "DivideByZeroException.h"

namespace rational {
	namespace exception {
		DivideByZeroException::DivideByZeroException(std::string fileName, int lineNum) : RationalException("Division by zero exception", fileName, lineNum) {}

		const char* DivideByZeroException::what() const throw() {
			return RationalException::what();
		}

		std::ostream& operator<<(std::ostream& os, const DivideByZeroException& ex) {
			os << ex.what();
			return os;
		}
	}
}