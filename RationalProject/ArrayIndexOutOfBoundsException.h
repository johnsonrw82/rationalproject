/**
* File: ArrayIndexOutOfBoundsException.h
* Author: Ryan Johnson
* Email: johnsonrw82@csu.fullerton.edu
*
* This class provides an implementation of an exception type that is used to indicate when an array index is out of bounds.
* It provides an index field that indicates the desired index.
*/

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
			// destructor
			virtual ~ArrayIndexOutOfBoundsException();

			// return the information from the exception, including the index
			virtual const char* what() const throw();

			// stream operator overload
			friend std::ostream& operator<<(std::ostream& os, const ArrayIndexOutOfBoundsException& ex);

			// get the index that was referenced
			int getIndex() const;

		private:
			int index;
		};
	}
}
#endif
