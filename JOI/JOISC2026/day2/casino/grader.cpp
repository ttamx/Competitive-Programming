#include "Azzurro.h"
#include "Bordeaux.h"
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <random>
#include <algorithm>

enum {
    INVALID_X = 1,
    INVALID_S = 2,
};

namespace {

void WrongAnswer(int code) {
  printf("Wrong Answer [%d]\n", code);
  exit(0);
}

int Q, N;
std::vector<int> L;
std::vector<std::string> S, R;
std::vector<std::vector<int>> X, T;

}

std::vector<std::vector<int>> Chiaro(int N, std::vector<std::vector<int>> X, std::string R){
    std::vector<std::vector<int>> res = X;
    int posX = 0, posY = 0;
    if (res[0][0] == 0) {
        res[0][0] = 1;
    }
    else {
        res[0][0] = 0;
    }
    for(int i = 0; i < 2 * N - 2; i++){
        if (R[i] == 'D') {
            posX++;
        }
        else {
            posY++;
        }
        if (res[posX][posY] == 0) {
            res[posX][posY] = 1;
        }
        else {
            res[posX][posY] = 0;
        }
    }
    return res;
}

int main(int argc, char **argv) {
	if (scanf("%d", &Q) != 1) {
		fprintf(stderr, "Error while reading input\n");
		exit(1);
	}
    if (scanf("%d", &N) != 1) {
		fprintf(stderr, "Error while reading input\n");
		exit(1);
	}

    L = std::vector<int>(Q + 1, 0);
    S = std::vector<std::string>(Q + 1, "");
    R = std::vector<std::string>(Q + 1, "");

    for (int turn = 1; turn <= Q; turn++) {
        S[turn] = "";
        R[turn] = "";
        if (scanf("%d", &L[turn]) != 1) {
            fprintf(stderr, "Error while reading input\n");
            exit(1);
        }
        char tmp;
		if (scanf("%c", &tmp) != 1) {
			fprintf(stderr, "Error while reading input\n");
			exit(1);
		}
		for (int i = 0; i < L[turn]; i++) {
			if (scanf("%c", &tmp) != 1) {
				fprintf(stderr, "Error while reading input\n");
				exit(1);
			}
			if (tmp != 'A' && tmp != 'B') {
				fprintf(stderr, "Error: A character in S is neither A nor B");
                exit(1);
			}
			S[turn] += tmp;
		}
        if (scanf("%c", &tmp) != 1) {
			fprintf(stderr, "Error while reading input\n");
			exit(1);
		}
        int Count = 0;
		for (int i = 0; i < 2 * (N - 1); i++) {
			if (scanf("%c", &tmp) != 1) {
				fprintf(stderr, "Error while reading input\n");
				exit(1);
			}
			if (tmp != 'D' && tmp != 'R') {
				fprintf(stderr, "Error: A character in R is neither D nor R");
                exit(1);
			}
            if (tmp == 'D') Count++;
			R[turn] += tmp;
		}
        if (Count != N - 1) {
            fprintf(stderr, "Error: The number of D is not N - 1");
            exit(1);
        }
    }
	
	int Score = 51;
	
	for (int turn = 1; turn <= Q; turn++) {
		X = Azzurro(N, L[turn], S[turn]);
        if (X.size() != N) {
            WrongAnswer(INVALID_X);
        }
        for (int i = 0; i < N; i++) {
            if (X[i].size() != N) {
                WrongAnswer(INVALID_X);
            }
            for (int j = 0; j < N; j++) {
                if (X[i][j] != 0 && X[i][j] != 1) {
                    WrongAnswer(INVALID_X);
                }
            }
        }
        T = Chiaro(N, X, R[turn]);
		std::string Answer = Bordeaux(N, L[turn], T);
		if ((int)Answer.size() != L[turn]) {
            WrongAnswer(INVALID_S);
        }
		for (int i = 0; i < (int)Answer.size(); i++) {
			if (Answer[i] != 'A' && Answer[i] != 'B') {
                WrongAnswer(INVALID_S);
            }
		}
		if (Answer != S[turn]) {
			Score = std::min(Score, L[turn] - 1);
		}
	}
	
	printf("Accepted: %d\n", Score);
	return 0;
}