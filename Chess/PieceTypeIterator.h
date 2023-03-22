#pragma once
#include <iterator>
#include "PieceTypes.h"

class PieceTypeIterator {
public:
	class iterator : public std::iterator<
		std::input_iterator_tag,    // iterator_category
		PieceType,                  // value_type
		PieceType,                  // difference_type
		const PieceType*,           // pointer
		PieceType					// reference
	> {
		int count;
	public:
		explicit iterator(int len) : count(len) {};
		iterator& operator++() { count++; return *this; }
		iterator operator++(int) { iterator retval = *this; ++(*this); return retval; }
		bool operator==(iterator other) const { return count == other.count; }
		bool operator!=(iterator other) const { return !(*this == other); }
		reference operator*() const { return static_cast<PieceType>(count); }
	};

	iterator begin() { return iterator(0); }
	iterator end() { return iterator(6); }
};