/**
* File: InvalidFormatException.cpp
* Author: Ryan Johnson
* Email: johnsonrw82@csu.fullerton.edu
*
* This class provides an implementation of an exception type used for cases when an invalid format of data is encountered.
* The class provides a reason for why the format is invalid.
*/

#include "InvalidFormatException.h"

namespace rational {
	namespace exception {
		// construct an invalid format exception
		InvalidFormatException::InvalidFormatException(std::string reason, std::string fileName, int lineNum) :
			RationalException("Invalid format exception", fileName, lineNum), reason(reason) {}

		// destructor
		InvalidFormatException::~InvalidFormatException() {}

		// what caused the exception?
		const char* InvalidFormatException::what() const throw() {
			std::ostringstream os;
			os << RationalException::what() << "\nReason = " << reason;

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

		// stream overload
		std::ostream& operator<<(std::ostream& os, const InvalidFormatException& ex) {
			os << ex.what();
			return os;
		}
	}
}