#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// グローバル変数
int H, W, K;
vector<string> grid;
vector<pair<int, int>> empty_cells; // 空きマスのリスト
int E; // 空きマスの数
vector<vector<int>> adj; // 各空きマスの隣接空きマス
ll total_paths = 0;

// 訪問済みマスをビットマスクで管理
uint64_t visited1, visited2;

// 関数のプロトタイプ
ll dfs(int current, int steps_left);

// 訪問チェック
inline bool is_visited(int idx){
    if(idx < 64) return (visited1 >> idx) & 1ULL;
    else return (visited2 >> (idx - 64)) & 1ULL;
}

// 訪問マーク
inline void set_visited(int idx){
    if(idx < 64) visited1 |= (1ULL << idx);
    else visited2 |= (1ULL << (idx - 64));
}

// 訪問マーク解除
inline void unset_visited(int idx){
    if(idx < 64) visited1 &= ~(1ULL << idx);
    else visited2 &= ~(1ULL << (idx - 64));
}

// DFS関数
ll dfs(int current, int steps_left){
    if(steps_left == 0) return 1;
    ll res = 0;
    for(auto &next : adj[current]){
        if(!is_visited(next)){
            set_visited(next);
            res += dfs(next, steps_left -1);
            unset_visited(next);
        }
    }
    return res;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    // 入力の読み取り
    cin >> H >> W >> K;
    grid.resize(H);
    for(int i=0;i<H;i++) cin >> grid[i];
    
    // 空きマスのリスト作成
    for(int i=0;i<H;i++){
        for(int j=0;j<W;j++){
            if(grid[i][j] == '.'){
                empty_cells.emplace_back(i, j);
            }
        }
    }
    E = empty_cells.size();
    
    // 各空きマスの隣接リストを作成
    adj.resize(E, vector<int>());
    // 方向ベクトル（上下左右）
    vector<pair<int, int>> directions = { {-1,0}, {1,0}, {0,-1}, {0,1} };
    for(int idx=0; idx<E; idx++){
        int x = empty_cells[idx].first;
        int y = empty_cells[idx].second;
        for(auto &dir : directions){
            int nx = x + dir.first;
            int ny = y + dir.second;
            // グリッド内かつ空きマスであることを確認
            if(nx >=0 && nx < H && ny >=0 && ny < W && grid[nx][ny] == '.'){
                // 隣接する空きマスのインデックスを取得
                // 線形探索で対応
                // 事前にインデックスをマップしても良いが、H,Wが小さいためこれで問題ない
                for(int k=0; k<E; k++) {
                    if(empty_cells[k].first == nx && empty_cells[k].second == ny){
                        adj[idx].push_back(k);
                        break;
                    }
                }
            }
        }
    }
    
    // 各空きマスを出発点としてDFSを実行
    for(int s=0; s<E; s++){
        // 訪問マスクをリセット
        visited1 = visited2 = 0;
        // 出発点を訪問済みにマーク
        set_visited(s);
        // DFSを実行し、経路数を加算
        total_paths += dfs(s, K);
        // 訪問マスクを解除（実際には不要だが、次のループのためにクリア）
        unset_visited(s);
    }
    
    // 結果の出力
    cout << total_paths;
}

