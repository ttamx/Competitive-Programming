#include<bits/stdc++.h>

using namespace std;

using ll = long long;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<ll> a(n);
    for(auto &x:a){
        cin >> x;
    }
    ll ans=n;
    for(int t=0;t<30;t++){
        ll mid=a[uniform_int_distribution<int>(0,n-1)(rng)];
        for(ll val=mid-1;val<=mid+1;val++){
            ll v=val;
            vector<ll> b;
            for(ll i=2;i*i<=v;i++){
                if(v%i==0){
                    b.emplace_back(i);
                    while(v%i==0)v/=i;
                }
            }
            if(v>1)b.emplace_back(v);
            for(auto d:b){
                ll res=0;
                for(auto x:a){
                    if(x<=d){
                        res+=d-x;
                    }else{
                        x%=d;
                        res+=min(x,d-x);
                    }
                    if(res>ans)break;
                }
                ans=min(ans,res);
            }
        }
    }
    cout << ans << "\n";
}