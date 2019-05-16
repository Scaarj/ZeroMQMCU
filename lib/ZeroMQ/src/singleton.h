#ifndef SINGLETON_H
#define SINGLETON_H

template<typename T>
class singleton {
public:
    static T& instance() {
        static T instance;
        return instance;
    }

private:
    singleton() {}
    ~singleton() {}
    singleton(const singleton&) = delete;
    singleton& operator=(const singleton&) = delete;
};

#endif // SINGLETON_H
