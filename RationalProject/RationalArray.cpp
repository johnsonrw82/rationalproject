/**
* File: RationalArray.cpp
* Author: Ryan Johnson
* Email: johnsonrw82@csu.fullerton.edu
*
* This class provides an implementation of a RationalArray, a container of Rational number objects
* This class uses a fixed-size native array to provide storage for Rational objects
* The class provides basic container operations, and should eventually update to allow dynamic memory allocation and re-sizing
*/

#include "RationalArray.h"

RationalArray::RationalArray() {
	count = 0;  // empty
}

// destructor - when needed
RationalArray::~RationalArray() {

}

Rational RationalArray::retrieve(int index) const {
	if (index >= 0 && static_cast<unsigned int>(index) < size()) {
		return rationalArray[index];
	}	
	return 0;
}

void RationalArray::add(const Rational& rationalObj) {
	if ( count < MAX_SIZE ) {
		// add to the array
		rationalArray[count] = rationalObj;

		// increment count
		count++;
	}
	// don't allow over indexing, just do nothing for now
}

void RationalArray::add(Rational* rationalPtr) {
	// add using other add function
	if ( rationalPtr != nullptr )
		add(*rationalPtr);
}

void RationalArray::replace(int index, const Rational& rationalObj) {
	// prevent under/over indexing
	if (index >= 0 && static_cast<unsigned int>(index) < size()) {
		rationalArray[index] = rationalObj;
	}
}
void RationalArray::replace(int index, Rational* rationalPtr) {
	if (rationalPtr != nullptr)
		replace(index, *rationalPtr);
}

Rational RationalArray::remove(int index) {
	if (index >= 0 && static_cast<unsigned int>(index) < size()) {
		Rational removeElement = rationalArray[index];

		// shift all elements from index+1 down by 1
		for (int i = index + 1; static_cast<unsigned int>(i) < size(); i++) {
			rationalArray[i - 1] = rationalArray[i];
		}

		// decrement index
		count--;

		return removeElement;
	}
	return 0;
}

void RationalArray::clear() {
	for (int i = 0; static_cast<unsigned int>(i) < size(); i++) {
		rationalArray[i] = 0;
	}

	count = 0;
}

void RationalArray::printArray() const {
	for (int i = 0; static_cast<unsigned int>(i) < size(); i++) {
		std::cout << rationalArray[i] << std::endl;
	}
}

std::size_t RationalArray::size() const { 
	return count; 
}
