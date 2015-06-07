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

#include "Rational.h"

#define MAX_SIZE 20

using namespace rational;

// class definition
class RationalArray {
public:
	// constructor/destructor
	RationalArray();
	// construct with an initial size
	RationalArray(int initialSize);
	~RationalArray();

	// retrieve an element
	Rational retrieve(int index) const;

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

	// clear container
	void clear();

	// print the contents
	void printArray() const;

private:
	// underlying storage
	Rational rationalArray[MAX_SIZE];
	// item count
	int count;
};

#endif