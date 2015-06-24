/**
* File: InvalidArgumentException.cpp
* Author: Ryan Johnson
* Email: johnsonrw82@csu.fullerton.edu
*
* This class provides an implementation of an exception type used for cases when an invalid argument has been supplied to a function or constructor
* This class does not inherit from type std::invalid_argument because it causes ambiguity errors with std::exception, which RationalException is derived from.
* That class provides more functionality than std::exception, so it is preferred over the existing exception type.
*/

#include "InvalidArgumentException.h"

namespace rational {
	namespace exception {

		// define a constructor for InvalidArgumentException
		InvalidArgumentException::InvalidArgumentException(const std::string reason, const std::string argument, const std::string fileName, const int lineNum)
			: RationalException("Invalid argument exception", fileName, lineNum),
			reason(reason), argument(argument) {}

		// destructor
		InvalidArgumentException::~InvalidArgumentException() {}

		// return the information from the exception, including the index
		const char* InvalidArgumentException::what() const throw() {
			std::ostringstream os;
			os << RationalException::what() << "\nReason = " << reason << "\nArgument = " << argument;

			// copy to a char array
			rsize_t size = os.str().length() + 1;
			char* returnVal;
			try {
				returnVal = new char[size];
			}
			catch (std::bad_alloc &ex) {
				std::cerr << ex.what() << std::endl;
				std::terminate();
			}

			// safe copy
			strcpy_s(returnVal, size, os.str().c_str());

			// return char array -- wont work without an explicit copy
			return returnVal;
		}

		// stream operator overload
		std::ostream& operator<<(std::ostream& os, const InvalidArgumentException& ex) {
			os << ex.what();
			return os;
		}
	}
}