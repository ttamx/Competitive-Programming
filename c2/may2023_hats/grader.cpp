#include "hats.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
    int N;
    string bitmask;
    cin >> N >> bitmask;
    int mask = 0;
    for (int i = 0; i < N; i++) {
	mask |= (bitmask[i] - 48) << i;
    }
    string result;
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
        if (res == -1)
            result.push_back('_');
        else
            result.push_back(res + 48);
        if (res != -1) {
            if (flag == 0)
                flag = 1;
            int sol = (mask >> id) & 1;
            if (res != sol) {
                flag = -1;
            }
        }
    }
    cout << result << endl;
    if (flag == 1)
        cout << "Correct Answer" << endl;
    else
        cout << "Wrong Answer" << endl;
    return 0;
}
