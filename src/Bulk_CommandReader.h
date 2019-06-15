#ifndef BULK_BULK_COMMANDREADER_H
#define BULK_BULK_COMMANDREADER_H

#include "Bulk_Observer.h"

#include <iostream>

class CommandReader : public BaseBulkObservable {
public:
    const std::string EndOfData= ""; //TODO: Make static
    const std::string DynamicBlockBegin = "{";
    const std::string DynamicBlockEnd = "}";
    const commands_block_t EmptyCommandsBlock = commands_block_t{};

public:
    CommandReader() = delete;
    CommandReader(size_t N, std::istream& in = std::cin)
        :  m_max_block_size{N}, m_input{in} {}

    command_t ReadCommand() {
        command_t cmd;
        std::getline(m_input, cmd);
        return cmd;
    }

    commands_block_t ReadStaticBlock() {
        commands_block_t block;
        auto cmdCounter = 0u;

        while (cmdCounter < m_max_block_size) {
            auto command = ReadCommand();

            if (command == DynamicBlockBegin) {
                m_dynamic_size = true;
                break;
            } else if (command != EndOfData) {
                block.push_back(command);
                ++cmdCounter;
            } else if (command == EndOfData) {
                break;
            }
        }

        return block;
    }

    commands_block_t ReadDynamicBlock() {
        commands_block_t block;
        bool innerBlock = false;
        while(true) {
            auto command = ReadCommand();

            if (command == DynamicBlockBegin) {
                innerBlock = true;
            } else if (command == DynamicBlockEnd) {
                if(innerBlock) {
                    innerBlock = false;
                } else {
                    break;
                }
            } else if (command != EndOfData) {
                block.push_back(command);
            } else if (command == EndOfData) {
                return EmptyCommandsBlock;
            }
        }
        return block;
    }

    commands_block_t ReadCommandsBlock() {
        if(IsDynamic()) {
            m_dynamic_size = false;
            return ReadDynamicBlock();
        } else {
            return ReadStaticBlock();
        }
    }

private:
    bool IsDynamic() const {
        return m_dynamic_size;
    }

private:
    size_t m_max_block_size = 0;
    std::istream& m_input;
    bool m_dynamic_size = false;
};


#endif //BULK_BULK_COMMANDREADER_H
