#include <iostream>
#include <thread>
#include <mutex>

class SingletonThreadSafe{
private:
    static SingletonThreadSafe* singleton_;
    static std::mutex mutex_;
    int value_;
    SingletonThreadSafe(int value): value_(value){}

public:
    SingletonThreadSafe(SingletonThreadSafe &other)  = delete;
    void operator=(const SingletonThreadSafe &other) = delete;
    static SingletonThreadSafe* Instance(int value);
    int value() const{
        return value_;
    }
};

SingletonThreadSafe* SingletonThreadSafe::singleton_ {nullptr};
std::mutex SingletonThreadSafe::mutex_{};

SingletonThreadSafe* SingletonThreadSafe::Instance(int value)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if(singleton_ == nullptr){
        singleton_ = new SingletonThreadSafe(value);
    }
    return singleton_;
}

void Thread1(){
    SingletonThreadSafe* singleton = SingletonThreadSafe::Instance(1);
    std::cout << singleton->value() << std::endl;
}

void Thread2(){
    SingletonThreadSafe* singleton = SingletonThreadSafe::Instance(2);
    std::cout << singleton->value() << std::endl;
}

void Thread3(){
    SingletonThreadSafe* singleton = SingletonThreadSafe::Instance(3);
    std::cout << singleton->value() << std::endl;
}

int main()
{
    std::thread thr1(Thread1);
    std::thread thr2(Thread2);
    std::thread thr3(Thread3);
    thr1.join();
    thr2.join();
    thr3.join();
    return 0;
}