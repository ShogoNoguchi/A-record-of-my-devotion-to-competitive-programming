#include <iostream>
using namespace std;

int main() {
    int N, C;
    cin >> N >> C;
    int T[100];
    for(int i = 0; i < N; ++i) {
        cin >> T[i];
    }
    int candies = 0;
    int last_candy_time = -1e9; // Initialize to a very small number
    for(int i = 0; i < N; ++i) {
        if(T[i] - last_candy_time >= C) {
            candies++;
            last_candy_time = T[i];
        }
    }
    cout << candies << endl;
    return 0;
}
