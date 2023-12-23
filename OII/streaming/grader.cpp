#include <iostream>
#include <vector>

long long bfs(int N, long long K, std::vector<int> P, std::vector<int> F);

int main() {
	// decommenta queste due righe per leggere da / scrivere su file
	// uncomment these two lines to read from / write to file
    // assert(freopen("input.txt", "r", stdin));
    // assert(freopen("output.txt", "w", stdout));

	int N;
	long long K;
	std::cin >> N >> K;

	std::vector<int> P(N), F(N);
	for (int& i : P)
		std::cin >> i;
	for (int& i : F)
		std::cin >> i;

	std::cout << bfs(N,K,P,F) << "\n";
	return 0;
}
