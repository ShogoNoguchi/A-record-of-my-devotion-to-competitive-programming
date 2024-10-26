#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
    int N, M;
    cin >> N >> M;
    vector<int> min_R(M + 2, M + 1);
    for (int i = 0; i < N; ++i) {
        int L_i, R_i;
        cin >> L_i >> R_i;
        if (min_R[L_i] > R_i) {
            min_R[L_i] = R_i;
        }
    }
    for (int l = M; l >= 1; --l) {
        if (min_R[l] > min_R[l + 1]) {
            min_R[l] = min_R[l + 1];
        }
    }
    ll total_intervals = (ll)M * (M + 1) / 2;
    ll total_forbidden = 0;
    for (int l = 1; l <= M; ++l) {
        if (min_R[l] <= M) {
            int start_r = max(l, min_R[l]);
            if (start_r <= M) {
                total_forbidden += M - start_r + 1;
            }
        }
    }
    ll answer = total_intervals - total_forbidden;
    cout << answer << endl;
    return 0;
}
