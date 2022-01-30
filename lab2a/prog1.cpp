#include <iostream>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

int main () {
    int pid = fork();
    if (!pid) {
        execlp("./prog2", "./prog2", NULL);
        perror("failed exec");
    }

    while (wait(NULL) != -1) {
        cout << "child completed :: " << pid << endl;
    }
    cout << getpid() << " done waiting" << endl;
}
