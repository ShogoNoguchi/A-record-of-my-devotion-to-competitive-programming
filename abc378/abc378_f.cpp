#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int N;
vector<vector<int>> adj;
vector<int> degree;
vector<int> comp_id;

void bfs(int start, int cid) {
    queue<int> q;
    q.push(start);
    comp_id[start] = cid;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto v : adj[u]) {
            if (degree[v] == 3 && comp_id[v] == -1) {
                comp_id[v] = cid;
                q.push(v);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 入力の読み取り
    cin >> N;
    adj.resize(N + 1);
    degree.resize(N + 1, 0);
    comp_id.resize(N + 1, -1);

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        degree[u]++;
        degree[v]++;
    }

    // コンポーネントIDの割り当て
    int cid = 0;
    for (int u = 1; u <= N; u++) {
        if (degree[u] == 3 && comp_id[u] == -1) {
            bfs(u, cid);
            cid++;
        }
    }

    // 各コンポーネントに接続されている次数2の頂点を収集
    vector<vector<int>> comp_deg2(cid);
    for (int u = 1; u <= N; u++) {
        if (degree[u] == 3) {
            int id = comp_id[u];
            for (auto v : adj[u]) {
                if (degree[v] == 2) {
                    comp_deg2[id].push_back(v);
                }
            }
        }
    }

    // 結果の計算
    ll ans = 0;
    for (int i = 0; i < cid; i++) {
        int n = comp_deg2[i].size();
        ans += (ll)n * (n - 1) / 2;
    }

    cout << ans << endl;

    return 0;
}
