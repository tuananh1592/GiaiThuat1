#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<queue>
#include <stack>
#include<limits>
#include <algorithm>
using namespace std;

void subset() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<long long> v(n + 1);
        for (int i = 1; i <= n; i++) {
            cin >> v[i];
        }
        vector<int> p(n + 1);
        int goc = 0;
        for (int i = 1; i <= n; i++) {
            cin >> p[i];
            if (p[i] == 0) goc = i;
        }
        vector<vector<int>> nutcon(n + 1);
        for (int i = 1; i <= n; i++) {
            if (p[i] != 0) nutcon[p[i]].push_back(i);
        }

        vector<long long> dp0(n + 1), dp1(n + 1);
        stack<pair<int, int>> stak;
        stak.emplace(goc, 0);

        while (!stak.empty()) {
            int u = stak.top().first;
            int& nutconindex = stak.top().second;
            if (nutconindex < (int)nutcon[u].size()) {
                int c = nutcon[u][nutconindex++];
                stak.emplace(c, 0);
            }
            else {
                long long tong_dp0_den_dp1 = 0;
                long long duong_goc = 0;
                long long khac_nhat = numeric_limits<long long>::min();
                bool pos_khac = false;
                for (int c : nutcon[u]) {
                    tong_dp0_den_dp1 += dp0[c];
                    long long a = dp1[c];
                    long long b = dp0[c];
                    duong_goc += max(a, b);
                    long long khac_biet = a - b;
                    if (khac_biet > khac_nhat)khac_nhat = khac_biet;
                    if (khac_biet > 0) pos_khac = true;
                }
                dp1[u] = v[u] + tong_dp0_den_dp1;

                if (nutcon[u].empty()) {
                    dp0[u] = 0;
                }
                else {
                    if (pos_khac) {
                        dp0[u] = duong_goc;
                    }
                    else {
                        dp0[u] = duong_goc + khac_nhat;
                    }
                }
                stak.pop();
            }
        }
        long long dapan = max(dp1[goc], dp0[goc]);
        cout << dapan << endl;
    }
}