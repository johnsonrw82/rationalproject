/**
* File: DivideByZeroException.h
* Author: Ryan Johnson
* Email: johnsonrw82@csu.fullerton.edu
*
* This class provides an implementation of an exception type used for indicating when a divide by zero arithmetic operation occurs
*/

#ifndef DIVIDE_BY_ZERO_EXCEPTION_H
#define DIVIDE_BY_ZERO_EXCEPTION_H

#include "RationalException.h"

namespace rational {
	namespace exception {
		class DivideByZeroException : public RationalException {
		public:
			// constructor
			DivideByZeroException(std::string fileName, int lineNum);
			// destructor
			virtual ~DivideByZeroException();
			// what caused the exception
			virtual const char* what() const throw();
			// stream overload
			friend std::ostream& operator<<(std::ostream& os, const DivideByZeroException& ex);
		};
	}
}

#endif