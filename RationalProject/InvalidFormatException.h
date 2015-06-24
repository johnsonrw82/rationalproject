/**
* File: InvalidFormatException.h
* Author: Ryan Johnson
* Email: johnsonrw82@csu.fullerton.edu
*
* This class provides an implementation of an exception type used for cases when an invalid format of data is encountered.
* The class provides a reason for why the format is invalid.
*/

#ifndef INVALID_FORMAT_EXCEPTION_H
#define INVALID_FORMAT_EXCEPTION_H

#include "RationalException.h"

namespace rational {
	namespace exception {
		class InvalidFormatException : public RationalException {
		public:
			// constructor
			InvalidFormatException(std::string reason, std::string fileName, int lineNum);
			// destructor
			virtual ~InvalidFormatException();
			// what happened?
			virtual const char* what() const throw();
			// stream overload
			friend std::ostream& operator<<(std::ostream& os, const InvalidFormatException& ex);

		private:
			std::string reason; // the reason for the invalid format
		};
	}
}

#endif