#ifndef INC_07_BULK_BULK_H
#define INC_07_BULK_BULK_H

#include <iostream>
#include <string>
#include <list>

class Bulk {
private:
    std::list<std::string> mBlockOfCommands;

    void addCommand(const std::string& cmd) {
        if(!cmd.empty())
            mBlockOfCommands.push_back(cmd);
    }

public:
    void readCommands(std::istream& in = std::cin) {
        while(in) {
            std::string command;
            std::getline(in, command);
//            if(command.empty())
//                executeCommads();
//            else
//                addCommand(command);
        }
    }

    const std::list<std::string> commands() const {
        return mBlockOfCommands;
    }
};

#endif //INC_07_BULK_BULK_H
