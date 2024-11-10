#include <iostream>
#include <set>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int Q;
    cin >> Q;

    multiset<long long> plants;
    long long global_add = 0;
    int harvest_queries = 0;

    for (int i = 0; i < Q; ++i) {
        int type;
        cin >> type;

        if (type == 1) {
            plants.insert(-global_add);
        } else if (type == 2) {
            long long T;
            cin >> T;
            global_add += T;
        } else if (type == 3) {
            long long H;
            cin >> H;
            long long threshold = H - global_add;
            auto it = plants.lower_bound(threshold);
            long long num_harvested = distance(it, plants.end());
            cout << num_harvested << "\n";
            plants.erase(it, plants.end());
        }
    }

    return 0;
}
