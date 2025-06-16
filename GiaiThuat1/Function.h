#ifndef FUNCTION_H
#define FUNCTION_H

#include<iostream>	
#include<string>
#include<vector>
#include"Function.h"
#include<queue>
using namespace std;

#ifdef __cplusplus
#endif



void Greedy();
void init_binarynumber(vector<string>& binary);
void bfs(int i, int j);
void inpo();
void init();
void init1();
vector<vector<int>> bfs2(int nx, int ny, int r, int c);

#ifdef __cplusplus
#endif

#endif // FUNCTION_H