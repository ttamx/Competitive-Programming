#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int B=60;

void solve(){
    int n;
    cin >> n;
    ll sum=0;
    vector<ll> a(n);
    for(auto &x:a){
        cin >> x;
        sum^=x;
    }
    ll basis[B]={};
    auto insert=[&](ll x){
        for(int i=B-1;i>=0;i--){
            if(x>>i&1){
                if(basis[i]){
                    x^=basis[i];
                }else{
                    basis[i]=x;
                    break;
                }
            }
        }
    };
    auto query=[&](ll x){
        for(int i=B-1;i>=0;i--)if(!(x>>i&1))x^=basis[i];
        return x;
    };
    ll ans=sum;
    for(auto x:a){
        x&=~sum;
        ans=max(ans,query(x));
        insert(x);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}