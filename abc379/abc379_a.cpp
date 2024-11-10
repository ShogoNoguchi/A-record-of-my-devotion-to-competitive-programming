#include <bits/stdc++.h>
using namespace std;

int main(){
    int N;
    cin >> N;
    
    // 各桁を抽出
    int a = N / 100;        // 100の位
    int b = (N / 10) % 10;  // 10の位
    int c = N % 10;         // 1の位
    
    // b,c,a の順に並べた整数
    int first = b * 100 + c * 10 + a;
    
    // c,a,b の順に並べた整数
    int second = c * 100 + a * 10 + b;
    
    // 出力
    cout << first << " " << second;
}
