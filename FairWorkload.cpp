//
// Created by Mouna Cheikhna on 28/03/2017.
//

#include <vector>
#include <iostream>
#include <queue>
#include <numeric>

using namespace std;

// Complexity O(n log SIZE) where n is the nb of workers and SIZE is the number of cabinets
int getMostWork(vector<int> folders, int workers) {
    int n = folders.size();
    int lo = *max_element(folders.begin(), folders.end());
    int hi = accumulate(folders.begin(), folders.end(), 0);

    while (lo < hi) {
        int mid = lo + (hi - lo + 1) / 2;

        int required_workers = 1;
        int current_load = 0;

        //calculating p(x)
        for (int i = 0; i < n; ++i) {
            if(current_load + folders[i] <= mid) {
                //we can still assign the next load to worker
                current_load += folders[i];
            }
            else { //assign a new worker to the next load
                required_workers++;
                current_load = folders[i];
            }
        }

        //checking p(x) == true
        if(required_workers <= workers) {
            hi = mid;
        }
        else {
            lo = mid - 1;
        }

    }

    return lo;
}