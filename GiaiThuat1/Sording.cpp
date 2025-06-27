#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<queue>
#include<stack>
#include<limits>
#include <algorithm>
using namespace std;

//Tìm kiếm số nuyên tốt gần n nhất 
using ll = long long;
bool isPrime(ll n) { // chir ddeer check xem có phải số nguyên tố ko thôi
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    ll r = static_cast<ll>(sqrt(n));
    for (ll i = 3; i <= r; i += 2) {
        if (n % i == 0)
            return false;
    }
    return true;
}

// Tìm số nguyên tố p sao cho |p - n| nhỏ nhất
ll nearestPrime(ll n) { // đoạn này tìm số nguyên tốt gần nhất 
    if (n <= 2) return 2;
    for (ll d = 0; ; ++d) {
        ll low = n - d;
        ll high = n + d;
        if (low >= 2 && isPrime(low))
            return low;
        if (isPrime(high))
            return high;
    }
}
// Het tim so nguyen gan nhat

// tra ve vector chua cac uoc cua n, sap xep tang dan bài này là tìm các ước nhé 
vector<ll> timUoc(ll n) {
    vector<ll> nho, lon;
    ll r = floor(sqrt((long double)n));
    for (ll i = 1; i <= r; ++i) {
        if (n % i == 0) {
            nho.push_back(i);
            if (i != n / i)
                lon.push_back(n / i);
        }
    }
    // chen cac uoc lon (dao nguoc) vao sau cac uoc nho
    nho.insert(nho.end(), lon.rbegin(), lon.rend());
    return nho;
}
void initTimUoc() {
    ll n;
    cin >> n;
    auto m = timUoc(n);
    for (ll u : m) {
        cout << u << ' ';
    }
}
// Het Tim Uoc