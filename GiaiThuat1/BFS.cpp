#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<queue>
#include<limits>
#include "Function.h"
using namespace std;

int dx1[4] = { 1,-1,0,0 }, dy1[4] = { 0,0,1,-1 };
using pii = pair<int, int>;
int n1, m, s, t, u, v;
char a[1001][1001];
int d[1001][1001]; // luu so bc di tu o bắt đầu đến ô i,j

void bfs(int i, int j) {
	queue<pii> q;
	q.push({ i,j }); // push cặp tọa độ i j 
	a[i][j] = 'o';
	d[i][j] = 0;
	while (!q.empty()) {
		pii top = q.front();
		q.pop();
		// duyet cac dinh ke
		for (int k = 0;k < 4;k++) {
			int i1 = top.first + dx1[k];
			int j1 = top.second + dy1[k];
			if (i1 < 0 || i1 >= n1 || j1 < 0 || j1 >= m) continue;
				if(a[i1][j1] != 'x'){
				d[i1][j1] = d[top.first][top.second] + 1;
				if (a[i1][j1] == 'B') return;
				q.push({ i1,j1 });
				a[i1][j1] = 'o';
			}
		}
	}
}

void inpo() {
	cin >> n1 >> m;
	for (int i = 0;i < n1;i++) {
		for (int j = 0;j < m;j++) {
			cin >> a[i][j];
			if (a[i][j] == 'A') {
				s = i; t = j;
			}
			else if (a[i][j] == 'B') {
				u = i; v = j;
			}
		}
	}
	bfs(s, t);
	if (!d[u][v]) {
		cout << "Ohno";
	}
	else cout << d[u][v] << endl;
}

const int Rmax = 1001, Cmax = 1001;
char board1[Rmax][Cmax];
const int INF2 = numeric_limits<int>::max();
using pii2 = pair<int, int>;
vector<vector<int>> bfs2(int nx, int ny, int r, int c) {
	vector<vector<int>> dist(r, vector<int>(c, INF2));
	queue<pii2> q;
	q.push({ nx,ny });
	for (int i = 0;i < r;i++) {
		for (int j = 0;j < c;j++) {
			if(board1[i][j] == 'W') dist[i][j] = 0;
			else dist[i][j] = INF2;
		}
	}
	dist[nx][ny] = 0;
	while (!q.empty()) {
		pii2 top = q.front();q.pop();
		int x = top.first, y = top.second;
		for (int k = 0;k < 4;k++) {
			int nx = x + dx1[k], ny = y + dy1[k];
			if (nx<0 || nx>=r || ny<0 || ny>=c) continue;
			if (board1[nx][ny] == 'W')continue;
			if (dist[nx][ny] > dist[x][y] + 1) {
				dist[nx][ny] = dist[x][y] + 1;
				q.push({ nx,ny });
			}
		}
	}
	return dist;
}

void init1() {
	int r, c, x, y;
	cin >> r >> c>>x>>y;
	x--,y--;
	for (int i = 0;i < r;i++) {
		for (int j = 0; j < c;j++) {
			cin >> board1[i][j];
		}
	}
	vector<vector<int>> distcheck = bfs2(x, y, r, c);

	for (const auto& row : distcheck) {
		for (const auto& val : row) {
		cout << val << ' ';
		}
		cout << '\n';
	}

}
vector<int>adj3[1001];
bool visite[1001];

void inp() {
	int n, m;
	cin >> n >> m;
	for (int i = 0;i < m;i++) {
		int x, y; cin >> x >> y;
		adj3[x].push_back(y);
		adj3[y].push_back(x);
	}
	memset(visite, false, sizeof(visite));//cho tat ca gia tri trong mang vited la false
}
void dfs3(int u) {
	cout << u << " ";
	visite[u] = true;
	for (int v : adj3[u]) {
		if (!visite[v]) {
			dfs3(v);
		}
	}
}


static void BFSCyc(int u, vector<int> edges[MAX]) { // dang bai dinh canh  
   // KhoiTao  
   queue<int> q;  
   q.push(u);  
   visite[u] = true;  
   while (!q.empty()) {  
       int v = q.front(); // lay o dau hang doi  
       q.pop();  
       cout << v << " ";  
       for (int x : edges[v]) { // Corrected 'edges[u]' to 'edges[v]'  
           if (!visite[x]) {  
               q.push(x);  
               visite[x] = true; // Corrected 'visited[u]' to 'visited[x]'  
           }  
       }  
   }  
}

vector<bool> visited;
extern vector<vector<int>> adj;
// để lưu parent phục vụ reconstruct path khi phát hiện cycle
vector<int> parent;

// --- BFS in thứ tự từ 0 ---
void printBFS(int start) {
	queue<int> q;
	vector<bool> seen(adj.size(), false);
	q.push(start);
	seen[start] = true;

	while (!q.empty()) {
		int u = q.front(); q.pop();
		cout << u << " ";
		for (int v : adj[u]) {
			if (!seen[v]) {
				seen[v] = true;
				q.push(v);
			}
		}
	}
	cout << "\n";
}
// --- DFS phát hiện cycle và reconstruct path ---
bool dfsCycle(int u, vector<bool>& inStack, int& cycle_start, int& cycle_end) {
	visited[u] = true;
	inStack[u] = true;

	for (int v : adj[u]) {
		if (!visited[v]) {
			parent[v] = u;
			if (dfsCycle(v, inStack, cycle_start, cycle_end) == true)
				return true;
		}
		else if (inStack[v] == true) {
			// gặp back-edge u->v, tìm được cycle
			cycle_end = u;
			cycle_start = v;
			return true;
		}
	}

	inStack[u] = false;
	return false;
}

void findAndPrintCycle() {
	int n = adj.size();
	visited.assign(n, false);
	parent.assign(n, -1);
	vector<bool> inStack(n, false);

	int cycle_start = -1, cycle_end = -1;
	// chạy DFS trên tất cả các thành phần liên thông (đồ thị có hướng)
	for (int i = 0; i < n; i++) {
		if (!visited[i] && dfsCycle(i, inStack, cycle_start, cycle_end) == true)
			cout << "true\n";
			break;
	}

	if (cycle_start == -1) {
		cout << "false\n";
		return;
	}

	// reconstruct đường cycle từ cycle_end ngược lên cycle_start va in ra
	/*vector<int> cycle;
	cycle.push_back(cycle_start);
	for (int v = cycle_end; v != cycle_start; v = parent[v]) {
		cycle.push_back(v);
	}
	cycle.push_back(cycle_start);  // đóng vòng

	// in đường đi
	for (int x : cycle) {
		cout << x << " ";
	}
	cout << "\n";*/
}
void isCyclic() {  
int V;  
cin >> V;  
adj.assign(V, {});
int u, v;  
for (int i = 0; i < V; i++) {  
	cin >> u >> v;  
	adj[u].push_back(v);  
	// edges[v].push_back(u);  
}  
printBFS(0);
findAndPrintCycle();
}  

