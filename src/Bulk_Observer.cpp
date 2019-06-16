#include "Bulk_Observer.h"

void BaseBulkObservable::notify(const commands_block_t &cmd, const size_t time) {
    for(auto subscriber : m_subscribers)
        subscriber->process(cmd, time);
}

void BaseBulkObservable::subscribe(IBulkObserver *observer) {
    m_subscribers.push_back(observer);
}

const std::list<IBulkObserver *> &BaseBulkObservable::subscribers() const {
    return m_subscribers;
}
