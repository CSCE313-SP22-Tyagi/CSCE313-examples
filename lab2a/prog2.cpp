#include <iostream>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

int main () {
    cout << "\tin " << getpid() << endl;
    cout << "\treturning to " << getppid() << " after 2 seconds" << endl;
    sleep(2);
}
