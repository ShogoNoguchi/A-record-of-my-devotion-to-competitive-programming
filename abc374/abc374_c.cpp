#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int64_t> K(N);
    int64_t sumTotal = 0;
    for (int i = 0; i < N; ++i) {
        cin >> K[i];
        sumTotal += K[i];
    }

    int64_t minMaxSum = sumTotal;
    int64_t numPartitions = 1LL << N;

    for (int64_t partition = 0; partition < numPartitions; ++partition) {
        int64_t sumA = 0;
        for (int i = 0; i < N; ++i) {
            if (partition & (1LL << i)) {
                sumA += K[i];
            }
        }
        int64_t sumB = sumTotal - sumA;
        int64_t maxSum = max(sumA, sumB);
        if (maxSum < minMaxSum) {
            minMaxSum = maxSum;
        }
    }

    cout << minMaxSum << endl;
    return 0;
}
