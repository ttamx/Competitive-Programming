#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<tuple<int,int,int>> a(n);
    ll sum=0;
    for(auto &[v,l,r]:a){
        cin >> v >> l >> r;
        sum+=v;
    }
    auto calc=[&](ll st){
        ll opt=0;
        priority_queue<ll> pql;
        priority_queue<ll,vector<ll>,greater<ll>> pqr;
        ll lzl=0,lzr=0;
        auto insert=[&](ll x){
            if(!pql.empty()&&x<pql.top()+lzl){
                opt+=(pql.top()+lzl)-x;
                pql.emplace(x-lzl);
                pql.emplace(x-lzl);
                pqr.emplace(pql.top()+lzl-lzr);
                pql.pop();
            }else if(!pqr.empty()&&x>pqr.top()+lzr){
                opt+=x-(pqr.top()+lzr);
                pqr.emplace(x-lzr);
                pqr.emplace(x-lzr);
                pql.emplace(pqr.top()+lzr-lzl);
                pqr.pop();
            }else{
                pql.emplace(x-lzl);
                pqr.emplace(x-lzr);
            }
        };
        for(int i=0;i<n+1;i++){
            insert(st);
        }
        for(int i=0;i<n;i++){
            auto [v,l,r]=a[i];
            lzl+=v-r;
            lzr+=v-l;
            insert(0);
        }
        if(st<pql.top()+lzl){
            while(!pql.empty()){
                ll p=pql.top()+lzl;
                if(p<=st)break;
                pql.pop();
                opt+=p-st;
            }
        }else{
            while(!pqr.empty()){
                ll p=pqr.top()+lzr;
                if(p>=st)break;
                pqr.pop();
                opt+=st-p;
            }
        }
        return opt;
    };
    ll l=-sum,r=sum;
    while(l<r){
        ll m=l+(r-l)/2;
        if(calc(m)<=calc(m+1))r=m;
        else l=m+1;
    }
    cout << calc(l) << "\n";
}