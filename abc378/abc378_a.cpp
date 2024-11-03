#include <bits/stdc++.h>
using namespace std;

int main(){
    // 入力を格納する配列
    int A[4];
    for(int &x : A) cin >> x;
    
    // 色の出現回数をカウントする配列（色は1から4）
    int count[5] = {0}; // インデックス0は使用しない
    for(int i = 0; i < 4; ++i){
        count[A[i]]++;
    }
    
    // 各色ごとにペアの数を計算し、合計する
    int operations = 0;
    for(int color = 1; color <=4; ++color){
        operations += count[color] / 2;
    }
    
    // 結果を出力
    cout << operations;
}
