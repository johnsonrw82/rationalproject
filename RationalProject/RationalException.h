/**
* File: RationalException.h
* Author: Ryan Johnson
* Email: johnsonrw82@csu.fullerton.edu
*
* This class provides an implementation of an exception type used to indicate there was an exception involved with a Rational object.
* This class inherits from std::exception, and also provides a file name and line number for reference.
*/

#ifndef RATIONAL_EXCEPTION_H
#define RATIONAL_EXCEPTION_H

#include <stdexcept>

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <cstdlib>
#include <cstring>

namespace rational {
	namespace exception {
		// definition of a base class of exception for use with the Rational set of classes
		// this class derives from std::exception to provide a basis for the different exception types
		class RationalException : public std::exception {
		public:
			// define a constructor for ArrayIndexOutOfBounds
			RationalException(const char* msg, std::string fileName, int lineNum);
			// copy constructor
			RationalException(const RationalException& ex);
			// destructor
			virtual ~RationalException();
			
			// assignment operator
			RationalException& operator=(const RationalException& ex);

			// what happened?
			virtual const char* what() const throw();

			// stream operator overload
			friend std::ostream& operator<<(std::ostream& os, const RationalException& ex);

			// get the filename of the source file where the exception was thrown
			std::string getFileName() const;

			// get the line number of the source file where the exception was thrown
			int getLineNum() const;

		private:
			// message
			const char* msg;
			// filename
			std::string fileName;
			// line number
			int lineNum;
		};
	}
}
#endif