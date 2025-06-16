#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<queue>
#include<limits>
#include <algorithm>
using namespace std;

void StringReversal() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<string> s(n + 1), r(n + 1);
        for (int i = 1;i <= n;i++) {
            cin >> s[i];
            r[i] = s[i];
            reverse(r[i].begin(), r[i].end());
        }

        bool sosanh[152][2][2];
        for (int i = 1;i < n;i++) {
            for (int j = 0;j < 2;j++) {
                for (int k = 0;k < 2;k++) {
                    const string& a = (j == 0 ? s[i] : r[i]);
                    const string& b = (k == 0 ? s[i + 1] : r[i + 1]);
                    sosanh[i][j][k] = (a <= b);
                }
            }
        }

        bool timkiem[152][2];
        timkiem[n][0] = timkiem[n][1] = true;
        for (int i = n - 1; i >= 1; i--) {
            for (int j = 0; j < 2; j++) {
                bool ok = false;
                for (int k = 0; k < 2; k++) {
                    if (sosanh[i][j][k] && timkiem[i + 1][k]) {
                        ok = true;
                        break;
                    }
                }
                timkiem[i][j] = ok;
            }
        }

        string dapan;
        dapan.reserve(n);
        int trangthai = -1;
        if (timkiem[1][0]) {
            dapan.push_back('0');
            trangthai = 0;
        }
        else {
            dapan.push_back('1');
            trangthai = 1;
        }
        for (int i = 2; i <= n; i++) {
            if (sosanh[i - 1][trangthai][0] && timkiem[i][0]) {
                dapan.push_back('0');
                trangthai = 0;
            }
            else {
                dapan.push_back('1');
                trangthai = 1;
            }
        }
        cout << dapan << endl;
    }
}