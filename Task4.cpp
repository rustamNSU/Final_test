#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>

class Spinlock{
private:
    std::atomic<bool> lock_ = false;

public:
    Spinlock() = default;
    Spinlock(const Spinlock &other) = delete;
    Spinlock(Spinlock &&other) = delete;
    Spinlock& operator=(const Spinlock &other) = delete;
    Spinlock& operator=(Spinlock &&other) = delete;

    void lock(){
        while(lock_.exchange(true, std::memory_order_acquire));
    }
    void unlock() {
        lock_.store(false, std::memory_order_release);
    }
};

Spinlock spinlock;
int check = 1;
int LAYERS = 5;
bool Painting = true;

class Painter{
private:
    std::thread thr_;
    int layers = 0;
public:
    Painter() : thr_(&Painter::working, this) {}
    void working(){
        while (layers < LAYERS)
        {
            if(Painting)
            {
                std::lock_guard<Spinlock> guard(spinlock);
                std::cout << std::to_string(layers) << ") " << "Painting car\n";
                ++layers;
                Painting = false;
            }
        }
    }
    ~Painter(){
        if(thr_.joinable()){
            thr_.join();
        }
    }
};

class Dryer{
private:
    std::thread thr_;
    int layers = 0;
public:
    Dryer() : thr_(&Dryer::working, this) {}
    void working(){
        while (layers < LAYERS)
        {
            if(!Painting)
            {
                std::lock_guard<Spinlock> guard(spinlock);
                std::cout << std::to_string(layers) << ") " << "Drying car\n";
                ++layers;
                Painting = true;
            }
        }
    }
    ~Dryer(){
        if(thr_.joinable()){
            thr_.join();
        }
    }
};


int main()
{
    Painter wk1{};
    Dryer wk2{};
    return 0;
}