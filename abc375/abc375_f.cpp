#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

const ll INF = 1e15; // 十分大きな値

struct Edge {
    int u, v;
    ll w;
};

int main() {
    int N, M, Q;
    cin >> N >> M >> Q;

    vector<Edge> edges(M);
    vector<bool> deleted(M, false);

    // エッジの入力
    for (int i = 0; i < M; ++i) {
        int A, B;
        ll C;
        cin >> A >> B >> C;
        edges[i] = {A, B, C};
    }

    vector<pair<int, vector<int>>> queries(Q); // {クエリの種類, データ}
    for (int i = 0; i < Q; ++i) {
        int type;
        cin >> type;
        if (type == 1) {
            int idx;
            cin >> idx;
            idx--; // 0-based インデックスに調整
            deleted[idx] = true; // 道路を通行止めにする
            queries[i] = {type, {idx}};
        } else {
            int x, y;
            cin >> x >> y;
            queries[i] = {type, {x, y}};
        }
    }

    // 通行止めになっていない道路で初期のグラフを構築
    vector<vector<ll>> dist(N + 1, vector<ll>(N + 1, INF));
    for (int i = 1; i <= N; ++i) dist[i][i] = 0;

    for (int i = 0; i < M; ++i) {
        if (!deleted[i]) {
            int u = edges[i].u;
            int v = edges[i].v;
            ll w = edges[i].w;
            if (dist[u][v] > w) {
                dist[u][v] = w;
                dist[v][u] = w;
            }
        }
    }

    // フロイド–ワーシャル法で最短距離を計算
    for (int k = 1; k <= N; ++k) {
        for (int i = 1; i <= N; ++i) {
            if (dist[i][k] == INF) continue;
            for (int j = 1; j <= N; ++j) {
                if (dist[k][j] == INF) continue;
                if (dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    vector<ll> ans;
    // クエリを逆順に処理
    for (int q = Q - 1; q >= 0; --q) {
        int type = queries[q].first;
        if (type == 1) {
            int idx = queries[q].second[0];
            int u = edges[idx].u;
            int v = edges[idx].v;
            ll w = edges[idx].w;

            // 道路を再度開通
            if (dist[u][v] > w) {
                dist[u][v] = w;
                dist[v][u] = w;
            }

            // 新たに追加された道路を使って最短距離を更新
            for (int i = 1; i <= N; ++i) {
                for (int j = 1; j <= N; ++j) {
                    if (dist[i][u] + w + dist[v][j] < dist[i][j]) {
                        dist[i][j] = dist[i][u] + w + dist[v][j];
                    }
                    if (dist[i][v] + w + dist[u][j] < dist[i][j]) {
                        dist[i][j] = dist[i][v] + w + dist[u][j];
                    }
                }
            }

        } else {
            int x = queries[q].second[0];
            int y = queries[q].second[1];
            ll d = dist[x][y];
            ans.push_back(d);
        }
    }

    // 結果を正しい順序で出力
    for (int i = ans.size() - 1; i >= 0; --i) {
        if (ans[i] >= INF / 2) {
            cout << -1 << '\n';
        } else {
            cout << ans[i] << '\n';
        }
    }

    return 0;
}
