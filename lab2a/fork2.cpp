//This is a modified version of fork.cpp that interleaves parent/child printing for better visibility

#include <iostream>

#include <sys/types.h>
#include <unistd.h>
#include <time.h>

using namespace std;

int main () {
    int top = -1;
    int* tpoint = &top;

    int a = 50;
    int b = 30;

    cout << "idx\t\tparent\t\t\tchild" << endl;

    timespec waittime1;
    waittime1.tv_sec = 0;
    waittime1.tv_nsec = 1000000; //1e6 nano = 1 milli
    timespec waittime2;
    waittime2.tv_sec = 0;
    waittime2.tv_nsec = 2000000; //2e6 nano = 2 milli

    if (!fork()) {
        int c1 = a + b;

        nanosleep(&waittime1, NULL);

        for (int i = 0; i < 10; i++) {
            cout << "c " << tpoint[i] << endl;
        nanosleep(&waittime2, NULL);
        }

        cout << "end child" << endl;
    }
    else {
        int c2 = a - b;

        for (int i = 0; i < 10; i++) {
            cout << "[" << i << "]\t\ts " << tpoint[i] << "\t\t\t" << flush;
            nanosleep(&waittime2, NULL);
        }

        nanosleep(&waittime2, NULL);

        cout << "end parent" << endl;
    }
}
