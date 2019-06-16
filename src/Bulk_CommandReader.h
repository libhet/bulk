#ifndef BULK_BULK_COMMANDREADER_H
#define BULK_BULK_COMMANDREADER_H

#include "Bulk_Observer.h"

#include <iostream>
#include <chrono>

class CommandReader : public BaseBulkObservable {
public:
    const std::string      EndOfData          = ""; //TODO: Make static
    const std::string      DynamicBlockBegin  = "{";
    const std::string      DynamicBlockEnd    = "}";
    const commands_block_t EmptyCommandsBlock = commands_block_t{};

public:
    CommandReader() = delete;

    CommandReader(size_t N, std::istream &in = std::cin)
            : m_max_block_size{N}, m_input{in} {}

    command_t ReadCommand();

    commands_block_t ReadCommandsBlock();

    /**
     * @brief Process
     * The only method you need.
     * Reads commands from input in infinity loop.
     */
    void Process();

private:
    bool IsDynamic() const;

    commands_block_t ReadStaticBlock();

    commands_block_t ReadDynamicBlock();

    std::chrono::system_clock::time_point GetTime();

    size_t GetTimeMilliseconds();

    void StartReadingBlock();

    bool IsFirstCommand() const;

    void GetFirstCommandTime();

private:
    size_t m_max_block_size = 0;
    std::istream &m_input;
    bool m_dynamic_size = false;

    bool m_first_command = false;
    std::chrono::system_clock::time_point m_time;
};


#endif //BULK_BULK_COMMANDREADER_H
