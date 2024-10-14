#include <iostream>
#include <vector>
using namespace std;

int main() {
    int N;
    cin >> N;
    vector<string> grid(N);
    for(int i = 0; i < N; ++i) {
        cin >> grid[i];
    }
    vector<string> result(N, string(N, '.'));
    for(int x = 1; x <= N; ++x) {
        for(int y = 1; y <= N; ++y) {
            int s = min(min(x - 1, y - 1), min(N - x, N - y)) + 1;
            int k = s % 4;
            int x_s, y_s;
            if(k == 0) {
                x_s = x;
                y_s = y;
            } else if(k == 1) {
                x_s = N + 1 - y;
                y_s = x;
            } else if(k == 2) {
                x_s = N + 1 - x;
                y_s = N + 1 - y;
            } else { // k == 3
                x_s = y;
                y_s = N + 1 - x;
            }
            // Adjust for 0-based indexing
            result[x - 1][y - 1] = grid[x_s - 1][y_s - 1];
        }
    }
    for(int i = 0; i < N; ++i) {
        cout << result[i] << endl;
    }
    return 0;
}
