//
// Created by Mouna Cheikhna on 28/03/2017.
//

#include <vector>
#include <iostream>
#include <queue>

using namespace std;

int findMedian(vector<vector<int>> &a) {
    int lo = a[0][0];
    int hi = a[0][0];

    int n = a.size();
    int m = a[0].size();
    for (int i = 0; i < n; ++i) {
        if(a[i][0] < lo) { lo = a[i][0]; }
        if(a[i][m - 1] > hi) { hi = a[i][m - 1]; }
    }

    int desired = (1 + n * m) / 2;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        int count = 0;
        //computing p(x) value
        for (int i = 0; i < n; ++i) {
            //upper_bound here returns the value in row i which compares to greater than mid
            count += upper_bound(a[i].begin(), a[i].end(), mid) - a[i].begin();
        }
        if(count >= desired) { //p(x) == true
            hi = mid;
        }
        else {
            lo = mid - 1;
        }
    }

    return lo;
}

