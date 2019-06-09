#ifndef BULK_BULK_OBSERVER_H
#define BULK_BULK_OBSERVER_H

#include <string>
#include <list>

using command_t = std::string;
using commands_block_t = std::list<command_t>;

class IBulkObserver {
public:
    virtual void process(const command_t& cmd) = 0;
};


class IBulkObservable {
public:
    virtual void subscribe(IBulkObserver* observer) = 0;
};


class BaseBulkObservable : public IBulkObservable {
protected:
    std::list<IBulkObserver*> m_subscribers;

    void notify(const command_t& cmd) {
        for(auto subscriber : m_subscribers)
            subscriber->process(cmd);
    }

public:
    void subscribe(IBulkObserver* observer) {
        m_subscribers.push_back(observer);
    }

    const std::list<IBulkObserver*>& subscribers() const {
        return m_subscribers;
    }
};

#endif //BULK_BULK_OBSERVER_H
