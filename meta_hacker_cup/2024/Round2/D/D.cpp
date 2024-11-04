#include<bits/stdc++.h>

using namespace std;

using ll = long long;

void runcase(){
    int n;
    cin >> n;
    vector<int> c(n);
    vector<set<int>> ids(n);
    for(int i=0;i<n;i++){
        cin >> c[i];
        c[i]--;
        ids[c[i]].emplace(i);
    }
    vector<int> w(n);
    for()
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cout << fixed << setprecision(15);
    int t(1);
    cin >> t;
    for(int i=1;i<=t;i++){
        cout << "Case #" << i << ": ";
        runcase();
    }
}