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

			// return the information from the exception, including the index
			virtual const char* what() const throw();

			// stream operator overload
			friend std::ostream& operator<<(std::ostream& os, const InvalidArgumentException& ex);

		private:
			std::string reason;
			std::string argument;
		};
	}
}
#endif