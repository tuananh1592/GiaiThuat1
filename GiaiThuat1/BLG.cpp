#include<iostream>
#include<string>
#include <cstring>
#include<vector>
#include<queue>
#include"Function.h"
using namespace std;
// Cặp tọa độ (x, y)
using pii = pair<int, int>;

// Hằng số khoảng cách vô cực
const int INF = numeric_limits<int>::max();

// Giới hạn tối đa
const int MAXRC = 1001;    // tối đa R, C ≤ 1000
const int MAXN = 50;

// 4 hướng di chuyển: xuống, lên, phải, trái
int dx[4] = { 1,-1,0,0 }, dy[4] = { 0,0,1,-1 };

// Mảng tĩnh cho bản đồ
char board[MAXRC][MAXRC];

// BFS từ (sx, sy) tính dist[x][y]
vector<vector<int>> bfs_from(int sx, int sy, int R, int C) {
    vector<vector<int>> dist(R, vector<int>(C, INF));
    queue<pii> q;
    q.push({ sx, sy });
    dist[sx][sy] = 0;

    while (!q.empty()) {
        pii front = q.front(); q.pop();
        int x = front.first, y = front.second;
        for (int k = 0;k < 4;k++) {
            int nx = x + dx[k], ny = y + dy[k];
            if (nx < 0 || nx >= R || ny < 0 || ny >= C) continue;
            if (board[nx][ny] == 'W') continue;
            if (dist[nx][ny] > dist[x][y] + 1) {
                dist[nx][ny] = dist[x][y] + 1;
                q.push({ nx,ny });
            }
        }
    }
    return dist;
}

void init() {
    int T;
    cin >> T;
    while (T--) {
        int R, C, N, rD, cD;
        cin >> R >> C >> N >> rD >> cD;
        rD--; cD--;

        // Đọc tọa độ pawns
        vector<pii> pawns(N);
        for (int i = 0;i < N;i++) {
            cin >> pawns[i].first >> pawns[i].second;
            pawns[i].first--; pawns[i].second--;
        }

        // *** Đọc bản đồ bằng mảng tĩnh ***
        for (int i = 0;i < R;i++) {
            for (int j = 0;j < C;j++) {
                cin >> board[i][j];
            }
        }
        // ***********************************

        // BFS từ đích
        auto d0 = bfs_from(rD, cD, R, C);
        for (const auto& row : d0) {
            for (const auto& val : row) {
                cout << val << ' ';
            }
            cout << '\n';
        }
        // Thu thập tường và minD0
        vector<pii> walls;
        vector<int> minD0;
        for (int i = 0;i < R;i++) {
            for (int j = 0;j < C;j++) {
                if (board[i][j] == 'W') {
                    walls.emplace_back(i, j);

                    int best = INF;
                    for (int k = 0;k < 4;k++) {
                        int ni = i + dx[k], nj = j + dy[k];
                        if (ni < 0 || ni >= R || nj < 0 || nj >= C) continue;
                        if (board[ni][nj == '.']) best = min(best, d0[ni][nj]);
                    }
                    minD0.push_back(best);
                }
            }
        }
        for (int x : minD0) {
            cout << x <<" ";
        }
        cout << "\n";
        for (const pii& p : walls) {
            cout << p.first + 1 << " "<<p.second + 1 << " "<<"|";
        }
        cout << "\n";
        cout << "\n";
        long long Dsum = 0;
        vector<long long> wallValue(walls.size(), 0);
        
        // Với mỗi pawn
        for (int i = 0;i < N;i++) {
                auto di = bfs_from(pawns[i].first, pawns[i].second, R, C);
                int Di = di[rD][cD];
                Dsum += Di;
            for (const auto& row1 : di) {
                for (const auto& val1 : row1) {
                    cout << val1 << ' ';
                }
                cout << '\n';
            }

            for (int j = 0; j < walls.size();j++) {
                int wx = walls[j].first, wy = walls[j].second;
                int bestEntry = INF;
                    for (int k = 0;k < 4;k++) {
                        int nxw = wx + dx[k], nyw = wy + dy[k];
                        if (nxw < 0 || nxw >= R || nyw < 0 || nyw >= C) continue;
                        if (board[nxw][nyw] == '.') bestEntry = min(bestEntry, di[nxw][nyw]);
                    }
                    int alt = bestEntry + 2 + minD0[j];
                    if (alt < Di) wallValue[j] += (Di-alt);
            }
            cout << '\n';
        }

        long long Net = 0;
        for (auto v : wallValue) Net += v;
        cout << Dsum << " " << Net << "\n";
    }
}