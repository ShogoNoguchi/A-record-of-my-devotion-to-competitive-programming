#include <bits/stdc++.h>
using namespace std;

// BIT（Fenwick Tree）の実装
struct BIT {
    int size;
    vector<int> tree;

    BIT(int n) : size(n), tree(n + 1, 0) {}

    // 位置 idx に value を加える
    void update(int idx, int value = 1) {
        while (idx <= size) {
            tree[idx] += value;
            idx += idx & (-idx);
        }
    }

    // 1からidxまでの累積和を取得
    int query(int idx) const {
        int res = 0;
        int i = idx;
        while (i > 0) {
            res += tree[i];
            i -= i & (-i);
        }
        return res;
    }

    // [l, r] の累積和を取得
    int range_query(int l, int r) const {
        if (l > r) return 0;
        return query(r) - query(l - 1);
    }
};

// クエリを格納する構造体
struct Query {
    int l;
    int r;
    int id;
};

// メイン関数
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, Q;
    cin >> N >> Q;

    // ビルの高さを1-basedで読み込む
    vector<int> H(N + 1);
    for(int i=1; i<=N; ++i){
        cin >> H[i];
    }

    // L_sを計算するためのスタック
    vector<int> L(N + 1, 0);
    stack<int> st;
    for(int s=1; s<=N; ++s){
        while(!st.empty() && H[st.top()] <= H[s]){
            st.pop();
        }
        if(st.empty()){
            L[s] = 0;
        }
        else{
            L[s] = st.top();
        }
        st.push(s);
    }

    // クエリの読み込み
    vector<Query> queries(Q);
    for(int i=0; i<Q; ++i){
        cin >> queries[i].l >> queries[i].r;
        queries[i].id = i;
    }

    // クエリをlの昇順にソート
    sort(queries.begin(), queries.end(), [&](const Query &a, const Query &b) -> bool{
        if(a.l != b.l) return a.l < b.l;
        return a.r < b.r;
    });

    // ビルsを(L_s, s)のペアとして格納し、L_sの昇順にソート
    vector<pair<int, int>> s_sorted;
    s_sorted.reserve(N);
    for(int s=1; s<=N; ++s){
        s_sorted.emplace_back(L[s], s);
    }
    sort(s_sorted.begin(), s_sorted.end());

    // BITの初期化
    BIT bit(N);

    // クエリの処理
    vector<long long> answers(Q, 0);
    int s_ptr = 0;
    for(int q=0; q<Q; ++q){
        int current_l = queries[q].l;
        int current_r = queries[q].r;

        // L_s <= current_l となるsをBITに追加
        while(s_ptr < N && s_sorted[s_ptr].first <= current_l){
            int s = s_sorted[s_ptr].second;
            bit.update(s, 1);
            s_ptr++;
        }

        // s > r かつ L_s <= l を満たすsの数をカウント
        if(current_r >= N){
            answers[queries[q].id] = 0;
        }
        else{
            int total = bit.query(N);
            int up_to_r = bit.query(current_r);
            answers[queries[q].id] = (long long)(total - up_to_r);
        }
    }

    // 答えを元のクエリ順に出力
    for(int i=0; i<Q; ++i){
        cout << answers[i] << "\n";
    }

    return 0;
}
