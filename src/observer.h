#ifndef BULK_OBSERVER_H
#define BULK_OBSERVER_H

#include <list>
#include <memory>

class IObserverMessage {
public:
    using SharedPtr = std::shared_ptr<IObserverMessage>;

    virtual size_t getMessage() = 0;
};

class IObserver {
public:
    virtual void processMessage(IObserverMessage::SharedPtr message) = 0;
};

class IObservable {
public:
    virtual void subscribe(IObserver* observer) = 0;
};


class BaseObservable : public IObservable {
protected:
    std::list<IObserver*> m_subscribers;

    void sendMessage() {

    }

public:
    void subscribe(IObserver* observer) {
        m_subscribers.push_back(observer);
    }

    const std::list<IObserver*>& subscribers() const {
        return m_subscribers;
    }
};

#endif //BULK_OBSERVER_H
