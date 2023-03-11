#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef tuple<ll,ll,ll> t3;

const int N=1e5+5;

struct line{
    ll m,c;
    line(ll m,ll c):m(m),c(c){}
    double cross(line l){
        return 1.0*(c-l.c)/(l.m-m);
    }
    ll calc(ll x){
        return m*x+c;
    }
};

int n;
ll ans;
vector<t3> in;
deque<line> dq;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    in.resize(n);
    for(auto &[x,y,a]:in)cin >> x >> y >> a;
    sort(in.begin(),in.end());
    dq.push_back(line(0,0));
    for(auto [x,y,a]:in){
        while(dq.size()>1 && dq[0].cross(dq[1])>y)dq.pop_front();
        ll dp=dq[0].calc(y)+(x*y)-a;
        line ln(-x,dp);
        ans=max(ans,dp);
        while(dq.size()>1 && dq[dq.size()-2].cross(dq.back())<dq[dq.size()-2].cross(ln))dq.pop_back();
        dq.push_back(ln);
    }
    cout << ans;
}