#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

// 繰り返し二乗法で (base^exp) % mod を計算
ll powmod(ll base, ll exp, ll mod) {
    ll result = 1 % mod;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = result * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return result;
}

int main() {
    ll N, K;
    cin >> N >> K;
    vector<int> P(N);
    for (int i = 0; i < N; ++i) {
        cin >> P[i];
        --P[i]; // 0-based index に変換
    }

    vector<bool> visited(N, false);
    vector<int> result(N);

    for (int i = 0; i < N; ++i) {
        if (!visited[i]) {
            // サイクルを構築
            vector<int> cycle;
            int curr = i;
            while (!visited[curr]) {
                visited[curr] = true;
                cycle.push_back(curr);
                curr = P[curr];
            }

            ll L = cycle.size();
            ll e_mod_L = powmod(2LL, K, L); // e = 2^K mod L

            // 新しい位置を計算
            for (ll pos = 0; pos < L; ++pos) {
                ll new_pos = (pos + e_mod_L) % L;
                result[cycle[pos]] = cycle[new_pos];
            }
        }
    }

    // 結果を出力（1-based index に戻す）
    for (int i = 0; i < N; ++i) {
        cout << result[i] + 1;
        if (i != N - 1) cout << " ";
    }
    cout << endl;

    return 0;
}
