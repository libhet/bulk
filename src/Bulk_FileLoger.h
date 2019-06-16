#ifndef BULK_BULK_FILELOGER_H
#define BULK_BULK_FILELOGER_H

#include "Bulk_Observer.h"
#include "PrettyPrinter.h"
#include <iostream>
#include <iterator>
#include <fstream>

class FileLoger : public IBulkObserver {
public:
    void process(const commands_block_t &commands, const size_t time) override {
        if(!commands.empty()) {
            std::ofstream outfile("bulk" + std::to_string(time) + ".log");
            print_collection(commands, ", ", outfile);
            outfile << std::endl;
        }
    }
};


#endif //BULK_BULK_FILELOGER_H
