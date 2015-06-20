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
			RationalException(const RationalException& ex);
			virtual ~RationalException();
			
			RationalException& operator=(const RationalException& ex);

			virtual const char* what() const throw();

			// stream operator overload
			friend std::ostream& operator<<(std::ostream& os, const RationalException& ex);

			// get the filename of the source file where the exception was thrown
			std::string getFileName() const;

			// get the line number of the source file where the exception was thrown
			int getLineNum() const;

		private:
			const char* msg;
			std::string fileName;
			int lineNum;
		};
	}
}
#endif