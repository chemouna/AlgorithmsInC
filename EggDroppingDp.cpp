//
// Created by Mouna Cheikhna on 26/03/2017.
//

#include <iostream>

using namespace std;

int max(int a, int b) {
    int ans = (a > b) ? a : b;
    return ans;
}

int min(int a, int b) {
    int ans = (a < b) ? a : b;
    return ans;
}

int solveEggDropPuzzle(int eggs, int floors) {

    int numdrops[eggs + 1][floor + 1];

    for (int i1 = 0; i1 <= floor; ++i1) {
        numdrops[1][i1] = i1;
    }
    for (int i2 = 0; i2 <= floors; ++i2) {
        numdrops[0][i2] = 0;
    }
    for (int i3 = 0; i3 <= eggs; ++i3) {
        numdrops[i3][0] = 0;
    }

    for (int i = 2; i <= eggs; ++i) {
        for (int j = 1; j <= floors; ++j) {
            int minimum = INT_MAX;

            for (int x = 1; x <= j; ++x) {
                minimum = min(minimum, 1 + max(numdrops[i - 1][x - 1], numdrops[i][j - x]));
            }

            numdrops[i][j] = minimum;
        }
    }

    return numdrops[eggs][floors];
}

int main() {
    int e;
    int f;
    cout << "Egg dropping puzzle\n\nNumber of eggs:";
    cin >> e;
    cout << "\nNumber of floors:";
    cin >> f;
    cout << solveEggDropPuzzle(e, f);
    return 0;
}

