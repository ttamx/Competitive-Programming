#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef tuple<ll,ll,int> t3;

const int N=1e5+5;

int n;
ll m;
ll ans[N];

set<t3> s1,s2,s3;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=n;++i){
        ll x,y;
        cin >> x >> y;
        s1.insert({x,y+i,i});
    }
    auto pre=s1.begin(),now=s1.begin();
    ++now;
    while(now!=s1.end()){
        auto [px,py,pi]=*pre;
        auto [nx,ny,ni]=*now;
        ll dif=ny-py;
        ll pxx=px+dif;
        if(pxx>nx || (pxx==nx && pi<ni))now=s1.erase(now);
        else ++pre;
        if(pre==now)++now;
    }
    for(auto [x,y,i]:s1)s2.insert({-x,y,i});
    pre=s2.begin(),now=s2.begin();
    ++now;
    while(now!=s2.end()){
        auto [px,py,pi]=*pre;
        auto [nx,ny,ni]=*now;
        px=-px,nx=-nx;
        ll dif=ny-py;
        ll pxx=px-dif;
        if(pxx<nx || (pxx==nx && pi<ni))now=s2.erase(now);
        else ++pre;
        if(pre==now)++now;
    }
    for(auto [x,y,i]:s2)s3.insert({-x,y,i});
    pre=s3.begin(),now=s3.begin();
    ++now;
    ans[get<2>(*pre)]+=get<0>(*pre);
    while(now!=s3.end()){
        auto [px,py,pi]=*pre;
        auto [nx,ny,ni]=*now;
        ll dif;
        if(py<ny){
            dif=ny-py;
            ans[pi]+=dif;
            ll pxx=px+dif;
            dif=nx-pxx-1LL;
        }else{
            dif=py-ny;
            ans[ni]+=dif;
            ll nxx=nx-dif;
            dif=nxx-px-1LL;
        }
        if(dif&1LL)++ans[(pi<ni?pi:ni)],--dif;
        ans[pi]+=(dif/2LL)+1;
        ans[ni]+=dif/2LL;
        ++now,++pre;
    }
    ans[get<2>(*pre)]+=m-get<0>(*pre)+1;
    for(int i=1;i<=n;++i)cout << ans[i] << '\n';
}
