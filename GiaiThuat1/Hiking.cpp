#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<queue>
#include<stack>
#include<limits>
#include <algorithm>
using namespace std;

const int chia = 1000000007;

int dempop(int x) {
    int c = 0;
    while (x) {
        c += x & 1;
        x >>= 1;
    }
    return c;
}
long long chia_cong(long long a, long long b) {
    a += b;
    if (a >= chia) a -= chia;
    return a;
}

long long chia_nhan(long long a, long long b) {
    return (a % chia) * (b % chia) % chia;
}

void Hiking() {

    vector<long long> giatrithat(19, 1);
    for (int i = 1; i <= 18; i++) giatrithat[i] = giatrithat[i - 1] * i % chia;
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        long long x, c, d;
        cin >> n >> m >> x >> c >> d;

        vector<long long> a(n), b(m);
        for (int i = 0; i < n; i++) cin >> a[i];
        for (int j = 0; j < m; j++) cin >> b[j];

        vector<vector<long long>> tongA(n + 1);
        for (int i = 0;i < (1 << n);i++) {
            int dem = dempop(i);
            long long s = 0;
            for (int j = 0; j < n;j++) {
                if (i & (1 << j))s += a[j];
            }
            tongA[dem].push_back(s);
        }
        vector<vector<long long>>tongB(m + 1);
        for (int i = 0;i < (1 << m);i++) {
            int dem = dempop(i);
            long long s = 0;
            for (int j = 0; j < m;j++) {
                if (i & (1 << j))s += b[j];
            }
            tongB[dem].push_back(s);
        }

        for (int k = 0;k <= n;k++) sort(tongA[k].begin(), tongA[k].end());
        for (int k = 0;k <= m;k++) sort(tongB[k].begin(), tongB[k].end());

        long long dapan = 0;
        for (int k = 0;k <= n;k++) {
            for (int h = 0;h <= m;h++) {
                if (k + h == 0) continue;
                long long dem_cau = k + h - 1;
                long long tong_cau = dem_cau * x;

                long long cach_dat = giatrithat[k] * giatrithat[h] % chia;
                if (k == h)cach_dat = cach_dat * 2 % chia;
                if (abs(k - h) > 1)continue;

                auto& va = tongA[k];
                auto& vb = tongB[h];
                for (auto sa : va) {
                    long long nho = c - tong_cau - sa;
                    long long lon = d - tong_cau - sa;
                    auto n_nho = lower_bound(vb.begin(), vb.end(), nho);
                    auto n_lon = upper_bound(vb.begin(), vb.end(), lon);
                    long long dem_cap = distance(n_nho, n_lon);
                    dapan = chia_cong(dapan, chia_nhan(dem_cap, cach_dat));
                }
            }
        }
        cout << dapan << endl;
    }
}