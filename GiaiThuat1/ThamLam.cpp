#include<iostream>  
#include"Function.h"  
using namespace std;  
const int NMax = 200000;  
vector<int> neg;  
vector<int> pos;  

void Quicksort_decre(vector<int>& arr, int l, int r) {  
   if (l > r) return;  
   int center = arr[(l + r) / 2];  
   int i = l, j = r;  
   while (i <= j) {  
       while (arr[i] > center) i++;  
       while (arr[j] < center) j--;  
       if (i <= j) {  
           int swap = arr[i];  
           arr[i] = arr[j];  
           arr[j] = swap;  
           i++;  
           j--;  
       }  
   }  
   if (l < j) Quicksort_decre(arr, l, j);  
   if (i < r) Quicksort_decre(arr, i, r);  
}  

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
       Quicksort_decre(pos, 0, pos.size() - 1);  
       Quicksort_decre(neg, 0, neg.size() - 1);  

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