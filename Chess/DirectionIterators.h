#pragma once
#include <iterator>

class DirectionalIterator {
public:
    class iterator : public std::iterator<
        std::input_iterator_tag,  
        int,                      
        int,                      
        const int*,               
        int
    > {
        int num = 0;
        int increment = 1;
    public:
        explicit iterator(int start, int _increment = 1) : num(start), increment(_increment) {}
        iterator& operator++() { num = num + increment; return *this; }
        iterator operator++(int) { iterator retval = *this; ++(*this); return retval; }
        bool operator==(iterator other) const { return num >= other.num; }
        bool operator!=(iterator other) const { return !(*this == other); }
        reference operator*() const { return num; }
    };

    virtual iterator begin() { return iterator(0); }
    iterator end() { return iterator(8); }
};

class DiagonalIterator : public DirectionalIterator {
public:
    iterator begin() { return iterator(1, 2); }
};

class LevelIterator : public DirectionalIterator {
public:
    iterator begin() { return iterator(0, 2); }
};