#include <iostream>
#include <vector>

using namespace std;

bool heights(int N, vector<int> Z, vector<int> &H);

int main() {
    // decommenta queste due righe per leggere da / scrivere su file
    // uncomment these two lines to read from / write to file
    // assert(freopen("input.txt", "r", stdin));
    // assert(freopen("output.txt", "w", stdout));

    int N;
    cin >> N;

    vector<int> Z(N - 1), H(N);
    for (int &z: Z) {
        cin >> z;
    }

    bool found = heights(N, Z, H);

    if (!found) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
        for (int h: H) {
            cout << h << " ";
        }
        cout << "\n";
    }
}
