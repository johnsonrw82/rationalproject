#ifndef DIVIDE_BY_ZERO_EXCEPTION_H
#define DIVIDE_BY_ZERO_EXCEPTION_H

#include "RationalException.h"

namespace rational {
	namespace exception {
		class DivideByZeroException : public RationalException {
		public:
			DivideByZeroException(std::string fileName, int lineNum);
			virtual const char* what() const throw();
			friend std::ostream& operator<<(std::ostream& os, const DivideByZeroException& ex);
		};
	}
}

#endif