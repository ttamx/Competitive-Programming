#include <iostream>
#include <vector>

using namespace std;

long long plan(int N, int M, int K, vector<int> A, vector<int> B, vector<int> L, vector<int> C, vector<int> T);

int main() {
    // decommenta queste due righe per leggere da / scrivere su file
    // uncomment these two lines to read from / write to file
    // assert(freopen("input.txt", "r", stdin));
    // assert(freopen("output.txt", "w", stdout));

    int N, M, K;
    cin >> N;
    cin >> M;
    cin >> K;

    vector<int> A(M), B(M), L(M), C(M), T(K);
    for (int &x: A) cin >> x;
    for (int &x: B) cin >> x;
    for (int &x: L) cin >> x;
    for (int &x: C) cin >> x;
    for (int &x: T) cin >> x;

    cout << plan(N, M, K, A, B, L, C, T) << '\n';

    return 0;
}
