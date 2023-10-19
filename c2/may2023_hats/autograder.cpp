#include "hats.cpp"
#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
using namespace std;

int get_score(int N) {
    int score = 0;
    for (int mask = 0; mask < (1 << N); mask++) {
	    int flag = 0;
	    for (int id = 0; id < N; id++) {
		vector<int> hats;
		for (int i = 0; i < N; i++) {
		    if (i == id)
			hats.push_back(-1);
		    else
			hats.push_back((mask >> i) & 1);
		}
		int res = think(N, id, hats);
		if (abs(res) > 1) {
		    flag = -1;
		}
		if (res != -1) {
		    if (flag == 0)
			flag = 1;
		    int sol = (mask >> id) & 1;
		    if (res != sol) {
			flag = -1;
		    }
		}
	    }
	    if (flag == 1) score++;
    }
    return score;
}

int main() {
    double total = 0.0;

    int N = 3;
    printf("[Subtask 1]\n");
    int score = get_score(N);
    printf("Current probability: %d/%d.\n", score, 1 << N);
    double outcome = 25.0 * max(0.0, 1.2 * log2(min((double)score * (N+1) / (1 << N) / N, 1.0))+1.0);
    printf("Expected score: %.2f\n", outcome);
    total += outcome;
    printf("\n");

    N = 7;
    printf("[Subtask 2]\n");
    score = get_score(N);
    printf("Current probability: %d/%d.\n", score, 1 << N);
    outcome = 75.0 * max(0.0, 1.2 * log2(min((double)score * (N+1) / (1 << N) / N, 1.0))+1.0);
    printf("Expected score: %.2f\n", outcome);
    total += outcome;
    printf("\n");

    printf("TOTAL: %.2f\n", total);
    return 0;
}
