#include "cheatsheet.cpp"
#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>
#include <set>

static int M = 0;
static int N;
static std::vector<int> a, R, answers;
static int MX = 1000000;
static std::set<int> labels;

int main(){
	assert(scanf("%d", &N) == 1);
	a.resize(N);
	for(int i = 0; i < N; i++) assert(scanf("%d", &a[i]) == 1);
	
	R = write_cheatsheet(N, a);
	if(R.size() > MX){
		printf("Wrong answer: size limit exceeded\n");
		exit(0);
	}
	for(int i = 0; i < R.size(); i++){
		if(labels.find(R[i]) != labels.end()){
			printf("Wrong answer: duplicate elements\n");
			exit(0);
		}
		if(R[i] < 0 || R[i] > MX){
			printf("Wrong answer: value out of bound\n");
			exit(0);
		}
		labels.insert(R[i]);
		M = std::max(M, R[i]);
	}
	
	answers = recover_answer(N, R);
	if(answers.size() != a.size()){
		printf("Wrong answer: incorrect answer size\n");
		exit(0);
	}
	for(int i = 0; i < answers.size(); i++){
		if(answers[i] != a[i]){
			printf("Wrong answer: incorrect value\n");
			exit(0);
		}
	}
	printf("%d\n", M);
}
