#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<queue>
#include<limits>
#include<algorithm>
using namespace std;
string solve_test(int n, const vector<string>& s) {
    vector<string>r(n + 1);
    for (int i = 1;i <= n;i++) {
        r[i] = s[i];
        reverse(r[i].begin(), r[i].end());
    }

    //Bc1 gan gia tri tai 1
    string bitmask0 = "0", UnRev = s[1];
    string bitmask1 = "1", Rev = r[1];
    string INF(n + 1, '2');
    //Bc2: So sanh trc sau
    for (int i = 2;i <= n;i++) {
        string bitmask0_new = INF, UnRevNew;
        string bitmask1_new = INF, RevNew;

        //Bc2.1 ss ko dao vs ko dao sau
        if (UnRev <= s[i]) {
            string status00 = bitmask0 + '0';
            if (status00 <= bitmask0_new) {
                bitmask0_new = status00;
                UnRevNew = s[i];
            }
        }
        //Bc2.2 ss dao vs ko dao sau
        if (Rev <= s[i]) {
            string status01 = bitmask1 + '0';
            if (status01 <= bitmask0_new) {
                bitmask0_new = status01;
                UnRevNew = s[i];
            }
        }

        //Bc2.3 ss ko dao vs dao sau
        if (UnRev <= r[i]) {
            string status10 = bitmask0 + '1';
            if (status10 <= bitmask1_new) {
                bitmask1_new = status10;
                RevNew = r[i];
            }
        }
        //Bc2.4 ss dao vs  dao sau
        if (Rev <= r[i]) {
            string status11 = bitmask1 + '1';
            if (status11 <= bitmask1_new) {
                bitmask1_new = status11;
                RevNew = r[i];
            }
        }
        UnRev = UnRevNew, bitmask0 = bitmask0_new;
        Rev = RevNew, bitmask1 = bitmask1_new;
    }
    //Bc4: min
    string ans;
    ans = min(bitmask0, bitmask1);
    return ans;
}
void StringReversal() {
    int T;
    cin >> T;
    while (T--) {
        int n;cin >> n;
        vector<string>s(n + 1);
        for (int i = 1;i <= n;i++) {
            cin >> s[i];
        }
        cout << solve_test(n, s)<<endl;
    }
}


string solve_test2(int n, const vector<string>& s) {
    vector<string>r(n + 1);
    for (int i = 1;i <= n;i++) {
        r[i] = s[i];
        sort(r[i].begin(), r[i].end());
    }

    //Bc1 gan gia tri tai 1
    string bitmask0 = "0", UnSort = s[1];
    string bitmask1 = "1", Sort = r[1];
    string INF(n + 1, '2');
    //Bc2: So sanh trc sau
    for (int i = 2;i <= n;i++) {
        string bitmask0_new = INF, UnSortNew;
        string bitmask1_new = INF, SortNew;

        //Bc2.1 ss ko dao vs ko dao sau
        if (UnSort <= s[i]) {
            string status00 = bitmask0 + '0';
            if (status00 <= bitmask0_new) {
                bitmask0_new = status00;
                UnSortNew = s[i];
            }
        }
        //Bc2.2 ss dao vs ko dao sau
        if (Sort <= s[i]) {
            string status01 = bitmask1 + '0';
            if (status01 <= bitmask0_new) {
                bitmask0_new = status01;
                UnSortNew = s[i];
            }
        }

        //Bc2.3 ss ko dao vs dao sau
        if (UnSort <= r[i]) {
            string status10 = bitmask0 + '1';
            if (status10 <= bitmask1_new) {
                bitmask1_new = status10;
                SortNew = r[i];
            }
        }
        //Bc2.4 ss dao vs  dao sau
        if (Sort <= r[i]) {
            string status11 = bitmask1 + '1';
            if (status11 <= bitmask1_new) {
                bitmask1_new = status11;
                SortNew = r[i];
            }
        }
        UnSort = UnSortNew, bitmask0 = bitmask0_new;
        Sort = SortNew, bitmask1 = bitmask1_new;
    }
    //Bc4: min
    string ans;
    //cout << bitmask0 << ' ' << bitmask1<<endl;
    ans = min(bitmask0, bitmask1);
    if (ans == INF) ans = "IMPOSSIBLE";
    return ans;
}
void StringSort() {
    int t;
    cin >> t;
    while (t--) {
        int n;cin >> n;
        vector<string>s(n + 1);
        for (int i = 1;i <= n;i++) {
            cin >> s[i];
        }
        cout << solve_test2(n, s) << endl;
    }
}