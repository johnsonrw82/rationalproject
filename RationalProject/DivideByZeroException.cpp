/**
* File: DivideByZeroException.cpp
* Author: Ryan Johnson
* Email: johnsonrw82@csu.fullerton.edu
*
* This class provides an implementation of an exception type used for indicating when a divide by zero arithmetic operation occurs
*/

#include "DivideByZeroException.h"

namespace rational {
	namespace exception {
		// construct excepton and supertype
		DivideByZeroException::DivideByZeroException(std::string fileName, int lineNum) : RationalException("Division by zero exception", fileName, lineNum) {}

		// destructor
		DivideByZeroException::~DivideByZeroException() {}

		// what's the exception?
		const char* DivideByZeroException::what() const throw() {
			return RationalException::what();
		}

		// stream overload
		std::ostream& operator<<(std::ostream& os, const DivideByZeroException& ex) {
			os << ex.what();
			return os;
		}
	}
}