#include <iostream>
#include <cmath>
#include <vector>

int main() {
    int N;
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> N;

    std::vector<std::pair<int64_t, int64_t>> points(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> points[i].first >> points[i].second;
    }

    double total_cost = 0.0;

    // Distance from origin to first point
    total_cost += std::hypot(points[0].first, points[0].second);

    // Sum of distances between consecutive points
    for (int i = 0; i < N - 1; ++i) {
        int64_t dx = points[i + 1].first - points[i].first;
        int64_t dy = points[i + 1].second - points[i].second;
        total_cost += std::hypot(dx, dy);
    }

    // Distance from last point back to origin
    total_cost += std::hypot(points[N - 1].first, points[N - 1].second);

    std::cout.precision(15);
    std::cout << std::fixed << total_cost << '\n';

    return 0;
}
