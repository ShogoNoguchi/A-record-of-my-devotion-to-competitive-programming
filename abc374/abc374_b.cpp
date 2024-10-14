#include <iostream>
#include <string>
using namespace std;

int main() {
    string S, T;
    cin >> S >> T;
    int lenS = S.length();
    int lenT = T.length();
    int maxLen = max(lenS, lenT);
    int i;
    for (i = 1; i <= maxLen; ++i) {
        int idx = i - 1;
        if (idx < lenS && idx < lenT) {
            if (S[idx] != T[idx]) {
                cout << i << endl;
                return 0;
            }
        } else {
            // One string is shorter than the other
            cout << i << endl;
            return 0;
        }
    }
    // Strings are equal
    cout << 0 << endl;
    return 0;
}
