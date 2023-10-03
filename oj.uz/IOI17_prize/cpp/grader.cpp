#include "prize.cpp"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

static const int max_q = 10000;
static int nn;
static int query_count = 0;
static vector<int> g;
static vector<vector<int> > rank_count;

vector<int> ask(int i) {
	query_count++;
	if(query_count > max_q) {
		cerr << "Query limit exceeded" << endl;
		exit(0);
	}

	if(i < 0 || i >= nn) {
		cerr << "Bad index: " << i << endl;
		exit(0);
	}

	vector<int> res(2);
	res[0] = rank_count[g[i] - 1][i + 1];
	res[1] = rank_count[g[i] - 1][nn] - res[0];
	return res;
}

int main() {
	cin >> nn;

	g.resize(nn);
	for(int i = 0; i < nn; i++) {
		cin >> g[i];
		if(g[i] < 1) {
			cerr << "Invalid rank " << g[i] << " at index " << i << endl;
			exit(0);
		}
	}

	int max_rank = *max_element(g.begin(), g.end());

	rank_count.resize(max_rank + 1, vector<int>(nn + 1, 0));
	for(int r = 0; r <= max_rank; r++) {
		for(int i = 1; i <= nn; i++) {
			rank_count[r][i] = rank_count[r][i - 1];
			if(g[i - 1] == r)
			  rank_count[r][i]++;
		}
	}

	for(int i = 0; i <= nn; i++)
		for(int r = 1; r <= max_rank; r++)
			rank_count[r][i] += rank_count[r - 1][i];

	int res = find_best(nn);
	cout << res << endl << "Query count: " << query_count << endl;

	return 0;
}
