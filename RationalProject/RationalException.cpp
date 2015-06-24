/**
* File: RationalException.cpp
* Author: Ryan Johnson
* Email: johnsonrw82@csu.fullerton.edu
*
* This class provides an implementation of an exception type used to indicate there was an exception involved with a Rational object.
* This class inherits from std::exception, and also provides a file name and line number for reference.
*/

#include "RationalException.h"

namespace rational {
	namespace exception {
		// definition of a base class of exception for use with the Rational set of classes
		// this class derives from std::exception to provide a basis for the different exception types
		RationalException::RationalException(const char* msg, std::string fileName, int lineNum) : msg(msg), fileName(fileName), lineNum(lineNum) {}

		// copy constructor
		RationalException::RationalException(const RationalException& ex) : RationalException(ex.msg, ex.fileName, ex.lineNum) {}

		// destructor -- not needed in this implementation, but here to satisfy contract with std::exception
		RationalException::~RationalException() {}

		// overloaded equals operator
		RationalException& RationalException::operator=(const RationalException& ex) {
			RationalException copy(ex);
			std::swap(msg, copy.msg);
			std::swap(fileName, copy.fileName);
			std::swap(lineNum, copy.lineNum);

			return *this;
		}
		
		const char* RationalException::what() const throw() {
			std::ostringstream os;
			os << msg << " in: " << getFileName() << " @ line: " << getLineNum() << ".";

			// copy to a char array
			rsize_t size = os.str().length() + 1;
			char* returnVal;
			// try to allocate memory. Catch and terminate to avoid throwing an exception
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
		std::ostream& operator<<(std::ostream& os, const RationalException& ex) {
			os << ex.what();
			return os;
		}

		// get the filename of the source file where the exception was thrown
		std::string RationalException::getFileName() const {
			return fileName;
		}

		// get the line number of the source file where the exception was thrown
		int RationalException::getLineNum() const {
			return lineNum;
		}
	}
}
