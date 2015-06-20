#include "ArrayIndexOutOfBoundsException.h"

namespace rational {
	namespace exception {
		// define a constructor for ArrayIndexOutOfBounds
		ArrayIndexOutOfBoundsException::ArrayIndexOutOfBoundsException(const int index, const std::string fileName, const int lineNum)
			: RationalException("Array index out of bounds", fileName, lineNum),
			index(index) {}

		// return the information from the exception, including the index
		const char* ArrayIndexOutOfBoundsException::what() const throw() {
			std::ostringstream os;
			os << RationalException::what() << "\nIndex = " << index;

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
		std::ostream& operator<<(std::ostream& os, const ArrayIndexOutOfBoundsException& ex) {
			os << ex.what();
			return os;
		}

		int ArrayIndexOutOfBoundsException::getIndex() const {
			return index;
		}
	}
}