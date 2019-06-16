#ifndef BULK_BULK_OBSERVER_H
#define BULK_BULK_OBSERVER_H

#include <string>
#include <list>

using command_t = std::string;
using commands_block_t = std::list<command_t>;

class IBulkObserver {
public:
    virtual void process(const commands_block_t& cmd, const size_t time) = 0;
};


class IBulkObservable {
public:
    virtual void subscribe(IBulkObserver* observer) = 0;
};


class BaseBulkObservable : public IBulkObservable {
protected:
    std::list<IBulkObserver*> m_subscribers;

    void notify(const commands_block_t& cmd, const size_t time);

public:
    void subscribe(IBulkObserver* observer) override;

    const std::list<IBulkObserver*>& subscribers() const;
};

#endif //BULK_BULK_OBSERVER_H
