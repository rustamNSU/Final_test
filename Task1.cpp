#include <iostream>
#include <thread>
#include <mutex>

class RaiiThread{
private:
    std::thread thr_;

public:
    template<class Function, class... Args>
    RaiiThread(Function&& fn, Args&&... args) : thr_(fn, args...){}

    ~RaiiThread(){
        if (thr_.joinable())
        {
            thr_.join();
            std::cout << "Yeeah, baby\n";
        }
    }
};

void check(){
    std::cout << "run void check()\n";
    return;
}

int main()
{
    RaiiThread{check};
    return 0;
}
