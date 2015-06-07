#ifndef RATIONAL_ARRAY_H
#define RATIONAL_ARRAY_H

#include "Rational.h"

using namespace rational;

class RationalArray {
public:
	RationalArray();
	~RationalArray();

	Rational retrieve(int index) const;

	void add(const Rational& rationalObj);
	void add(Rational* rationalPtr);

	void replace(int index, const Rational& rationalObj);
	void replace(int index, Rational* rationalPtr);

	Rational remove(int index);
	std::size_t size() const;

	void clear();

	void printArray() const;

private:
	Rational rationalArray[20];
	int count;
};

#endif