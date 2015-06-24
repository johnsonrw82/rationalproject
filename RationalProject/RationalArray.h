/**
* File: RationalArray.h
* Author: Ryan Johnson
* Email: johnsonrw82@csu.fullerton.edu
*
* This header provides an interface for a RationalArray, a container of Rational number objects
* This class uses a fixed-size native array to provide storage for Rational objects
* The class provides basic container operations, and should eventually update to allow dynamic memory allocation and re-sizing
*/

#ifndef RATIONAL_ARRAY_H
#define RATIONAL_ARRAY_H

#include <exception>
#include <stdexcept>

#include "Rational.h"
#include "RationalException.h"
#include "ArrayIndexOutOfBoundsException.h"
#include "InvalidArgumentException.h"

#define INIT_CAPACITY 20

using namespace rational;

// class definition
class RationalArray {
public:
	// constructor/destructor
	RationalArray();
	// construct with an initial size
	RationalArray(int initialSize);
	// copy constructor
	RationalArray(const RationalArray& ra);
	// destructor
	virtual ~RationalArray();

	// assignment operator
	RationalArray& operator=(const RationalArray& ra);

	// equality operators
	bool operator==(const RationalArray& ra) const;
	bool operator!=(const RationalArray& ra) const;

	// retrieve an element
	Rational retrieve(int index) const;
	//Rational* retrieve(int index) const;

	// add an object
	void add(const Rational& rationalObj);
	// add by pointer
	void add(Rational* rationalPtr);

	// replace an object
	void replace(int index, const Rational& rationalObj);
	// replace by pointer
	void replace(int index, Rational* rationalPtr);

	// remove an object
	Rational remove(int index);
	// size of the container
	std::size_t size() const;
	// capacity of the container
	std::size_t capacity() const;

	// clear container
	void clear();

	// print the contents
	void printArray() const;

private:
	// underlying storage
	Rational** rationalArray;
	// item count
	unsigned int count;
	// max capacity
	unsigned int maxCapacity;

	// resize and copy the original array contents to a new, bigger array. return the new size
	std::size_t resizeAndCopy(Rational **& originalArray, std::size_t size);
	// init array resources
	void initArray(Rational**& arrayRef, std::size_t size);
	// free array resources
	void freeArray(Rational**& arrayRef);

	// handler used for when bad_alloc is thrown
	void badAllocHandler(const char* reason, Rational**& arrayRef);
};



#endif