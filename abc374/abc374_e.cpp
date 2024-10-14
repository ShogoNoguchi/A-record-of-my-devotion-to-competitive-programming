#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

typedef long long ll;

const ll INF = 1e18;

int N;
ll X;
vector<int> A, B;
vector<ll> P, Q;

ll compute_min_cost(int idx, ll W) {
    ll minCost = INF;
    int A_i = A[idx], B_i = B[idx];
    ll P_i = P[idx], Q_i = Q[idx];

    // 単位処理能力あたりのコストを計算
    double unit_cost_S = (double)P_i / A_i;
    double unit_cost_T = (double)Q_i / B_i;

    // 最適な s_i と t_i を初期化
    ll s_opt = (W + A_i - 1) / A_i;
    ll t_opt = (W + B_i - 1) / B_i;

    // 探索範囲を設定
    ll s_start = max(0LL, s_opt - 1000);
    ll s_end = s_opt + 1000;
    ll t_start = max(0LL, t_opt - 1000);
    ll t_end = t_opt + 1000;

    // s_i を固定して t_i を計算
    for (ll s = s_start; s <= s_end; ++s) {
        ll W_remain = W - A_i * s;
        ll t = (W_remain > 0) ? (W_remain + B_i - 1) / B_i : 0;
        if (t < 0) continue;
        ll cost = P_i * s + Q_i * t;
        if (cost < minCost) {
            minCost = cost;
        }
    }

    // t_i を固定して s_i を計算
    for (ll t = t_start; t <= t_end; ++t) {
        ll W_remain = W - B_i * t;
        ll s = (W_remain > 0) ? (W_remain + A_i - 1) / A_i : 0;
        if (s < 0) continue;
        ll cost = P_i * s + Q_i * t;
        if (cost < minCost) {
            minCost = cost;
        }
    }

    return minCost;
}

int main() {
    cin >> N >> X;
    A.resize(N);
    B.resize(N);
    P.resize(N);
    Q.resize(N);

    for (int i = 0; i < N; ++i) {
        cin >> A[i] >> P[i] >> B[i] >> Q[i];
    }

    ll left = 0, right = 1e9;
    ll answer = 0;

    while (left <= right) {
        ll mid = (left + right) / 2;
        ll totalCost = 0;
        bool possible = true;

        for (int i = 0; i < N; ++i) {
            ll cost = compute_min_cost(i, mid);
            if (cost >= INF) {
                possible = false;
                break;
            }
            totalCost += cost;
            if (totalCost > X) {
                possible = false;
                break;
            }
        }

        if (possible) {
            answer = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    cout << answer << endl;
    return 0;
}
