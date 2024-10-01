#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<long long> a(n);
    for(auto &x:a)cin >> x;
    sort(a.begin(),a.end());
    long long mx=a.back();
    long long ans=0;
    for(auto x:a){
        for(auto y:a){
            ans=max(ans,mx*mx+x*x+y*y-mx*x-mx*y-x*y);
        }
    }
    cout << ans;
}