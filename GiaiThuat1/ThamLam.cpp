#include<iostream>  
#include<vector>
#include<algorithm>
#include<functional>
#include"Function.h"  
using namespace std;  

vector<int> neg;  
vector<int> pos;  

void Greedy() {  
   int t;  
   cin >> t;  
   while (t--) {  
       pos.clear();  
       neg.clear();  
       int n, k;  
       cin >> n >> k;  
       int x;  
       for (int i = 0; i < n; i++) {  
           cin >> x;  
           if (x > 0) {  
               pos.push_back(x);  
           }  
           if (x < 0) {  
               neg.push_back(-x);  
           }  
       }  
       sort(pos.begin(), pos.end(), greater<int>());
       sort(neg.begin(), neg.end(),greater<int>());

       int ans = 0;  
       for (int i = 0; i < pos.size(); i += k) {  
           ans += 2 * pos[i];  
       }  
       for (int i = 0; i < neg.size(); i += k) {  
           ans += 2 * neg[i];  
       }  

       cout << ans << endl;  
   }  
}

void greedy2() {
    int t;
    vector<int>adj[MAX];
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int k;
        cin >> k;
        int x, y;
        for (int i = 0;i < n;i++) {
            cin >> x >> y;
            adj[x].push_back(y);
            adj[y].push_back(x);
        }

    }
}