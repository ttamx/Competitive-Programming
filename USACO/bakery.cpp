#include<bits/stdc++.h>

using namespace std;

const bool DBG=false;

typedef long long ll;
typedef double db;

struct line{
    db m,c;
    line():m(-1e18),c(-1e18){}
    line(db _m,db _c):m(_m),c(_c){}
    db get(db x){
        return m*x+c;
    }
    db insect(line o){ 
        return (o.c-c)/(m-o.m);
    }
    bool operator<(line o){
        if(m==o.m)return c<o.c;
        return m<o.m;
    }
};

void runcase(){
    int n;
    db tc,tm;
    cin >> n >> tc >> tm;
    vector<line> v;
    for(int i=0;i<n;i++){
        db a,b,c;
        cin >> a >> b >> c;
        v.emplace_back(-a/b,(a*tc+b*tm-c)/b);
    }
    v.emplace_back(0,0);
    sort(v.begin(),v.end());
    if(DBG)for(auto [x,y]:v)cerr << x << ' ' << y << '\n';
    deque<line> dq;
    for(line l:v){
        while(dq.size()>1&&dq[dq.size()-2].insect(l)<=dq[dq.size()-2].insect(dq[dq.size()-1]))dq.pop_back();
        dq.emplace_back(l);
    }
    if(DBG)cerr << "\n";
    if(DBG)for(auto [m,c]:dq)cerr << m << " " << c << "\n";
    db x=floor(dq[0].insect(dq[1]));
    ll ans=min(ceil(dq[0].get(0)),x+ceil(dq[0].get(x)));
    if(DBG)cerr << "\n2ND PROCESS\n";
    if(DBG)cerr << "0 : 0 " << x << '\n';
    for(int i=1;i+1<dq.size();i++){
        db x1=ceil(dq[i].insect(dq[i-1]));
        db x2=floor(dq[i].insect(dq[i+1]));
        if(DBG)cerr << i << " : " << x1 << ' ' << x2 << '\n';
        if(x2<x1)continue;
        ans=min(ans,ll(x1+ceil(dq[i].get(x1))));
        ans=min(ans,ll(x2+ceil(dq[i].get(x2))));
    }
    x=ceil(dq[dq.size()-1].insect(dq[dq.size()-2]));
    ans=min(ans,ll(x+ceil(dq[dq.size()-1].get(x))));
    cout << max(ans,0ll) << '\n';
    if(DBG)cerr << "\n-----------\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();   
}