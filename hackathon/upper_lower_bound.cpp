#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> v(n);
    for(auto &x:v)cin >> x;
    vector<int> in=v;
    sort(in.begin(),in.end());
    for(auto &x:v)x=lower_bound(in.begin(),in.end(),x)-in.begin();
    for(auto x:v)cout << x << '\n';
}
