#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>

int main() {
    int N, M;
    std::cin >> N >> M;

    std::vector<std::vector<int>> graph(N + 1);
    for (int i = 0; i < M; ++i) {
        int a, b;
        std::cin >> a >> b;
        graph[a].push_back(b);
    }

    std::vector<int> dist(N + 1, -1);
    std::vector<int> parent(N + 1, -1);
    std::queue<int> q;

    dist[1] = 0;
    q.push(1);

    int min_cycle_length = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : graph[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                parent[v] = u;
                q.push(v);
            } else if (v == 1) {
                if (min_cycle_length == -1 || dist[u] + 1 < min_cycle_length) {
                    min_cycle_length = dist[u] + 1;
                }
            }
        }
    }

    std::cout << min_cycle_length << std::endl;

    return 0;
}