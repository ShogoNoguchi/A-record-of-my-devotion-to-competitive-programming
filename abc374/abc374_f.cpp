#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <climits>

using namespace std;

typedef long long ll;

int N, K;
ll X;
vector<ll> T;

map<pair<int, ll>, ll> memo;

ll dfs(int pos, ll last_ship_day) {
    if (pos == N) {
        return 0;
    }
    if (memo.count({pos, last_ship_day})) {
        return memo[{pos, last_ship_day}];
    }

    ll res = LLONG_MAX;

    ll earliest_possible = last_ship_day + X; // Next shipping can be at day last_ship_day + X

    // Try shipping from size 1 to K
    for (int sz = 1; sz <= K; ++sz) {
        if (pos + sz > N) {
            break;
        }
        // Maximum Ti in the current shipment
        ll Ti_max = T[pos + sz - 1];

        // Shipping day s
        ll s = max(earliest_possible, Ti_max);

        // Calculate dissatisfaction for orders from pos to pos + sz - 1
        ll total_dissatisfaction = 0;
        for (int i = pos; i < pos + sz; ++i) {
            total_dissatisfaction += (s - T[i]);
        }

        ll total = total_dissatisfaction + dfs(pos + sz, s);
        res = min(res, total);
    }

    memo[{pos, last_ship_day}] = res;
    return res;
}

int main() {
    cin >> N >> K >> X;
    T.resize(N);
    for (int i = 0; i < N; ++i) {
        cin >> T[i];
    }

    ll result = dfs(0, -X);

    cout << result << endl;

    return 0;
}
