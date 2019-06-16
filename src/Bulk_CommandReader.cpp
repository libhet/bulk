#include "Bulk_CommandReader.h"

//const std::string CommandReader::EmptyLine = "";

command_t CommandReader::ReadCommand() {
    command_t cmd;
    if(IsFirstCommand()) { GetFirstCommandTime(); }
    std::getline(m_input, cmd);
    return cmd;
}

commands_block_t CommandReader::ReadCommandsBlock() {
    if(IsDynamic()) {
        m_dynamic_size = false;
        return ReadDynamicBlock();
    } else {
        return ReadStaticBlock();
    }
}

void CommandReader::Process() {
    while(m_input) {
        auto commands = ReadCommandsBlock();
        auto time = GetTimeMilliseconds();
        notify(commands, time);
    }
}

commands_block_t CommandReader::ReadStaticBlock() {
    StartReadingBlock();
    commands_block_t block;
    auto cmdCounter = 0u;

    while (cmdCounter < m_max_block_size) {
        auto command = ReadCommand();

        if (command == DynamicBlockBegin) {
            m_dynamic_size = true;
            break;
        } else if (command == EndOfData) {
            break;
        } else {
            block.push_back(command);
            ++cmdCounter;
        }
    }

    return block;
}

commands_block_t CommandReader::ReadDynamicBlock() {
    StartReadingBlock();
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
        } else if (command == EndOfData) {
            return EmptyCommandsBlock;
        } else {
            block.push_back(command);
        }
    }

    return block;
}

std::chrono::system_clock::time_point CommandReader::GetTime() {
    return std::chrono::system_clock::now();
}

size_t CommandReader::GetTimeMilliseconds() {
    return std::chrono::time_point_cast<std::chrono::milliseconds>(m_time).time_since_epoch().count();
}

void CommandReader::GetFirstCommandTime() {
    m_time = GetTime();
    m_first_command = false;
}

bool CommandReader::IsFirstCommand() const {
    return m_first_command;
}

void CommandReader::StartReadingBlock() {
    m_first_command = true;
}

bool CommandReader::IsDynamic() const {
    return m_dynamic_size;
}
