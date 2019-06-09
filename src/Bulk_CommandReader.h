#ifndef BULK_BULK_COMMANDREADER_H
#define BULK_BULK_COMMANDREADER_H

#include "Bulk_Observer.h"

#include <iostream>

class CommandReader : public BaseBulkObservable {
public:
    const std::string EmptyLine = ""; //TODO: Make static
    const std::string DynamicBlockBegin = "{";
    const std::string DynamicBlockEnd = "}";

public:
    CommandReader() = delete;
    CommandReader(size_t N, std::istream& in = std::cin)
        :  m_max_block_size{N}, m_input{in} {}

    command_t ReadCommand() {
        command_t cmd;
        std::getline(m_input, cmd);
        return cmd;
    }

    commands_block_t ReadCommandsBlock() {
        commands_block_t block;
        for(auto i = 0u; i < m_max_block_size; ++i) {
            auto command = ReadCommand();
            if(command != EmptyLine)
                block.push_back(command);
            else
                break;
        }
        return block;
    }

private:
    size_t m_max_block_size = 0;
    std::istream& m_input;
};


#endif //BULK_BULK_COMMANDREADER_H
