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

int INF1 = (int)1e9;
ll f[MAX][2];
ll a[MAX];
vector<ll> adj[MAX];


void dfs(int u, int par) {
    //bc1
    f[u][0] = 0;
    f[u][1] = a[u];
    int best_diff = numeric_limits<int>::min();
    int diff = numeric_limits<int>::min();
    bool has_pos = false;
    //bc2 tham dinh va cap nhat gia tri
    for (int v : adj[u]) if (v != par) {
        dfs(v, u);
        f[u][1] += f[v][0];
        f[u][0] += max(f[v][0], f[v][1]);
        
        int x0 = f[v][0], x1 = f[v][1];
        diff = x1 - x0;
        best_diff = max(best_diff, diff);
        if (diff > 0) has_pos = true;
    }

    bool isLeaf = true;
    for (int v : adj[u]) if (v != par) { isLeaf = false;break; }

    if (isLeaf == true) f[u][0] = 0;
    else f[u][0] = (has_pos == true) ? f[u][0] : (f[u][0] + best_diff);
}
void int_goodnode() {

    int T;
    cin >> T;
    while (T--) {
        int n; cin >> n;
        for (int i = 1;i <= n;i++) {
            cin >> a[i];
            adj[i].clear();
        }

        
        int u, q;
        for (int i = 1;i <= n;i++) {
            cin >> q;
            if (q == 0) u = i;
            else adj[q].push_back(i);
        }

        dfs(u, 0);
        cout << max(f[u][0], f[u][1])<<endl;
    }
}

void dfs22(int u, int par) {
    //bc1: như bthg
    f[u][0] = 0;
    f[u][1] = a[u];


    vector<int> diff;
    int Leafcnt = 0;
    // bc 2: như bthg
    for (int v : adj[u]) if (v != par) {
        dfs22(v, u);
        f[u][1] += f[v][0];
        f[u][0] += max(f[v][0], f[v][1]);
        // khác biệt mình lưu vào 1 biến mình sẽ lưu vào 1 vector 
        int x0 = f[v][0], x1 = f[v][1];
        diff.push_back(x1 - x0);
        Leafcnt++;
    }

    if (Leafcnt >= 3) {// từ vector đó mình lấy ra và so sánh với 0
        sort(diff.rbegin(), diff.rend());
        int poscnt = 0;
        for (int i : diff) if (i > 0) { poscnt++; }

        if(poscnt >= 3) {
            // baseline đã đủ 2 con tốt → KHÔNG làm gì thêm
        }
        else if (poscnt == 2) {
            // chỉ 1 con tốt → ép chọn thêm con đứng thứ nhì
            f[u][0] += diff[1];
        }
        else if (poscnt == 1) { f[u][0] += diff[0] + diff[1]; }
        else { // poscnt == 0
            // không con nào tốt → ép chọn 2 con nhất nhì
            f[u][0] += diff[0] + diff[1] + diff[2];
        }
    }
}
void init_goodnode2() {
    int n;
    cin >> n;
    for (int i = 1;i <= n;i++) {
        cin >> a[i];
        adj[i].clear();
    }
    int u, q;
    for (int i = 1;i <= n;i++) {
        cin >> q;
        if (q == 0) u = i;
        else adj[q].push_back(i);
    }
    dfs22(u, 0);
    cout << max(f[u][1], f[u][0]) << endl;
}

void dfs23(int u, int par) {
    f[u][1] = a[u];
    for (int v : adj[u]) if (v != par) {
        dfs23(v, u);
        f[u][1] += max(0ll, f[v][1]);
    }
}
void init_goodnode3() {
    int n;
    cin >> n;
    for (int i = 1;i <= n;i++) {
        cin >> a[i];
        adj[i].clear();
    }
    int u, v;
    for (int i = 1;i < n;i++) {
        cin >> u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs23(1, 0);
    ll MaxDP = -INF1;
    for (int u = 2;u <= n;u++) {
        MaxDP = max(MaxDP, f[u][1]);
    }
    cout << MaxDP;
}   