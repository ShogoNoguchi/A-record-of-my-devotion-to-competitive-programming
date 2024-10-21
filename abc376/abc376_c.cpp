#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N;
vector<long long> A;
vector<long long> B;

bool is_possible(long long x) {
    vector<long long> box_sizes = B;
    box_sizes.push_back(x);
    sort(box_sizes.begin(), box_sizes.end());
    for (int i = 0; i < N; ++i) {
        if (A[i] > box_sizes[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    cin >> N;
    A.resize(N);
    B.resize(N - 1);
    for (int i = 0; i < N; ++i) cin >> A[i];
    for (int i = 0; i < N - 1; ++i) cin >> B[i];

    sort(A.begin(), A.end());
    sort(B.begin(), B.end());

    long long left = 1, right = 1e10;
    long long ans = -1;

    while (left <= right) {
        long long mid = (left + right) / 2;
        if (is_possible(mid)) {
            ans = mid;
            right = mid - 1; // より小さい値を探す
        } else {
            left = mid + 1;
        }
    }

    cout << ans << endl;
    return 0;
}
