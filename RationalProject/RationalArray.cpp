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
#include <iterator>

using namespace rational::exception;

// constructor
RationalArray::RationalArray() : RationalArray(INIT_CAPACITY) {}

// constructor with initial size
RationalArray::RationalArray(int initialSize) {
	if (initialSize <= 0) {
		std::stringstream ss;
		ss << initialSize;
		throw InvalidArgumentException("Initial capacity cannot be <= 0", ss.str(), __FILE__, __LINE__);
	}

	maxCapacity = initialSize; // initial capacity

	// initialize the array reference -- if this statement fails, the resources will be cleaned up in the badAllocHandler() function
	initArray(rationalArray, maxCapacity);

	count = 0;  // empty
}

// copy constructor
RationalArray::RationalArray(const RationalArray& ra) {
	count = ra.count;
	maxCapacity = ra.maxCapacity;
	initArray(rationalArray, maxCapacity);
	// copy
	for (unsigned int i = 0; i < maxCapacity; i++) {
		rationalArray[i] = ra.rationalArray[i];
	}
}

// destructor
RationalArray::~RationalArray() {
	// this will be called on a fully constructed object, guaranteed
	freeArray(rationalArray);
}

// assignment operator
RationalArray& RationalArray::operator=(const RationalArray& ra) {
	RationalArray tmp(ra); // make a copy

	std::swap(maxCapacity, tmp.maxCapacity);
	std::swap(count, tmp.count);
	std::swap(rationalArray, tmp.rationalArray);

	return *this;
}

// test for equality
bool RationalArray::operator==(const RationalArray& ra) const {
	bool isEqual = size() == ra.size() && capacity() == ra.capacity();
	if (isEqual) {
		// check each element
		for (unsigned int i = 0; i < size(); i++) {
			isEqual &= *rationalArray[i] == *ra.rationalArray[i];
			if (!isEqual) {
				break;
			}
		}
	}

	return isEqual;
}
// test for inequality
bool RationalArray::operator!=(const RationalArray& ra) const {
	return !(*this == ra);
}

// retrieve a Rational object from the container using the specified index
// throws an ArrayIndexOutOfBoundsException if the index exceeds the bounds of the underlying container
Rational RationalArray::retrieve(int index) const {
	if (index >= 0 && static_cast<unsigned int>(index) < size()) {
		return *rationalArray[index];
	}	
	else {
		throw ArrayIndexOutOfBoundsException(index, __FILE__, __LINE__);
	}
}

// add a Rational to the end of the container
// container will resize itself if necessary
void RationalArray::add(const Rational& rationalObj) {
	// if the array is too small, resize and copy
	if (size() >= maxCapacity) {
		maxCapacity = resizeAndCopy(rationalArray, size());  // resize and copy - assign result to new capacity
	}

	// add to the array
	*rationalArray[size()] = rationalObj;

	// increment count
	count++;
}

// add a Rational* to the container. no-op if rationalPtr is nullptr
void RationalArray::add(Rational* rationalPtr) {
	// add the contents of this pointer to the array
	if (rationalPtr != nullptr) {
		add(*rationalPtr);
	}
}

// replace the specified rational object at index, with rationalObj
void RationalArray::replace(int index, const Rational& rationalObj) {
	// prevent under/over indexing
	if (index >= 0 && static_cast<unsigned int>(index) < size()) {
		*rationalArray[index] = rationalObj;
	}
	else {
		throw ArrayIndexOutOfBoundsException(index, __FILE__, __LINE__);
	}
}

// replace rational at index with pointer-specified rational object
void RationalArray::replace(int index, Rational* rationalPtr) {
	if (rationalPtr != nullptr)
		replace(index, *rationalPtr);
}

// remove rational from index and return
Rational RationalArray::remove(int index) {
	if (index >= 0 && static_cast<unsigned int>(index) < size()) {
		Rational removeElement = *rationalArray[index];

		// shift all elements from index+1 down by 1
		for (unsigned int i = index + 1; i < size(); i++) {
			rationalArray[i - 1] = rationalArray[i];
		}

		// decrement index
		count--;

		return removeElement;
	}
	else {
		throw ArrayIndexOutOfBoundsException(index, __FILE__, __LINE__);		
	}
}

// reset the array to initial size
void RationalArray::clear() {
	// free resources
	freeArray(rationalArray);
	// initialize resources
	initArray(rationalArray, INIT_CAPACITY);

	// reset count
	count = 0;
	// max capacity
	maxCapacity = INIT_CAPACITY;
}

// print the contents of the array
void RationalArray::printArray() const {
	for (unsigned int i = 0; i < size(); i++) {
		std::cout << *(rationalArray[i]) << std::endl;
	}
}

// return the number of elements in the container
std::size_t RationalArray::size() const { 
	return count; 
}

// return the current capacity of the container
std::size_t RationalArray::capacity() const {
	return maxCapacity;
}

// private function that will resize the reference container to specified size and copy elements
std::size_t RationalArray::resizeAndCopy(Rational **&originalArray, std::size_t size) {
	unsigned int newSize = (unsigned int)(size * 1.5); // grow by 1.5
	if (newSize == size) {
		newSize++; // guarantee at least one element increase;
	}

	// create the new array
	Rational** newArray;
	initArray(newArray, newSize);

	// copy
	for (unsigned int i = 0; i < size; i++) {
		*newArray[i] = *originalArray[i];
	}

	// free old resources
	freeArray(originalArray);

	// copy reference
	originalArray = newArray;

	return newSize;
}

// function that initializes an array reference to a specified size
void RationalArray::initArray(Rational**& arrayRef, std::size_t size) {
	try {
		// allocate memory for pointer array
		arrayRef = new Rational*[size];
		// allocate memory for each element
		for (unsigned int i = 0; i < size; i++) {
			arrayRef[i] = new Rational();
		}
	}
	catch (std::bad_alloc &ex) {
		// call the resource handler for this class
		// pass in the reference being allocated and the reason why the exception was thrown
		badAllocHandler(ex.what(), arrayRef);
	}
}

// free the specified array reference
void RationalArray::freeArray(Rational**& arrayRef) {
	delete[] arrayRef;
}

// handler used if bad_alloc is thrown
// this will free all resources, print to std::cerr and terminate.
void RationalArray::badAllocHandler(const char* reason, Rational**& arrayRef) {
	// tell the user what happened
	std::cerr << "Unable to allocate memory.\nReason = " << reason << "\nFreeing resources and terminating program" << std::endl;
	// free resources
	freeArray(arrayRef);

	// terminate program
	std::terminate();
}
