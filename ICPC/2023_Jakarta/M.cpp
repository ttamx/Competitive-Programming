#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    ll sum=accumulate(a.begin(),a.end(),0LL);
    ll mx=*max_element(a.begin(),a.end());
    cout << min(sum/3,sum-mx);
}