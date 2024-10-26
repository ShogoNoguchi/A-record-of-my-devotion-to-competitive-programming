#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<string> S(8);
    for (int i = 0; i < 8; ++i) {
        cin >> S[i];
    }

    bool row_has_piece[8] = {false};
    bool col_has_piece[8] = {false};

    // 既存のコマのある行と列を記録
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (S[i][j] == '#') {
                row_has_piece[i] = true;
                col_has_piece[j] = true;
            }
        }
    }

    int count = 0;
    // 空マスで、かつその行と列に既存のコマがないマスをカウント
    for (int i = 0; i < 8; ++i) {
        if (!row_has_piece[i]) {
            for (int j = 0; j < 8; ++j) {
                if (!col_has_piece[j] && S[i][j] == '.') {
                    count++;
                }
            }
        }
    }

    cout << count << endl;
    return 0;
}
