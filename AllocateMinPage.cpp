//
// Created by Mouna Cheikhna on 28/03/2017.
//
/**
 *
Input : pages[] = {12, 34, 67, 90}
        m = 2
Output : 113
Explanation:
There are 2 number of students. Books can be distributed
in following fashion :
  1) [12] and [34, 67, 90]
      Max number of pages is allocated to student
      2 with 34 + 67 + 90 = 191 pages
  2) [12, 34] and [67, 90]
      Max number of pages is allocated to student
      2 with 67 + 90 = 157 pages
  3) [12, 34, 67] and [90]
      Max number of pages is allocated to student
      1 with 12 + 34 + 67 = 113 pages

  Of the 3 cases, Option 3 has the minimum pages = 113.
*/

#include <vector>
#include <numeric>
#include <iostream>

using namespace std;


int findPages(vector<int> pages, int students) {
    int lo = *max_element(pages.begin(), pages.end());
    int hi = accumulate(pages.begin(), pages.end(), 0);

    while (lo < hi) {
        int mid = lo + (hi - lo + 1) / 2;

        int required_students = 1;
        int current_sum = 0;

        for (int i = 0; i < pages.size(); ++i) {
            if (current_sum + pages[i] <= mid) {
                current_sum += pages[i];
            } else {
                current_sum = pages[i];
                required_students++;
            }
        }

        if (required_students <= students) {
            hi = mid;
        } else {
            lo = mid - 1;
        }
    }

    return lo;
}

int main() {
    //Number of pages in books
    vector<int> arr = {12, 34, 67, 90};
    int n = sizeof arr / sizeof arr[0];
    int m = 2; //No. of students

    cout << "Minimum number of pages = "
         << findPages(arr, m) << endl;
    return 0;
}
