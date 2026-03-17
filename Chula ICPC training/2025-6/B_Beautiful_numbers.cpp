#pragma GCC optimize("Ofast,unroll-loops")
#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int S=8*9*5*7;

ll calc(ll v){
    string s=to_string(v);
    unordered_map<int,array<ll,S>> dp;
    int base_ss=1,base_sum=0;
    for(auto ch:s){
        int x=ch-'0';
        unordered_map<int,array<ll,S>> ndp;
        for(auto &[ss,a]:dp){
            for(int d=0;d<10;d++){
                int sss=ss;
                if(d>0)sss=lcm(ss,d);
                if(!ndp.count(sss))ndp[sss]=array<ll,S>{};
                for(int j=0;j<S;j++){
                    ndp[sss][(j*10+d)%S]+=a[j];
                }
            }
        }
        for(int d=0;d<x;d++){
            int sss=base_ss;
            if(d>0)sss=lcm(base_ss,d);
            if(!ndp.count(sss))ndp[sss]=array<ll,S>{};
            ndp[sss][(base_sum*10+d)%S]++;
        }
        if(x>0)base_ss=lcm(base_ss,x);
        base_sum=(base_sum*10+x)%S;
        dp=move(ndp);
    }
    ll res=0;
    for(auto &[ss,a]:dp){
        for(int i=0;i<S;i+=ss){
            res+=a[i];
        }
    }
    return res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        ll l,r;
        cin >> l >> r;
        cout << calc(r+1)-calc(l) << "\n";
    }
}