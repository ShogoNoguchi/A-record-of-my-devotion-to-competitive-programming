#include <iostream>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <cstdint>

using namespace std;

int main() {
    int64_t N, M;
    cin >> N >> M;

    vector<pair<int32_t, int32_t>> pieces(M);
    unordered_set<uint64_t> occupied;

    for (int64_t idx = 0; idx < M; ++idx) {
        int32_t a, b;
        cin >> a >> b;
        pieces[idx] = {a, b};
        uint64_t key = ((uint64_t)a << 32) | (uint32_t)b;
        occupied.insert(key);
    }

    // ナイトの移動方向
    int di[8] = {2,1,-1,-2,-2,-1,1,2};
    int dj[8] = {1,2,2,1,-1,-2,-2,-1};

    vector<uint64_t> attacked_empty_cells;

    for (const auto& p : pieces) {
        int32_t i = p.first;
        int32_t j = p.second;
        for (int k = 0; k < 8; ++k) {
            int32_t ni = i + di[k];
            int32_t nj = j + dj[k];
            if (ni >= 1 && ni <= N && nj >=1 && nj <= N) {
                uint64_t key = ((uint64_t)ni << 32) | (uint32_t)nj;
                if (occupied.find(key) == occupied.end()) {
                    attacked_empty_cells.push_back(key);
                }
            }
        }
    }

    // 攻撃可能なマスをソートしてユニークにする
    sort(attacked_empty_cells.begin(), attacked_empty_cells.end());
    attacked_empty_cells.erase(unique(attacked_empty_cells.begin(), attacked_empty_cells.end()), attacked_empty_cells.end());

    int64_t total_empty_cells = N * N - M;
    int64_t safe_empty_cells = total_empty_cells - attacked_empty_cells.size();

    cout << safe_empty_cells << endl;

    return 0;
}
