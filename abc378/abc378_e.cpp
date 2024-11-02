#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// Binary Indexed Tree (Fenwick Tree) for frequency counting
struct BIT {
    int size;
    vector<int> tree;

    BIT(int n) : size(n), tree(n + 2, 0) {}

    void update(int idx, int delta=1) {
        idx += 1; // 1-based indexing
        while (idx <= size +1) {
            tree[idx] += delta;
            idx += idx & (-idx);
        }
    }

    // Returns the count of elements <= idx
    int query(int idx) const {
        idx +=1; // 1-based indexing
        int res =0;
        int x = const_cast<BIT*>(this)->tree.size() -1;
        while (idx >0) {
            res += tree[idx];
            idx -= idx & (-idx);
        }
        return res;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int N, M;
    cin >> N >> M;
    vector<ll> A(N);
    for(auto &x:A) cin >> x;
    
    // Initialize prefix sum and s[r] = S[r] mod M
    ll S =0;
    vector<int> s(N+1, 0);
    s[0] =0;
    
    for(int r=1; r<=N; ++r){
        S += A[r-1];
        s[r] = S % M;
    }
    
    // Initialize BIT
    BIT bit(M);
    bit.update(s[0]);
    
    ll total =0;
    ll sum_s_before = s[0];
    
    for(int r=1; r<=N; ++r){
        int sr = s[r];
        // Number of s[l] <= sr
        int count_le = bit.query(sr);
        // C2 = number of s[l] > sr
        ll C2 = (ll)r - count_le;
        // Compute total += r * s[r} - sum_s_before + M * C2
        total += (ll)r * sr - sum_s_before + (ll)M * C2;
        // Update sum_s_before
        sum_s_before += sr;
        // Update BIT with s[r}
        bit.update(sr);
    }
    
    cout << total;
}
