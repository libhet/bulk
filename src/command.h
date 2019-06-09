#ifndef BULK_COMMAND_H
#define BULK_COMMAND_H

#include "observer.h"
#include <string>
#include <list>
#include <iostream>

class CommandMessage : IObserverMessage {
public:
    using SharedPtr = std::shared_ptr<CommandMessage>;

    enum Message : size_t {
        UNDIFINED = 0,
        PRINT_COMMANDS,
        NEW_BLOCK,
    };

    CommandMessage(Message msg) : m_msg(msg) {}

    size_t getMessage() override {
        return m_msg;
    }

private:
    Message m_msg = UNDIFINED;
};

class CommandBlock : public IObserver {
public:
    void processMessage(IObserverMessage::SharedPtr msg) override {
        auto commandMessage = static_cast<CommandMessage>(*msg);

        switch (commandMessage.getMessage()) {
            case CommandMessage::NEW_BLOCK :
                return;
        }
    }

private:
    std::list<std::string> m_commands;
};

class CommandReader : public BaseObservable {
public:
    void ReadCommands(std::istream& in = std::cin) {

    }


    CommandMessage::SharedPtr CreateMessage(CommandMessage::Message msg) {
        return std::make_shared<CommandMessage>(msg);
    }

    void SendMessageToObservers(CommandMessage::Message msg) {
        for(auto & subscriber : m_subscribers) {
            subscriber->processMessage(CreateMessage(msg));
        }
    }

private:
    size_t m_max_bolck_size;
};


#endif //BULK_COMMAND_H
