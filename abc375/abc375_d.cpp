#include <iostream>
#include <vector>
#include <string>
#include <cstdint>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string S;
    std::cin >> S;
    int N = S.length();

    int64_t ans = 0;

    // For each uppercase letter, store positions
    std::vector<std::vector<int>> positions(26);

    for (int i = 0; i < N; ++i) {
        positions[S[i] - 'A'].push_back(i);
    }

    for (int c = 0; c < 26; ++c) {
        const auto& pos = positions[c];
        int m = pos.size();
        if (m < 2) continue;

        // Compute suffix sums of positions
        std::vector<int64_t> sufSum(m + 1, 0);
        for (int i = m - 1; i >= 0; --i) {
            sufSum[i] = pos[i] + sufSum[i + 1];
        }

        int64_t total_c = 0;
        for (int i = 0; i < m - 1; ++i) {
            int64_t s = m - i - 1;
            total_c += sufSum[i + 1] - s * pos[i] - s;
        }

        ans += total_c;
    }

    std::cout << ans << '\n';

    return 0;
}
