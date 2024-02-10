#include<bits/stdc++.h>

using namespace std;

using ll = long long;
using pl = pair<ll,ll>;

const int N=1e6+5;

int n,k;
string s;
int a[N],b[N];
ll qs[N];
pl dp[N];

struct Line{
    ll m,c,cnt;
    Line(ll _m,ll _c,ll _cnt):m(_m),c(_c),cnt(_cnt){}
    ll eval(ll x){
        return m*x+c;
    }
};

struct CHT{
    deque<Line> hull;
    bool bad(Line x,Line y,Line z){
        return (x.c-y.c)*(z.m-y.m)>(y.c-z.c)*(y.m-x.m);
    }
    void insert(ll m,ll c,ll cnt){
        Line v(m,c,cnt);
        while(hull.size()>1&&bad(hull.end()[-2],hull.back(),v))hull.pop_back();
        hull.emplace_back(v);
    }
    pl query(ll x){
        while(hull.size()>1&&hull[0].eval(x)>hull[1].eval(x))hull.pop_front();
        return pl(hull[0].eval(x),hull[0].cnt);
    }
};

pl solve(ll lambda){
    CHT cht;
    cht.insert(0,0,0);
    queue<int> q;
    for(int i=1;i<=n;i++){
        while(!q.empty()&&b[q.front()]<i){
            int j=q.front();
            q.pop();
            cht.insert(-j,dp[j].first-qs[b[j]]+1LL*j*b[j],dp[j].second);
        }
        dp[i]=cht.query(i);
        dp[i].first+=qs[i]+lambda;
        dp[i].second++;
        q.emplace(i);
    }
    return dp[n];
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k >> s;
    for(int i=0,ia=0,ib=0;i<2*n;i++){
        if(s[i]=='A'){
            a[++ia]=ib;
        }else{
            ib++;
            b[ib]=max(ib,ia);
        }
    }
    for(int i=1;i<=n;i++)qs[i]=qs[i-1]+a[i];
    ll l=0,r=1LL*n*n;
    while(l<r){
        ll m=(l+r)/2;
        if(solve(m).second<=k)r=m;
        else l=m+1;
    }
    cout << solve(l).first-k*l;
}