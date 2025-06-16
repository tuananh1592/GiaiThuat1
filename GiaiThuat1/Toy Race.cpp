#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<queue>
#include<limits>
#include <algorithm>
using namespace std;

long long chialamtron(long long x, long long y) {
    if (x > 0) return (x + y - 1) / y;
    else return x / y;
}

void Toprace() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        long long x, y;
        cin >> n >> x >> y;
        vector<long long> v(n);
        for (int i = 0;i < n;i++) {
            cin >> v[i];
        }
        // Tim toc do lon nhat cua doi thu
        long long vmax = 0;
        for (int i = 0; i < n - 1;i++) {
            vmax = max(vmax, v[i]);
        }

        long long vn = v[n - 1];
        //1)
        if (vn >= vmax) {
            cout << 0 << endl;
            continue;
        }
        //2)
        if (vmax * (x - y) >= vn * (x - vmax)) {
            cout << -1 << endl;
            continue;
        }
        //3)
        long long s = vn * (x - vmax);
        long long k = chialamtron(s, vmax);
        long long zmin = x + 1 - k;
        cout << zmin << endl;
    }
}