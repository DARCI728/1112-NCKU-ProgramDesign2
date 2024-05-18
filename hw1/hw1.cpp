#include <iostream>

using namespace std;

int main(int argc, char** argv) {
    int n = atoi(argv[1]), max = 0;
    for (int i = 0; i <= n; i++) {
        max = (i * (n - i) > max) ? i * (n - i) : max;
        cout << "(" << i << "," << n - i << ")" << endl;
    }
    cout << max << endl;
    return 0;
}
