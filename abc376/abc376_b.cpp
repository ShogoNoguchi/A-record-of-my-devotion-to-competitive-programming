#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

// BFSを用いて最短距離を計算する関数
int bfs(int N, int start, int target, int forbidden) {
    vector<int> dist(N + 1, -1); // 1-indexed
    queue<int> q;
    dist[start] = 0;
    q.push(start);

    while (!q.empty()) {
        int curr = q.front(); q.pop();

        if (curr == target) {
            return dist[curr];
        }

        // 左隣
        int left = (curr == 1) ? N : curr - 1;
        if (left != forbidden && dist[left] == -1) {
            dist[left] = dist[curr] + 1;
            q.push(left);
        }

        // 右隣
        int right = (curr == N) ? 1 : curr + 1;
        if (right != forbidden && dist[right] == -1) {
            dist[right] = dist[curr] + 1;
            q.push(right);
        }
    }
    // ここに来ることはない（問題文で達成可能と保証されている）
    return -1;
}

int main() {
    int N, Q;
    cin >> N >> Q;

    vector<char> H(Q);
    vector<int> T(Q);
    for (int i = 0; i < Q; ++i) {
        cin >> H[i] >> T[i];
    }

    int l = 1, r = 2; // 初期位置
    int total_moves = 0;

    for (int i = 0; i < Q; ++i) {
        char hand = H[i];
        int target = T[i];

        if (hand == 'L') {
            // 左手を移動
            int moves = bfs(N, l, target, r);
            total_moves += moves;
            l = target;
        } else {
            // 右手を移動
            int moves = bfs(N, r, target, l);
            total_moves += moves;
            r = target;
        }
    }

    cout << total_moves << endl;

    return 0;
}
