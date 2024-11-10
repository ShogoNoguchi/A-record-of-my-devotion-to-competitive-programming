#include <bits/stdc++.h>
using namespace std;

// BigIntクラスの定義
class BigInt {
public:
    static const uint64_t BASE = 1000000000000000000ULL; // 1e18
    vector<uint64_t> chunks; // 最下位チャンクから順に格納

    // 64ビット整数をBigIntに加算する関数
    void add(uint64_t x){
        if(chunks.empty()) chunks.push_back(0);
        uint64_t carry = x;
        size_t i = 0;
        while(carry > 0 && i < chunks.size()){
            __int128 temp = (__int128)chunks[i] + carry;
            if(temp >= BASE){
                chunks[i] = temp - BASE;
                carry = 1;
            }
            else{
                chunks[i] = temp;
                carry = 0;
            }
            i++;
        }
        if(carry > 0){
            chunks.push_back(carry);
        }
    }

    // BigIntを10進数の文字列に変換する関数
    string to_string_decimal() const{
        if(chunks.empty()) return "0";
        string s = "";
        // 最上位チャンクを取得
        vector<uint64_t> rev_chunks = chunks;
        int idx = rev_chunks.size()-1;
        while(idx > 0 && rev_chunks[idx] == 0) idx--;
        // 最上位チャンクを文字列に追加
        s += to_string(rev_chunks[idx]);
        // 残りのチャンクを18桁で埋めて追加
        for(int i = idx-1; i >=0; i--){
            string part = to_string(rev_chunks[i]);
            while(part.size() < 18){
                part = "0" + part;
            }
            s += part;
        }
        return s;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    long long N, M;
    cin >> N >> M;
    
    // 入力データの読み込み
    vector<pair<long long, long long>> stones(M);
    for(int i=0; i<M; i++) cin >> stones[i].first;
    for(int i=0; i<M; i++) cin >> stones[i].second;
    
    // 合計石数の計算
    long long total_stones =0;
    for(int i=0; i<M; i++) total_stones += stones[i].second;
    if(total_stones != N){
        cout << "-1\n";
        return 0;
    }
    
    // 初期位置でソート
    sort(stones.begin(), stones.end(), [&](const pair<long long, long long> &a, const pair<long long, long long> &b) -> bool{
        return a.first < b.first;
    });
    
    // 割り当て開始
    long long Y =1;
    BigInt total_sum;
    bool possible = true;
    for(int i=0; i<M; i++){
        long long X = stones[i].first;
        long long A = stones[i].second;
        Y = max(Y, X);
        if(Y + A -1 > N){
            possible = false;
            break;
        }
        // sum_for_this = A * Y + A*(A-1)/2 - A * X
        __int128 temp1 = (__int128)A * Y;
        __int128 temp2 = (__int128)A * (A -1) / 2;
        __int128 temp3 = (__int128)A * X;
        __int128 sum_for_this = temp1 + temp2 - temp3;
        // sum_for_thisをuint64_tにキャスト（sum_for_this <= 4e18 + 2e18 <= 6e18 < 1e19）
        uint64_t sum_term = (uint64_t)sum_for_this;
        total_sum.add(sum_term);
        Y += A;
    }
    
    if(!possible){
        cout << "-1\n";
    }
    else{
        cout << total_sum.to_string_decimal() << "\n";
    }
    
    return 0;
}
