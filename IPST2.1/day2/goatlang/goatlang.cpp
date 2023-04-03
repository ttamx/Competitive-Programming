#include "goatlang.h"
#include<bits/stdc++.h>

using namespace std;

typedef tuple<vector<vector<int>>, int, int> t3;

t3 example1() {
	return {{{1, 0, 0}, {0, 2, 0}, {0, 0, 3}}, 2, 2};
}

t3 example2() {
	return {{{1, 1}, {1, 0}}, 0, 1};
}

t3 task1(vector<vector<int>> A, int r, int c) {
	return {A, r, c}; // edit this
}
t3 task2(vector<vector<int>> H, int a, int b) {
	vector<vector<int>> res(40,vector<int>(40));
	for(int i=0;i<H.size();i++){
		for(int j=0;j<H[i].size();j++){
			res[i][j]=H[i][j];
		}
	}
	for(int i=0;i<H.size();i++)res[35][i]=H[a][i];
	res[35][35]=1;
	return {res, 35, b}; // edit this
}
t3 task3(vector<int> a) {
	int d=a.size();
	while(a.size()<=10)a.emplace_back(0);
	vector<vector<int>> res(40,vector<int>(40));
	// 0 -> 1
	// 2 -> n
	// 4 -> n^2
	res[0][0]=1;
	res[0][1]=1;
	res[1][1]=1;
	res[1][2]=1;
	res[0][2]=1;
	res[2][3]=1;
	res[3][3]=1;
	res[3][4]=2;
	res[2][4]=3;
	res[0][4]=1;
	res[0][39]=a[0]+a[1]+a[2];
	res[2][39]=a[1]+2*a[2];
	res[4][39]=a[2];
	res[0][5]=1;
	res[2][5]=3;
	res[4][5]=3;
	res[5][5]=1;
	return {res,0,39};
}
t3 task4() {
	vector<vector<int>> res(10,vector<int>(10));
	for(int i=1;i<=7;i++)res[0][i]=res[i][8]=1;
	res[1][1]=1;
	res[1][2]=1;
	res[2][3]=1;
	res[2][4]=1;
	res[3][5]=1;
	res[4][6]=1;
	res[4][7]=1;
	res[5][1]=1;
	res[5][2]=1;
	res[6][5]=1;
	res[7][6]=1;
	res[7][7]=1;
	res[8][9]=1;
	res[0][8]=4;
	res[0][9]=2;
	return {res, 0, 9}; // edit this
}
t3 task5(vector<int> D) {
	vector<vector<int>> res(30,vector<int>(30));
	int m=D.size();
	for(int i=1;i<m;i++)res[i-1][i]=1;
	for(int i=0;i<m;i++)res[i][m]=D[i];
	return {res, 0, m}; // edit this
}
t3 task6(int m) {
	vector<vector<int>> res(30,vector<int>(30));
	for(int i=1;i<=m;i++)res[i-1][i]=1;
	for(int i=1;i<m;i++)res[m+i-1][m+i]=1;
	res[2*m-1][m]=1;
	return {res, 0, m}; // edit this
}