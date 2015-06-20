#include "InvalidArgumentException.h"

namespace rational {
	namespace exception {

		// define a constructor for InvalidArgumentException
		InvalidArgumentException::InvalidArgumentException(const std::string reason, const std::string argument, const std::string fileName, const int lineNum)
			: RationalException("Invalid argument exception", fileName, lineNum),
			reason(reason), argument(argument) {}

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