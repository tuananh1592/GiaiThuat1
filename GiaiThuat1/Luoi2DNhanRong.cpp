#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<queue>
#include<stack>
#include<limits>
#include<algorithm>
#include"Function.h"
using namespace std;
using ll = long long;
using namespace std;
using ll = long long;

int n;
vector<string> board;           // board[r][c]
vector<int> layer;              // layer[u] = lớp của ô u
vector<vector<int>> adj;        // adj[u] = danh sách ô kề u
vector<bool> visited;
string cur;
string best_min, best_max;

inline int id(int r, int c) { return r * n + c; }
inline bool inside(int r, int c) {
    return r >= 0 && r < n && c >= 0 && c < n;
}

// u = id ô hiện tại, par = ô trước đó (flattened index), depth = độ sâu (số ô đã chọn)
void dfs(int u, int par, int depth) {
    visited[u] = true;
    cur.push_back(board[u / n][u % n]);

    if (depth == n * n) {
        // đã chọn đủ n^2 ô, cập nhật min/max
        best_min = min(best_min, cur);
        best_max = max(best_max, cur);
    }
    else {
        // thu thập các ô kề chưa visited
        vector<int> cand;
        for (int v : adj[u]) {
            if (v != par && !visited[v])
                cand.push_back(v);
        }
        // tìm layer lớn nhất trong các ứng viên
        int best_layer = -1;
        for (int v : cand)
            best_layer = max(best_layer, layer[v]);

        // lọc chỉ giữ các v có layer == best_layer
        vector<int> nexts;
        for (int v : cand) {
            if (layer[v] == best_layer)
                nexts.push_back(v);
        }

        // đệ quy cho mỗi nhánh
        for (int v : nexts) {
            dfs(v, u, depth + 1);
        }
    }

    // backtrack
    cur.pop_back();
    visited[u] = false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        board.resize(n);
        for (int i = 0; i < n; i++)
            cin >> board[i];

        int N = n * n;
        layer.assign(N, 0);
        adj.assign(N, {});
        visited.assign(N, false);

        // 1) Tính layer[u]
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                int u = id(r, c);
                layer[u] = min({ r, c, n - 1 - r, n - 1 - c });
            }
        }

        // 2) Xây đồ thị adjacency
        int dr[4] = { -1, 1, 0, 0 };
        int dc[4] = { 0, 0, -1, 1 };
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                int u = id(r, c);
                for (int k = 0; k < 4; k++) {
                    int nr = r + dr[k], nc = c + dc[k];
                    if (inside(nr, nc)) {
                        adj[u].push_back(id(nr, nc));
                    }
                }
            }
        }

        // 3) Khởi tạo và chạy DFS từ 4 góc
        cur.clear();
        best_min = string(N, char('Z' + 1));
        best_max = string(N, char('A' - 1));

        vector<int> corners = { id(0,0), id(0,n - 1), id(n - 1,0), id(n - 1,n - 1) };
        for (int start : corners) {
            dfs(start, -1, 1);
        }

        // 4) In kết quả: max trước, rồi min
        cout << best_max << ' ' << best_min << "\n";
    }
    return 0;
}