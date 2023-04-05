#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    ll m;
    cin >> n >> m;
    map<int,ll> mp;
    for(int i=0;i<n;i++){
        int s,e,b;
        cin >> s >> e >> b;
        mp[s]+=b;
        mp[e+1]-=b;
    }
    ll val=0;
    int l;
    for(auto [x,y]:mp){
        if(val<m&&val+y>=m)l=x;
        if(val>=m&&val+y<m)cout << l << ' ' << x-1 << '\n';
        val+=y;
    }
}