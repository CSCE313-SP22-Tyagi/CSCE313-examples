#include <iostream>

#include <sys/types.h>
#include <unistd.h>

using namespace std;

int main () {
    int top = -1;
    int* tpoint = &top;

    int a = 50;
    int b = 30;

    if (!fork()) {
        int c1 = a + b;

        cout << "\nchild" << endl;

        for (int i = 0; i < 10; i++) {
            cout << tpoint[i] << endl;
        }

        cout << "end child" << endl;
    }
    else {
        int c2 = a - b;

        cout << "\nparent" << endl;

        for (int i = 0; i < 10; i++) {
            cout << tpoint[i] << endl;
        }

        cout << "end parent" << endl;
    }
}
