#include <iostream>
#include <limits.h>

using namespace std;

int max(int a, int b) {
    int ans = (a > b) ? a : b;
    return ans;
}

int min(int a, int b) {
    int ans = (a < b) ? a : b;
    return ans;
}

int eggdrop_recur(int n, int h) {

    if (n == 1) return h;
    if (h == 1) return n;
    if (h == 0) return 0;

    int minimum = INT_MAX;

    for (int x = 1; x < h; x++) {
        minimum = min(minimum, 1 + max(eggdrop_recur(n - 1, x - 1), eggdrop_recur(n, h - x)));
    }

    return minimum;
}

int main() {
    int e;
    int f;
    cout << "Egg dropping puzzle\n\nNumber of eggs:";
    cin >> e;
    cout << "\nNumber of floors:";
    cin >> f;
    cout << "\nNumber of drops in the worst case:" << eggdrop_recur(e, f);
    return 0;
}

