#include<bits/stdc++.h>

using namespace std;

using ll = long long;
using P = pair<ll,int>;
using T = tuple<ll,int,int>;

const int N=2e5+5;
const int K=1<<19;
const ll INF=1e18;

int n,k;
vector<tuple<int,int,int>> a,b;

vector<ll> calc(vector<tuple<int,int,int>> &a){
    int n=a.size();
    vector<bool> used(n);
    int l=0,r=n-1;
    int pl=0,pr=n-1;
    priority_queue<P,vector<P>,greater<P>> pql,pqr;
    auto get_min=[&](){
        T res(INF,-1,-1);
        P opt(INF,-1);
        for(int i=0;i<n;i++){
            if(used[i])continue;
            auto [_,t,v]=a[i];
            if(t)res=min(res,{opt.first+v,opt.second,-i});
            else opt=min(opt,{v,i});
        }
        return res;
    };
    auto get_min2=[&](){
        for(;pl<l;pl++){
            auto [_,t,v]=a[pl];
            if(!t)pql.emplace(v,pl);
        }
        for(;pr>r;pr--){
            auto [_,t,v]=a[pr];
            if(t)pqr.emplace(v,-pr);
        }
        while(!pql.empty()&&used[pql.top().second])pql.pop();
        while(!pqr.empty()&&used[-pqr.top().second])pqr.pop();
        if(pql.empty()||pqr.empty())return T(INF,-1,-1);
        auto [vl,il]=pql.top();
        auto [vr,ir]=pqr.top();
        return T(vl+vr,il,ir);
    };
    vector<ll> res{0};
    while(res.size()<=k){
        auto [v,i,j]=min(get_min(),get_min2());
        if(v==INF)break;
        j=-j;
        res.emplace_back(res.back()+v);
        used[i]=used[j]=true;
        l=max(l,j);
        r=min(r,i);
    }
    return res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for(int i=0;i<n;i++){
        int t,x,y,c;
        cin >> t >> x >> y >> c;
        if(t<=2){
            a.emplace_back(x,t%2,c);
        }else{
            b.emplace_back(y,t%2,c);
        }
    }
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    auto aa=calc(a);
    auto bb=calc(b);
    ll ans=INF;
    for(int i=0;i<aa.size();i++){
        if(k-i<bb.size()){
            ans=min(ans,aa[i]+bb[k-i]);
        }
    }
    cout << (ans<INF?ans:-1LL) << "\n";
}