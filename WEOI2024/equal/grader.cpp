// Sample grader
#include <iostream>
#include <algorithm>
#include <vector>
#include "equal.cpp"

namespace {

constexpr int MAX_N = 2048;
constexpr long long MIN_DELTA = 0, MAX_DELTA = 1e12;
static_assert(MAX_DELTA == 1000000000000ll);
int max_add, max_compare;
int curr_add = 0, curr_compare = 0;

int N;
long long hidden_array[MAX_N];

void wa(std::string MSG) {
	std::cout << "Wrong answer: " << MSG << '\n';
	exit(0);
}

}  // namespace

void add(std::vector<int> S, long long X) {
	++curr_add;
	if (curr_add > max_add) {
		wa("too many calls to add");
	}
	if (!(MIN_DELTA <= X && X <= MAX_DELTA)) {
		wa("X out of range");
	}
	if (S.empty()) {
		return;
	}
	std::sort(S.begin(), S.end());
	if (!(0 <= S.front() && S.back() <= N-1)) {
		wa("index in S out of range");
	}
	for (int iSub = 0; iSub < (int)(S.size()) - 1; ++iSub) {
		if (S[iSub] == S[iSub+1]) {
			wa("indices in S not distinct");
		}
	}
	for (int iArray : S) {
		hidden_array[iArray] += X;
	}
	std::sort(hidden_array, hidden_array + N);
	for(int i=0;i<N;i++)cerr << hidden_array[i] << " \n"[i==N-1];
}

bool compare(int i, int j) {
	++curr_compare;
	if (curr_compare > max_compare) {
		wa("too many calls to compare");
	}
	if (!(0 <= i && i <= N-1)) {
		wa("i out of range");
	}
	if (!(0 <= j && j <= N-1)) {
		wa("j out of range");
	}
	return hidden_array[i] == hidden_array[j];
}

int main() {
	std::cin >> N >> max_add >> max_compare;
	for (int i = 0; i < N; ++i) {
		std::cin >> hidden_array[i];
	}
	make_all_equal(N, max_add, max_compare);
	// invariant: array is sorted
	for (int i = 0; i < N-1; ++i) {
		if (hidden_array[i] != hidden_array[i+1]) {
			wa("heights are not equal");
		}
	}
	std::cout << "Accepted: add=" << curr_add << ", compare=" << curr_compare << "\n";
}
