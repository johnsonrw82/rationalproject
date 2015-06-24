/**
* File: InvalidArgumentException.h
* Author: Ryan Johnson
* Email: johnsonrw82@csu.fullerton.edu
*
* This class provides an implementation of an exception type used for cases when an invalid argument has been supplied to a function or constructor
* This class does not inherit from type std::invalid_argument because it causes ambiguity errors with std::exception, which RationalException is derived from.
* That class provides more functionality than std::exception, so it is preferred over the existing exception type.
*/

#ifndef INVALID_ARGUMENT_EXCEPTION_H
#define INVALID_ARGUMENT_EXCEPTION_H

#include <string>
#include <sstream>

#include "RationalException.h"

namespace rational {
	namespace exception {

		// class inheriting from RationalException
		// not inherited from or using std::invalid_argument because additional information provided in RationalException is needed
		// multiple inheritance not used to avoid ambiguity with superclass definitions (exception vs invalid_argument)
		class InvalidArgumentException : public RationalException {
		public:
			// define a constructor for InvalidArgumentException
			InvalidArgumentException(const std::string reason, const std::string argument, const std::string fileName, const int lineNum);
			// destructor
			virtual ~InvalidArgumentException();

			// return the information from the exception, including the index
			virtual const char* what() const throw();

			// stream operator overload
			friend std::ostream& operator<<(std::ostream& os, const InvalidArgumentException& ex);

		private:
			std::string reason;  // the reason the argument is invalid
			std::string argument;  // the argument supplied
		};
	}
}
#endif