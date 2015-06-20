#ifndef ARRAY_INDEX_OUT_OF_BOUNDS_EXCEPTION_H
#define ARRAY_INDEX_OUT_OF_BOUNDS_EXCEPTION_H

#include <sstream>
#include "RationalException.h"

namespace rational {
	namespace exception {
		// definition of an exception for cases when the container is over/under indexed
		class ArrayIndexOutOfBoundsException : public RationalException {
		public:
			// define a constructor for ArrayIndexOutOfBounds
			ArrayIndexOutOfBoundsException(const int index, const std::string fileName, const int lineNum);

			// return the information from the exception, including the index
			virtual const char* what() const throw();

			// stream operator overload
			friend std::ostream& operator<<(std::ostream& os, const ArrayIndexOutOfBoundsException& ex);

			int getIndex() const;

		private:
			int index;
		};
	}
}
#endif
