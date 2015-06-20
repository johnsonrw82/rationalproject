#include "InvalidFormatException.h"

namespace rational {
	namespace exception {
		InvalidFormatException::InvalidFormatException(std::string reason, std::string fileName, int lineNum) :
			RationalException("Invalid format exception", fileName, lineNum), reason(reason) {}

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
		std::ostream& operator<<(std::ostream& os, const InvalidFormatException& ex) {
			os << ex.what();
			return os;
		}
	}
}