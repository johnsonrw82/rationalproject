#ifndef INVALID_FORMAT_EXCEPTION_H
#define INVALID_FORMAT_EXCEPTION_H

#include "RationalException.h"

namespace rational {
	namespace exception {
		class InvalidFormatException : public RationalException {
		public:
			InvalidFormatException(std::string reason, std::string fileName, int lineNum);
			virtual const char* what() const throw();
			friend std::ostream& operator<<(std::ostream& os, const InvalidFormatException& ex);

		private:
			std::string reason;
		};
	}
}

#endif