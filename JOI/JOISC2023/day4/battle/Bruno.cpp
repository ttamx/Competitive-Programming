#include "Bruno.h"
#include<bits/stdc++.h>

using namespace std;

std::string Bruno(int N, std::vector<std::vector<int>> T) {
	string S(N,'A');
	while(S.size()<4)S.push_back('A');
	int a=0,b=0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if(T[i][j]==0)a++;
			else b++;
		}
	}
	if(a<b)S[0]='B';
	a=b=0;
	for (int i = 4; i < 8; i++) {
		for (int j = 0; j < 4; j++) {
			if(T[i][j]==0)a++;
			else b++;
		}
	}
	if(a<b)S[1]='B';
	a=b=0;
	for (int i = 0; i < 4; i++) {
		for (int j = 4; j < 8; j++) {
			if(T[i][j]==0)a++;
			else b++;
		}
	}
	if(a<b)S[2]='B';
	a=b=0;
	for (int i = 4; i < 8; i++) {
		for (int j = 4; j < 8; j++) {
			if(T[i][j]==0)a++;
			else b++;
		}
	}
	if(a<b)S[3]='B';
	return S.substr(0,N);
}
