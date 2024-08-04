#include <bits/stdc++.h>
#include "overtaking.h"

using namespace std;

using ll = long long;

const int N=1005;
const ll LIM=1e18;

int n,m,x;
ll s[N],dp[N][N];
vector<pair<int,ll>> bus;

bool querymode=false;

struct Interval{
    mutable ll l,r,v;
    Interval(ll _l,ll _r,ll _v):l(_l),r(_r),v(_v){}
    bool operator<(const Interval &o)const{
        if(querymode)return v<o.v;
        return l<o.l||(l==o.l&&r<o.r);
    }
};

struct DS{
    multiset<Interval> s;
    ll offset;
    DS():s(),offset(0){
        querymode=false;
    }
    void add_all(ll x){
        offset+=x;
    }
    void update(ll l,ll r,ll v){
        v-=offset;
        auto it=s.emplace(Interval(l,r,v));
        for(auto x=it;x!=s.begin();x=s.erase(x)){
            x--;
            if(x->l<=l-1){
                x->r=min(x->r,l-1);
                break; 
            }
        }
        for(auto x=next(it);x!=s.end();x=s.erase(x)){
            if(r+1<=x->r){
                x->l=max(x->l,r+1);
                break;
            }
        }
    }
    ll query(ll x){
        auto it=s.lower_bound(Interval(x+1,0,0));
        if(it==s.begin())return x+offset;
        it--;
        return (it->r<x?x:it->v)+offset;
    }
    ll find_first(ll x){
        querymode=true;
        auto it=s.upper_bound(Interval(0,0,x-offset));
        querymode=false;
        ll p=x-offset+1;
        if(it==s.end())return min(LIM+1,p);
        auto [l,r,v]=*it;
        ll pre=it!=s.begin()?prev(it)->r+1:0;
        return min(max(p,pre),l);
    }
}seg;

void init(int _l,int _n,vector<ll> _t,vector<int> _w,int _x,int _m,vector<int> _s){
    n=_n,m=_m-1,x=_x;
    for(int i=0;i<=m;i++)s[i]=_s[i];
    for(int i=0;i<n;i++)bus.emplace_back(_w[i],_t[i]);
    sort(bus.rbegin(),bus.rend());
    while(!bus.empty()&&bus.back().first<=x)bus.pop_back();
    n=bus.size();
    for(int i=0;i<n;i++)dp[0][i]=bus[i].second;
    for(int i=0;i<m;i++){
        ll dist=s[i+1]-s[i];
        vector<pair<ll,ll>> exp,real;
        for(int j=0;j<n;j++){
            ll w=bus[j].first;
            dp[i+1][j]=dp[i][j]+w*dist;
            exp.emplace_back(dp[i][j],dp[i+1][j]);
        }
        sort(exp.begin(),exp.end());
        for(auto [l,r]:exp){
            if(!real.empty()){
                if(real.back().first==l)real.back().second=r;
                else if(real.back().second<r)real.emplace_back(l,r);
            }else{
                real.emplace_back(l,r);
            }
        }
        for(int j=0;j<n;j++){
            auto it=lower_bound(real.begin(),real.end(),pair<ll,ll>(dp[i][j],0));
            if(it!=real.begin())dp[i+1][j]=max(dp[i+1][j],prev(it)->second);
        }
        reverse(real.begin(),real.end());
        vector<tuple<ll,ll,ll>> upd;
        ll dif=x*dist;
        ll last=LIM;
        for(auto [l,r]:real){
            ll l2=seg.find_first(l);
            ll r2=min(seg.find_first(r-dif)-1,last);
            if(l2>r2)continue;
            upd.emplace_back(l2,r2,r);
            last=l2-1;
        }
        seg.add_all(dif);
        for(auto [l,r,v]:upd)seg.update(l,r,v);
    }
}

ll arrival_time(ll y){
    return seg.query(y);
}