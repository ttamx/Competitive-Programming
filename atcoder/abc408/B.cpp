#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    sort(a.begin(),a.end());
    a.erase(unique(a.begin(),a.end()),a.end());
    cout << a.size() << "\n";
    for(auto x:a)cout << x << " ";
    cout << "\n";
}