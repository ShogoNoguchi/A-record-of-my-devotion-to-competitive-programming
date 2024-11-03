#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int N;
    cin >> N;
    vector<long long> A(N);
    for(auto &x : A) cin >> x;
    
    // 座標圧縮
    vector<long long> sorted_A = A;
    sort(sorted_A.begin(), sorted_A.end());
    sorted_A.erase(unique(sorted_A.begin(), sorted_A.end()), sorted_A.end());
    
    // 各A[i]を圧縮後のインデックスにマッピング
    // 最後に出現した位置を保持する配列
    int M = sorted_A.size();
    vector<int> last_pos(M, -1);
    vector<int> B(N, -1);
    
    for(int i = 0; i < N; ++i){
        // A[i]の圧縮後インデックスを取得
        int idx = lower_bound(sorted_A.begin(), sorted_A.end(), A[i]) - sorted_A.begin();
        
        // 前に同じ値があればその位置をB[i]に設定
        if(last_pos[idx] != -1){
            B[i] = last_pos[idx];
        }
        // 現在の位置を更新（1-based index）
        last_pos[idx] = i + 1;
    }
    
    // 結果を出力
    for(int i = 0; i < N; ++i){
        if(i > 0) cout << ' ';
        cout << B[i];
    }
    cout << '\n';
}
