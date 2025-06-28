#include"Function.h"
#include<algorithm>
#include<cstring>
#include<iostream>
#include<limits>
#include<queue>
#include<stack>
#include<string>
#include<vector>
using namespace std;

void LIS() {
	int n; cin >> n;
	int a[1001];
	int l[1001];
	for (int i = 0; i < n;i++) {
		cin >> a[i];
	}
	for(int i= 0;i< n;i++) {
		l[i] = 1;
		for (int j = 0;j < i;j++) {
			if (a[i] > a[j]){
				l[i]=max(l[i],l[j]+1);
				}
		}
	}
	cout << *max_element(l, l + n) << endl;
}

void dp_tree(int u, int par, vector<int> adj[MAX], int a[MAX], int f[MAX][2]) {
	f[u][0] = 0;
	f[u][1] = a[u];

	//cout << "\n--- Dang xu ly dinh: " << u << " (cha: " << par << ") ---\n";
	//cout << "Khoi tao: f[" << u << "][0] = " << f[u][0] << ", f[" << u << "][1] = " << f[u][1] << "\n";

	for (int v : adj[u]) {
		if (v != par) {
			dp_tree(v, u, adj, a, f);

			//cout << "  Xet con v = " << v << "\n";
			//cout << "    f[" << v << "][0] = " << f[v][0] << ", f[" << v << "][1] = " << f[v][1] << "\n";

			f[u][0] += max(f[v][0], f[v][1]);
			f[u][1] += f[v][0];

			//cout << "    Cap nhat f[" << u << "][0] = " << f[u][0] << "\n";
			//cout << "    Cap nhat f[" << u << "][1] = " << f[u][1] << "\n";

			//cout << "    --> f[1][1] sau khi them f[" << v << "][0] = " << f[v][0] << " => " << f[1][1] << "\n";
		}
	}

	//cout << "Ket thuc dinh " << u << ": f[" << u << "][0] = " << f[u][0] << ", f[" << u << "][1] = " << f[u][1] << "\n";
}


void init_dp_tree() {
	vector<int> adj[MAX];//mới là nơi lưu danh sách các đỉnh kề nhau
	//1 2
	//1 3
	//2 4
	//2 5
	// đỉnh 1 kề với 2 và 3; đỉnh 2 kề với 4 và 5.
	int a[MAX]; // a[] lưu giá trị của đỉnh, không phải cạnh.
	int f[MAX][2]; 
	int n;
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> a[i];

	for (int i = 1; i < n; ++i) {
		int u, v; cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	dp_tree(1, -1, adj, a, f);
	cout <<max(f[1][0], f[1][1]) << "\n";
}



int INF4 = (int)1e9 + 7;
int a4[MAX], f[MAX][MAX], treesize[MAX], Gij[MAX], Gij_1[MAX];
vector<int> adj4[MAX];
int k, kDP[MAX];
template<class X, class Y>
bool maximent(X& x, const Y& y) {
	if (x < y) { x = y; return true; }
	return false;
}
void dfs_Knapsack(int u, int par) {
	//bc1: Ktra dinh
	for (int v : adj4[u]) if (v != par) { dfs_Knapsack(v, u); }

	//bc2: Khoi Tao Gi,j
	for (int j = 0;j <= treesize[u];j++) { // nham Gij thanh fuk
		Gij[j] = -INF4;
	}
	Gij[0] = 0;
	treesize[u] = 0;

	//bc3: Tinh maximen cua Gi,j+k vs Gj+f[v][k]
	for (int v : adj4[u]) if(v!=par){ // thieu if(v!=par)
		for (int j = 0;j <= treesize[u];j++) {
			Gij_1[j] = Gij[j];
			Gij[j] = -INF4;
		}

		for (int j = 0;j <= treesize[u];j++) {
			if (Gij_1[j] < -INF4 / 2)continue;
			for (int k = 0;k <= treesize[v];k++) {
				if(f[v][k]<-INF4/2)continue;
				maximent(Gij[j + k], Gij_1[j] + f[v][k]);
			}
		}
		treesize[u] += treesize[v];
	}

	//bc4:Tinh fui+1 = au + Gij
	for (int i = 0;i <= treesize[u];i++) {
		f[u][i + 1] = Gij[i] + a4[u];
	}
	f[u][0] = 0;
	treesize[u]++;
}
void Knapsack() {
	int n; cin >> n >> k;
	for (int i = 1;i <= n;i++) {
		cin >> a4[i];
		adj4[i].clear();
	}

	int u, v;
	for (int i = 1;i < n;i++) {
		cin >> u >> v;
		adj4[u].push_back(v);
		adj4[v].push_back(u);
	}

	for (int u = 1; u <= n;u++) {
		for (int k = 1; k <= n;k++) {
			f[u][k] = -INF4;
		}
	}
	
	for (int i = 1;i <= k; i++) {
		cin >> kDP[i];
	}
	dfs_Knapsack(1, 0);

	for (int i = 1;i <= k;i++) {
		int ans = -INF4;
		for (int u = 1;u <= n;u++) {
			if (treesize[u] >= kDP[i]) {
				maximent(ans, f[u][kDP[i]]);
			}
		}
		cout << kDP[i] <<" dinh: " << ans <<endl; // chu y dau ngoac va k==n 
	}
}

void DP_TimtapConTrongMang() {
	int n, target;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	cin >> target;

	// dp[s] = true nếu có tập con đạt tổng s
	vector<char> dp(target + 1, 0);
	// parent[s] = chỉ số i trong a[] dùng để bật dp[s] lần đầu
	vector<int> parent(target + 1, -1);

	dp[0] = 1;  // tập rỗng cho tổng 0

	for (int i = 0; i < n; i++) {
		int x = a[i];
		// lùi s từ target xuống x để mỗi a[i] dùng đúng 1 lần
		for (int s = target; s >= x; s--) {
			// nếu chưa từng bật dp[s] và dp[s-x] đang bật
			if (!dp[s] && dp[s - x]) {
				dp[s] = 1;
				parent[s] = i;  // lưu rằng để có được s ta dùng a[i]
			}
		}
	}

	if (!dp[target]) {
		cout << "false\n";
	}

	// Ngược dấu parent để lấy ra các phần tử
	vector<int> subset;
	int s = target;
	while (s > 0) {
		int i = parent[s];
		subset.push_back(a[i]);
		s -= a[i];
	}
	// subset chứa các phần tử, có thể đảo lại nếu muốn tăng dần thứ tự
	reverse(subset.begin(), subset.end());

	// In kết quả
	cout << "true\n";
	cout << "Subset of sum " << target << ": ";
	for (int v : subset) {
		cout << v << " ";
	}
	cout << "\n";
}

void DpKtraXemCoTapConKo() {
	int n, target;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	cin >> target;

	// dp[j] = có thể hay không có tập con đạt tổng j
	vector<char> dp(target + 1, 0);
	dp[0] = 1;

	for (int x : a) {
		// duyệt ngược để mỗi phần tử chỉ dùng 1 lần
		for (int s = target; s >= x; s--) {
			if (dp[s - x]) dp[s] = 1;
		}
	}

	cout << (dp[target] ? "true" : "false");
}