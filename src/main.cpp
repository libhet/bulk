#include <iostream>
#include <memory>
#include <cstdlib>
#include <errno.h>
#include <langinfo.h>

#include "Bulk_CommandReader.h"
#include "Bulk_Console.h"
#include "Bulk_FileLoger.h"

int main(int argc, char** argv) {

    if(argc != 2) {
        std::cout << "Usage: bulk N \nWhere N is size of block.";
        return 0;
    }
    else {
        int  base = 10;
        char *end;
        int  N;

        N = strtoll(argv[1], &end, base);

        if(N <= 0) {
            std::cout << argv[1] << " isn't a positive number." << std::endl;
        } else if(errno == ERANGE) {
            std::cout << "Range error!" << std::endl;
        } else {
            auto commandReader = std::make_unique<CommandReader>(N, std::cin);
            auto fileLoger     = FileLoger();
            auto console       = Console();

            commandReader->subscribe(&console);
            commandReader->subscribe(&fileLoger);

            commandReader->Process();
        }
    }
}