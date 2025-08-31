#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int B=100;

ll mob[B];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    ll l,r;
    cin >> l >> r;
    mob[1]=-1;
    for(int i=1;i<B;i++){
        for(int j=i*2;j<B;j+=i){
            mob[j]-=mob[i];
        }
    }
    auto calc=[&](ll x){
        ll res=0;
        for(ll s=1,b=1;s<=x;s<<=1,b++){
            for(int i=1;i<b;i++){
                if(b%i)continue;
                ll mn=(1LL<<i)-1;
                if(x<s*2){
                    ll cur=x;
                    for(int j=0;j<b;j+=i){
                        mn=min(mn,cur&((1LL<<i)-1));
                        cur>>=i;
                    }
                }
                if(!(mn>>i&1))continue;
                res+=mob[b/i]*(mn-(1LL<<i));
            }
        }
        cerr << x << " : " << res << "\n";
        return res;
    };
    cout << calc(r)-calc(l-1) << "\n";
}