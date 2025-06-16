#include<iostream>	
#include<string>
#include<vector>
#include"Function.h"
#include<queue>
using namespace std;

void init_binarynumber(vector<string>& binary) {
	queue<string> q;
	q.push("1");
	binary.push_back("1");
	while (binary.size() < 10000) {
		string top = q.front(); // luu gia tri cua ham doi sau khi bi xoa
		q.pop();
		binary.push_back(top + "0");
		binary.push_back(top + "1");
		q.push(top + "0");
		q.push(top + "1");
	}
}