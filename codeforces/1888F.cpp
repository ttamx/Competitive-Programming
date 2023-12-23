#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

void runcase(){
    int n;
    cin >> n;
    vector<ll> a(n+2);
    for(int i=1;i<=n;i++)cin >> a[i];
    map<int,ll> mp;
    int q;
    cin >> q;
    vector<tuple<int,int,int>> qr(q);
    for(auto &[l,r,x]:qr)cin >> l >> r >> x;
    int ans=0;
    for(int i=1;i<=q;i++){
        auto [l,r,x]=qr[i-1];
        mp[l]+=x;
        if(mp[l]==0)mp.erase(mp.find(l));
        mp[r+1]-=x;
        if(mp[r+1]==0)mp.erase(mp.find(r+1));
        if(mp.empty())continue;
        if(mp.begin()->second<0){
            ans=i;
            mp.clear();
        }
    }
    vector<ll> b(n+2);
    for(int i=0;i<ans;i++){
        auto[l,r,x]=qr[i];
        b[l]+=x;
        b[r+1]-=x;
    }
    for(int i=1;i<=n;i++){
        b[i]+=b[i-1];
        cout << a[i]+b[i] << " \n"[i==n];
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}