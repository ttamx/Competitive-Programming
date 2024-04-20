#include "alienlang.cpp"
#include <iostream>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;

static int counter = 3;
static vector<tuple<int, int, int>> nodes;

int add_machine(int src1, int src2) {
    if (src1 >= counter || src2 >= counter || src1 < 0 || src2 < 0) {
        cout << "input position out of bound" << endl;
        exit(0);
    }
    if (counter >= 5000003) {
        cout << "too many machines" << endl;
        exit(0);
    }
    int now = counter++;
    nodes.push_back({1, src1, src2});
    return now;
}

int minus_machine(int src1, int src2) {
    if (src1 >= counter || src2 >= counter || src1 < 0 || src2 < 0) {
        cout << "input position out of bound" << endl;
        exit(0);
    }
    if (counter >= 5000003) {
        cout << "too many machines" << endl;
        exit(0);
    }
    int now = counter++;
    nodes.push_back({-1, src1, src2});
    return now;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m, p;
    cin >> n >> m >> p;
    vector<int> values;
    values.push_back(0);
    values.push_back(n);
    values.push_back(m);
    nodes.push_back({0, 0, 0});
    nodes.push_back({0, n, n});
    nodes.push_back({0, m, m});
    int out = make_circuit(n, m, p);
    if (out == -1) {
        cout << "output: null" << endl;
        cout << "machines count: " << counter - 3 << endl;
        return 0;
    }
    for (int i = 3; i < counter; i++) {
        if (get<0>(nodes[i]) == 1) {
            int a = values[get<1>(nodes[i])];
            int b = values[get<2>(nodes[i])];
            if (abs(a) > 1000000000 || abs(b) > 1000000000) {
                cout << "billion limit exceeded" << endl;
                return 0;
            }
            values.push_back(a + b);
        } else {
            int a = values[get<1>(nodes[i])];
            int b = values[get<2>(nodes[i])];
            if (abs(a) > 1000000000 || abs(b) > 1000000000) {
                cout << "billion limit exceeded" << endl;
                return 0;
            }
            values.push_back(a - b);
        }
    }
    cout << "output: " << values[out] << endl;
    cout << "machines count: " << counter - 3 << endl;
    return 0;
}