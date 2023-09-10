#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
#include <mutex>

using namespace std;

void work(int &count, mutex &mtx)
{
    for(int i = 0; i < 1E6; ++i){
            unique_lock<mutex> guard(mtx);
            ++count;
        }
}

int main(){
    int count = 0;

    mutex mtx;

    // Record the starting time
    auto start = std::chrono::high_resolution_clock::now();

    thread t1(work, ref(count), ref(mtx));
    thread t2(work, ref(count), ref(mtx));


    t1.join();
    t2.join();
    // Record the ending time
    auto end = std::chrono::high_resolution_clock::now();

    // Calculate the duration (time difference)
    std::chrono::duration<double> duration = end - start;

    // Convert duration to milliseconds or other time units if needed
    double milliseconds = duration.count() * 1000.0;

    // Print the time taken
    std::cout << "Time taken: " << milliseconds << " milliseconds" << std::endl;

    cout << count << endl;

    return 0;
}