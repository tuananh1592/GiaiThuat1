#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<queue>
#include<limits>
#include <algorithm>
using namespace std;
using ll = long long;
int INF = (int)1e9;

void Toprace() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        ll x, y;
        cin >> n >> x >> y;
        vector<ll> v(n);
        for (int i = 0;i < n;i++) {
            cin >> v[i];
        }
        ll Vmax = -INF;

        for (int i = 0;i+1 < n;i++) {
            Vmax = max(Vmax, v[i]);
        }
        ll vn = v[n-1];
        if (vn >= Vmax) {
            cout << "0"<< endl;
            continue;
        }
        /*✅ Gọi lại công thức chính xác: 
        Thời gian của đối thủ nhanh nhất: 𝑇(𝑜𝑝) = 𝑋/𝑣𝑚𝑎𝑥 
        Thời gian của bạn nếu dùng booster tốc độ Z trong 1 giây: 
        Nếu Z ≥ X → bạn về trong 1 giây 
        Nếu Z < X → bạn đi Z m trong 1 giây, còn lại (X - Z) m đi với tốc độ thường vn: 
        𝑇(𝑦𝑜𝑢)(𝑍) = 1 + ((𝑋 − 𝑍)/ 𝑣𝑛) ​
        ✅ Đặt Z = Y (booster tối đa), ta có: 𝑇(𝑦𝑜𝑢)(𝑌) = 1 + (𝑋 − 𝑌)/ 𝑣𝑛 
        Ta muốn điều kiện để bạn vẫn không thắng nổi, tức là: 
        𝑇(𝑦o𝑢)(𝑌) ≥ 𝑇(𝑜𝑝) ⇒ 1 + ((𝑋 − 𝑌0/ 𝑣𝑛) ≥ 𝑋/𝑣𝑚𝑎𝑥 
        ✅ Nhân 2 vế với vn * vmax để khử mẫu (bảo toàn dấu bất đẳng thức): 
        𝑣𝑚𝑎𝑥 * 𝑣𝑛 + 𝑣𝑚𝑎𝑥 * ( 𝑋 − 𝑌 ) ≥ 𝑣𝑛 * 𝑋
        Chuyển vế: 𝑣𝑚𝑎𝑥 * ( 𝑋 − 𝑌 ) ≥ 𝑣𝑛 * (𝑋 − 𝑣𝑚𝑎𝑥) */
        if (Vmax * (x - y) >= vn * (x - Vmax)) {
            cout << -1 << '\n';
        continue;
        }
        ll num = vn * (x - Vmax);
        ll k = num / Vmax + (num % Vmax != 0);      // ceil(num / vmax) thay cho ceil (num % Vmax != 0)
        cout << num / Vmax << endl;
        cout << k<<endl;
        ll Zmin = x + 1 - k;
        cout << Zmin << "\n";
    }
}