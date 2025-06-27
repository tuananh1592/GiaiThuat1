#ifndef FUNCTION_H
#define FUNCTION_H

#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<queue>
#include<stack>
#include<limits>
#include<algorithm>
#include"Function.h"
using namespace std;
using ll = long long;
// Define MAX to avoid undeclared identifier error

#ifdef __cplusplus
#endif

const int MAX = 100 + 5;
void Greedy();
void init_binarynumber(vector<string>& binary);
void bfs(int i, int j);
void inpo();
void init();
void init1();
void LIS();
void StringReversal();
vector<vector<int>> bfs2(int nx, int ny, int r, int c);
void dp_tree(int u, int par, vector<int> adj[MAX], int a[MAX], int f[MAX][2]); // par la cha cua dinh u
void init_dp_tree();
void int_goodnode();
void dfs(int u, int par);
void Knapsack();
void init_goodnode2();
void init_goodnode3();
void StringReversal();
void StringSort();
void Toprace();
vector<ll> timUoc(ll n);
#ifdef __cplusplus
#endif

#endif // FUNCTION_H