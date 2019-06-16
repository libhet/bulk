#ifndef BULK_PRETTYPRINTER_H
#define BULK_PRETTYPRINTER_H

#include <iostream>

template<typename Collection>
void print_collection(Collection collection, std::string delim, std::ostream& out = std::cout) {
    auto begin = std::begin(collection);
    auto end = std::end(collection);
    auto current = begin;
    auto next = std::next(begin);

    while(current != end) {
        out << *current;
        if(next != end) {
            out << delim;
        }

        current = std::next(current);
        next    = std::next(next);
    }
}

#endif //BULK_PRETTYPRINTER_H
