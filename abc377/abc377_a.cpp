#include <iostream>
using namespace std;

int main() {
    string S;
    cin >> S;
    bool hasA = false, hasB = false, hasC = false;
    for (char c : S) {
        if (c == 'A') hasA = true;
        else if (c == 'B') hasB = true;
        else if (c == 'C') hasC = true;
    }
    if (hasA && hasB && hasC) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
    return 0;
}
