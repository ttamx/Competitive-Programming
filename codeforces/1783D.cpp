#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll mod=998244353;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    vector<ll> mp(200000);
    mp[a[2]-a[1]+100000]++;
    if(a[1])mp[a[2]+a[1]+100000]++;
    for(int i=3;i<n;i++){
        vector<ll> res(200000);
        for(int j=0;j<200000;j++){
            if(mp[j]==0)continue;
            res[a[i]+200000-j]+=mp[j];
            res[a[i]+200000-j]%=mod;
            if(j!=100000){
                res[a[i]+j]+=mp[j];
                res[a[i]+j]%=mod;
            }
        }
        mp=res;
    }
    ll ans=0;
    for(int i=0;i<200000;i++){
        ans+=mp[i];
        ans%=mod;
    }
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}