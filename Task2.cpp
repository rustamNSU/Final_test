#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <utility>
using namespace std::literals;

std::mutex car_mutex;
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
                car_mutex.lock();
                std::cout << std::to_string(layers) << ") " << "Painting car\n";
                ++layers;
                car_mutex.unlock();
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
                car_mutex.lock();
                std::cout << std::to_string(layers) << ") " << "Drying car\n";
                ++layers;
                car_mutex.unlock();
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
