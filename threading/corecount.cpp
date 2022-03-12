#include <cassert>
#include <cmath>
#include <cstdio>
#include <sys/time.h>

#include <atomic>
#include <mutex>
#include <thread>
#include <vector>
using namespace std;

//this is just a basic timer class that remembers when it was constructed
//and can be queried for how many seconds has passed since then
class Timer {
    //please ignore this voodoo magic :`)
    typedef std::result_of<decltype(std::chrono::high_resolution_clock::now)&(void)>::type TimeType;

    TimeType begin;
    public:
    Timer() : begin(std::chrono::high_resolution_clock::now()) {}
    double time() {
        //the chrono stuff only deals with integers, so to maximize precision,
        //we use a duration case to microseconds
        //then divide it by 1e6, which will be a floating-point division and retain the high precision.
        return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - begin).count() / 1e6;
    }
};

//implements a multithreaded add of an array of random numbers
class Adder {
    uint64_t len; //the number of ... numbers
    int* arr; //all of the numbers
    int realSum; //the actual value of the sum

public:
    //initialize an array of random integers
    //this is actually the slowest part of the program,
    //since it's single-threaded and calls rand()
    Adder(uint64_t len) : len(len), arr(new int[len]), realSum(0) {
        for(uint64_t i = 0; i < len; i++) {
            arr[i] = rand();
            realSum += arr[i];
        }
    }
    //basic descructor
    ~Adder() {
        delete[] arr;
    }
    //disable the copy constructor
    Adder(const Adder&) = delete;
    //

    //helper to count a chunk of an array
    int sum(int* buf, uint64_t count) {
        int total = 0;
        for(uint64_t i = 0; i < count; i++) {
            total += buf[i];
        }
        return total;
    }

    //thread function
    void threadSum(int* buf, uint64_t count, atomic_int* total) {
        //calculate the sum using the helper function
        //then atomically add it to the running total across all threads
        //(atomic variables are basically a simple partially-thread-safe version of normal variables)
        int result = sum(buf, count);
        total->fetch_add(result);
    }

    //this function actually runs the calculation, managing all of the threads
    //returns amt of time taken to process entire array
    double run(int threadCount) {
        Timer t;
        //
        atomic_int total(0);
        thread* threads = new thread[threadCount];
        uint64_t countPerThread = (len / threadCount) + (len % threadCount != 0); //each thread gets a roughly equal chunk; this rounds up, in case it doesn't evenly divide
        //
        uint64_t countHandled = 0; //keeps track of the amount of data left to assign
        for(int i = 0; i < threadCount; i++) {
            int* buf = arr + countHandled;
            uint64_t count = min(countPerThread, len - countHandled);
            threads[i] = thread(&Adder::threadSum, this, buf, count, &total);
            countHandled += count;
        }
        //make sure all data was handled
        assert(countHandled == len);
        //wait for completion
        for(int i = 0; i < threadCount; i++) {
            threads[i].join();
        }
        //cleanup
        delete[] threads;
        //make sure there wasn't any data corruption (validate using the single-threaded calculation from earlier)
        assert(total == realSum);
        //return execution time
        return t.time();
    }
};

int main(int argc, char** argv) {
    uint64_t n = 1LU << 30; //default data size = 1 GB
    //if user supplies an arg, use it to determine the data size
    //to keep the cmdline args shorter, they are the power of a base-2 exponent
    //so to get a MB, just pass "20"
    if(argc > 1) {
        float power = atof(argv[1]);
        n = std::pow(2, power); 
    }
    //
    printf("Initializing 2^%.1f bytes\n", log2(n));
    Timer t;
    Adder a(n);
    printf(" Initialized in %f sec\n", t.time());
    //
    printf("#threads, time (sec), speedup (relative to 1 thread)\n");
    //
    double timeSingle = a.run(1);
    printf("1, %.2f\n", timeSingle);
    //start off testing every count, then do logarithmic scaling
    std::vector<int> threadCounts;
    int cutoff = 32; //when to switch from linear to logarithmic scaling
    for(int threads = 2; threads <= cutoff; threads++) threadCounts.push_back(threads);
    for(int threads = cutoff * 2; threads <= 16384; threads *= 2) threadCounts.push_back(threads);
    //
    for(int threads : threadCounts) {
        double time = a.run(threads);
        printf("%d, %.2f, %.2fx\n", threads, time, timeSingle / time);
    }
}
