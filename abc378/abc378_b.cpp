#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int N;
    cin >> N;
    // 1-based indexing
    vector<pair<ll, ll>> garbage(N+1);
    for(int i=1;i<=N;i++) cin >> garbage[i].first >> garbage[i].second;
    int Q;
    cin >> Q;
    while(Q--){
        ll t_j, d_j;
        cin >> t_j >> d_j;
        ll q = garbage[t_j].first;
        ll r = garbage[t_j].second;
        ll d_mod_q = d_j % q;
        ll delta = (r - d_mod_q + q) % q;
        ll x = d_j + delta;
        cout << x << "\n";
    }
}

