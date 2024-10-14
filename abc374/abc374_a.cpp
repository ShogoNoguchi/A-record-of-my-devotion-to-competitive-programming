#include <iostream>
#include <string>
using namespace std;

int main() {
    string S;
    cin >> S;
    int n = S.size();
    if (n >= 3 && S[n - 3] == 's' && S[n - 2] == 'a' && S[n - 1] == 'n') {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
    return 0;
}
