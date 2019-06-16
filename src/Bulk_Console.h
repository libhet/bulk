#ifndef BULK_BULK_CONSOLE_H
#define BULK_BULK_CONSOLE_H

#include "Bulk_Observer.h"
#include "PrettyPrinter.h"
#include <iostream>
#include <iterator>

class Console : public IBulkObserver {
public:
    void process(const commands_block_t &commands, const size_t time) override {
        if(!commands.empty()) {
            std::cout << "bulk: ";
            print_collection(commands, ", ", std::cout);
            std::cout << std::endl;
        }
    }
};


#endif //BULK_BULK_CONSOLE_H
