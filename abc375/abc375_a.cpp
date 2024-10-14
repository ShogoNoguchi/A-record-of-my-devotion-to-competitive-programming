#include <iostream>
#include <string>

int main() {
    int N;
    std::string S;
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> N >> S;

    int ans = 0;
    for (int i = 0; i < N - 2; ++i) {
        if (S[i] == '#' && S[i + 1] == '.' && S[i + 2] == '#') {
            ++ans;
        }
    }

    std::cout << ans << '\n';

    return 0;
}
