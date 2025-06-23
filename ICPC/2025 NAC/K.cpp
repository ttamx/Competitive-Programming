#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<ll> a(n);
    for(auto &x:a)cin >> x;
    ll cur=0,ans=1;
    for(auto x:a){
        if(x>cur){
            ans+=x-cur+1;
        }
        cur=x;
    }
    cout << ans << "\n";
}