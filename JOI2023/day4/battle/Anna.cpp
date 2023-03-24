#include "Anna.h"
#include <bits/stdc++.h>

using namespace std;

void Anna(int X, int Y, int N, std::string S) {
	while(S.size()<4)S.push_back('A');
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i != X && j != Y) {
				Paint(i, j,(S[0]=='B'));
			}
		}
	}
	for (int i = 4; i < 8; i++) {
		for (int j = 0; j < 4; j++) {
			if (i != X && j != Y) {
				Paint(i, j,(S[1]=='B'));
			}
		}
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 4; j < 8; j++) {
			if (i != X && j != Y) {
				Paint(i, j,(S[2]=='B'));
			}
		}
	}
	for (int i = 4; i < 8; i++) {
		for (int j = 4; j < 8; j++) {
			if (i != X && j != Y) {
				Paint(i, j,(S[3]=='B'));
			}
		}
	}
}
