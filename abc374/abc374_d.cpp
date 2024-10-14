#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <limits>

using namespace std;

struct Point {
    double x, y;
};

int main() {
    int N;
    double S, T;
    cin >> N >> S >> T;

    int P = 1 + 2 * N; // Total number of positions
    vector<Point> positions(P);
    positions[0] = {0.0, 0.0}; // Starting position at index 0

    vector<pair<int, int>> endpoints(N); // Store indices of endpoints for each segment

    for (int i = 0; i < N; ++i) {
        double A, B, C, D;
        cin >> A >> B >> C >> D;
        positions[2 * i + 1] = {A, B};
        positions[2 * i + 2] = {C, D};
        endpoints[i] = {2 * i + 1, 2 * i + 2};
    }

    // Precompute distances between all positions
    vector<vector<double>> dist(P, vector<double>(P, 0.0));
    for (int i = 0; i < P; ++i) {
        for (int j = 0; j < P; ++j) {
            double dx = positions[i].x - positions[j].x;
            double dy = positions[i].y - positions[j].y;
            dist[i][j] = sqrt(dx * dx + dy * dy);
        }
    }

    int totalStates = 1 << N;
    int maxPositions = P;
    const double INF = numeric_limits<double>::infinity();

    vector<vector<double>> dp(totalStates, vector<double>(maxPositions, INF));
    dp[0][0] = 0.0; // Starting at position 0 with no segments printed

    for (int state = 0; state < totalStates; ++state) {
        for (int pos = 0; pos < maxPositions; ++pos) {
            if (dp[state][pos] < INF) {
                for (int s = 0; s < N; ++s) {
                    if ((state & (1 << s)) == 0) {
                        int newState = state | (1 << s);
                        // Option 1: Start from first endpoint
                        for (int k = 0; k < 2; ++k) {
                            int start_endpoint = endpoints[s].first;
                            int end_endpoint = endpoints[s].second;
                            if (k == 1) {
                                swap(start_endpoint, end_endpoint);
                            }

                            double time_to_move = dist[pos][start_endpoint] / S;
                            double time_to_print = dist[start_endpoint][end_endpoint] / T;
                            double total_time = dp[state][pos] + time_to_move + time_to_print;

                            if (dp[newState][end_endpoint] > total_time) {
                                dp[newState][end_endpoint] = total_time;
                            }
                        }
                    }
                }
            }
        }
    }

    double result = INF;
    int fullState = (1 << N) - 1;
    for (int pos = 0; pos < maxPositions; ++pos) {
        if (dp[fullState][pos] < result) {
            result = dp[fullState][pos];
        }
    }

    cout << fixed << setprecision(20) << result << endl;

    return 0;
}
