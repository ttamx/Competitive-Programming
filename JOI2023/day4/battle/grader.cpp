#include "Anna.cpp"
#include "Bruno.cpp"
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <random>
#include <algorithm>

namespace {

void WrongAnswer(int code) {
  printf("Wrong Answer [%d]\n", code);
  exit(0);
}

int Current_Challenge = 0;
int Q;
std::vector<int> X, Y, N;
std::vector<std::string> S;
int PaintCount = 0;
std::vector<std::vector<int>> T;
std::mt19937 rng;

}

void Paint(int a, int b, int c) {
	if (a < 0 || a > 7 || a == X[Current_Challenge]) WrongAnswer(1);
	if (b < 0 || b > 7 || b == Y[Current_Challenge]) WrongAnswer(1);
	if (c < 0 || c > 1) WrongAnswer(2);
	if (T[a][b] != -1) WrongAnswer(3);
	T[a][b] = c;
	PaintCount += 1;
}

void Bitaro() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (i != X[Current_Challenge] && j != Y[Current_Challenge]) continue;
			T[i][j] = std::uniform_int_distribution<int>(0, 1)(rng);
		}
	}
}

int main(int argc, char **argv) {
	long long seed = 0;
	if (argc >= 2) {
		seed = atoll(argv[1]);
	}
	rng = std::mt19937(seed);
	
	if (scanf("%d", &Q) != 1) {
		fprintf(stderr, "Error while reading input\n");
		exit(1);
	}
	X = std::vector<int>(Q + 1, 0);
	Y = std::vector<int>(Q + 1, 0);
	N = std::vector<int>(Q + 1, 0);
	S = std::vector<std::string>(Q + 1, "");
	
	for (int challenge = 1; challenge <= Q; challenge++) {
		S[challenge] = "";
		if (scanf("%d%d%d", &X[challenge], &Y[challenge], &N[challenge]) != 3) {
			fprintf(stderr, "Error while reading input\n");
			exit(1);
		}
		char tmp;
		if (scanf("%c", &tmp) != 1) {
			fprintf(stderr, "Error while reading input\n");
			exit(1);
		}
		for (int i = 0; i < N[challenge]; i++) {
			if (scanf("%c", &tmp) != 1) {
				fprintf(stderr, "Error while reading input\n");
				exit(1);
			}
			if (tmp != 'A' && tmp != 'B') {
				cout << char(tmp);
				fprintf(stderr, "Error: A character in S is neither A nor B");
			}
			S[challenge] += tmp;
		}
	}
	
	int Score = 43;
	
	for (int challenge = 1; challenge <= Q; challenge++) {
		Current_Challenge = challenge;
		T = std::vector<std::vector<int>>(8, std::vector<int>(8, -1));
		PaintCount = 0;
		Anna(X[challenge], Y[challenge], N[challenge], S[challenge]);
		if (PaintCount != 49) WrongAnswer(4);
		Bitaro();
		std::string Answer = Bruno(N[challenge], T);
		if ((int)Answer.size() > 43) WrongAnswer(5);
		for (int i = 0; i < (int)Answer.size(); i++) {
			if (Answer[i] != 'A' && Answer[i] != 'B') WrongAnswer(6);
		}		
		if (Answer != S[challenge]) {
			Score = std::min(Score, N[challenge] - 1);
		}
	}
	
	printf("Accepted: %d\n", Score);
	return 0;
}
