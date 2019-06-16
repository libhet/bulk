#include <iostream>
#include <memory>

#include "Bulk_CommandReader.h"
#include "Bulk_Console.h"
#include "Bulk_FileLoger.h"

int main(int argc, char** argv) {

    if(argc != 2) {
        std::cout << "Usage: bulk N \nWhere N is size of the block.";
        return 0;
    }
    else {
        auto commandReader = std::make_unique<CommandReader>(std::atoi(argv[1]), std::cin);
        auto fileLoger     = FileLoger();
        auto console       = Console();

        commandReader->subscribe(&console);
        commandReader->subscribe(&fileLoger);

        commandReader->Process();
    }
}