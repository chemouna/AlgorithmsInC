
#include <iostream>
#include <iomanip>

static const int alphabetSize = 26;
using namespace std;

bool isInAscendingOrder(string str) {
    for (int i = 1; i < str.size(); ++i) {
        if (str[i] <= str[i - 1]) return false;
    }

    return true;
}

int NChooseK(int n, int k) {
    if (n == k || k == 0) return 1;

    return NChooseK(n - 1, k) + NChooseK(n - 1, k - 1);
}

static int FindIndex(string str) {
    if (!isInAscendingOrder(str)) return 0;

    // count how many strings before string with str.size()
    // C(26, 1) + C(26, 2) + ... + C(26, len - 1)
    int index = 0;
    int i = 1;
    while (i < str.size()) {
        index += NChooseK(alphabetSize, i);
        i++;
    }

    char desirableStart;
    i = 0;
    while (i < str.size()) {
        desirableStart = (i == 0) ? 'a' : str[i - 1] + 1;

        for (int j = desirableStart; j < str[i]; ++j) {
            index += NChooseK('z' - j, str.size() - i - 1);     // Choose str.size() - i - 1 in the available charset
        }

        i++;
    }

    index++;
    return index;
}

/** During preprocessing, in array 'a'
* a[i][j] stores number of valid combinations
* of length i+1 starting from (j+1)th character
* and b[i][j] represents index of first valid combination
* of length i+1 starting from (j+1)th character
* */
void findIndexSol2(char *str) {
    int a[alphabetSize][alphabetSize] = {0};
    int b[alphabetSize][alphabetSize] = {0};
    for (int i = 0; i < alphabetSize; i++)
        a[0][i] = 1;

    for (int i = 1; i < alphabetSize; i++) {
        for (int j = 0; j < alphabetSize; j++) {
            for (int k = j + 1; k < alphabetSize; k++) {
                a[i][j] = a[i][j] + a[i - 1][k];
            }
        }
    }

    b[0][0] = 1;
    for (int i = 0; i < alphabetSize; i++)
        for (int j = 0; j < alphabetSize; j++) {
            if (j != 0)
                b[i][j] = b[i][j - 1] + a[i][j - 1];
            if (j == 0 && i != 0)
                b[i][j] = b[i - 1][25] + a[i - 1][25];
        }


    int len = strlen(str);
    int result = 0;
    int mvindx = 0;
    for (int i = len - 1; i >= 0; i--) {
        int indx = int(str[len - 1 - i]) - 'a';
        if (i != 0)
            mvindx = b[i - 1][indx + 1];
        else
            mvindx = 0;
        result = result + b[i][indx] - mvindx;
    }
    cout << "\nResult----" << str << "----" << result;

}

static void DoTest(char *str) {
    cout << setw(10) << left << str;
    //cout << " ----> " << left << FindIndex(str) << endl;
    findIndexSol2(str);
    cout << "--------------------------------" << endl;
}

int main(int argc, char *argv[]) {
    DoTest("ab");       // 27
    DoTest("ba");       // 0
    DoTest("bc");       // 52
    DoTest("aez");      // 441
    DoTest("cde");      // 928
    DoTest("cdb");      // 0
    DoTest("cdf");      // 929
    DoTest("moqx");     // 16983
    DoTest("xyz");      // 2951
    DoTest("hjmoqsu");  // 930152

    return 0;
}
