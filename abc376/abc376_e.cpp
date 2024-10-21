#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>  // LLONG_MAX を使用するために追加

typedef long long ll;

int main() {
    int T;
    std::cin >> T;
    std::vector<ll> answers(T);

    for (int t = 0; t < T; ++t) {
        int N, K;
        std::cin >> N >> K;
        std::vector<std::pair<int, int>> items(N);
        for (int i = 0; i < N; ++i) {
            std::cin >> items[i].first; // A_i
        }
        for (int i = 0; i < N; ++i) {
            std::cin >> items[i].second; // B_i
        }

        // A_i で昇順ソート
        std::sort(items.begin(), items.end());

        // 最大の B_i を追跡するための最大ヒープ
        std::priority_queue<int> maxHeap;
        ll sumB = 0;
        ll minValue = LLONG_MAX;

        for (int i = 0; i < N; ++i) {
            int A_i = items[i].first;
            int B_i = items[i].second;

            maxHeap.push(B_i);
            sumB += B_i;

            if ((int)maxHeap.size() > K) {
                sumB -= maxHeap.top();
                maxHeap.pop();
            }

            if ((int)maxHeap.size() == K) {
                ll currentValue = static_cast<ll>(A_i) * sumB;
                if (currentValue < minValue) {
                    minValue = currentValue;
                }
            }
        }
        answers[t] = minValue;
    }

    for (int t = 0; t < T; ++t) {
        std::cout << answers[t] << '\n';
    }
    return 0;
}
