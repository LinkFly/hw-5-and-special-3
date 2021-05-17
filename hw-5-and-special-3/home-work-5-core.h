#pragma once

#include <iostream>
#include <cstdint>
#include <algorithm>

using std::swap;

template<typename T>
void output_array(std::wostream& out, T ar[], size_t arSize) {
	out << "{";
	if (arSize > 0) 
		out << ar[0];
	for (size_t i = 1; i < arSize; ++i) {
		out << ", " << ar[i];
	}
	out << "}";
}

template<typename T>
void xor_array(T ar[], size_t arSize) {
	for(size_t i = 0; i < arSize; ++i)
		ar[i] ^= 1;
}

void fill_array_step3(int ar[], size_t arSize) {
	for (size_t i = 0, fill = 1; i < arSize; ++i, fill += 3)
		ar[i] = fill;
}

template<typename T>
void rotate_one_array(T ar[], size_t arSize) {
	size_t i = 1;
	do {
		swap(ar[0], ar[i]);
		++i;
	} while (i < arSize);
	
}

template<typename T>
void rotate_array(T ar[], size_t arSize, int64_t nRotate) {
	if (arSize <= 1) return;
	nRotate %= arSize;
	if (nRotate < 0) nRotate = arSize + nRotate;
	for(auto j = nRotate; j > 0; --j)
		rotate_one_array(ar, arSize);
}

template<typename T>
bool is_balance_array(T ar[], size_t arSize) {
	if (arSize < 2) return false;
	struct {
		bool operator()(T ar[], size_t arSize, size_t mid) {
			int left = 0, right = 0;
			for(size_t i = 0; i < mid; ++i)
				left += ar[i];
			for(size_t j = mid; j < arSize; ++j)
				right += ar[j];
			return left == right;
		}
	} checkMid;
	for(size_t i = 1; i < arSize; ++i)
		if (checkMid(ar, arSize, i))
			return true;
	return false;
}