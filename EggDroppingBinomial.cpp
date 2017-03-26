//
// Created by Mouna Cheikhna on 26/03/2017.
//
#include <iostream>

using namespace std;

//Evaluates C(n,k) and verifies if it's greater than or equal to k
long long binomial(int x, int n, int k) {

    int i;
    long long int answer = 0;
    double aux = 1;

    //Calculates C(n,k) using the formula: C(n,k): sum_i_0^k {(n-i+1)/i}
    for (i = 1; i <= n; i++) {

        aux *= (float) x + 1 - i;
        aux /= (float) i;
        answer += aux;

        if (answer > k) break;
    }

    return answer;
}

int binarySearchEggDrop(int n, int k) {
    int inf = 0;
    int upper = k;
    int mid;

    while(upper - inf > 1) {
        mid = inf + (upper - inf) / 2;
        if(binomial(mid, n, k) < k) {
            inf = mid;
        }
        else {
            upper = mid;
        }
    }

    return inf;
}

int main() {
    int n; //Number of eggs
    int k; //Number of floors

    cout << "Egg dropping puzzle: ( O(n log k)  solution )\n\n";

    cout << "Number of floors:";
    cin >> k;

    cout << "\nNumber of eggs:";
    cin >> n;

    int res = binarySearchEggDrop(n, k);

    cout << "\nNumber of drops in the worst case: " << (res + 1);
}
