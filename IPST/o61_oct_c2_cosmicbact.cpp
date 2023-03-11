#include<bits/stdc++.h>
#define ll long long

using namespace std;

const int N=1e5+5;

int n;
ll m;
ll ans[N];
set<tuple<ll,ll,int>> s,s2,s3;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=n;++i){
        ll x,y;
        cin >> x >> y;
        s.insert({x,y+i,i});
    }
    auto pre=s.begin(),now=++s.begin();
    while(now!=s.end()){
        auto [px,pt,pi]=*pre;
        auto [nx,nt,ni]=*now;
        ll dif=nx-px;
        if(nt<pt+dif)now=s.erase(now);
        else if(nt==pt+dif && ni>pi)now=s.erase(now);
        else ++pre;
        if(pre==now)++now;
    }
    for(auto [x,t,i]:s)s2.insert({-x,t,i});
    pre=s2.begin(),now=++s2.begin();
    while(now!=s2.end()){
        auto [px,pt,pi]=*pre;
        auto [nx,nt,ni]=*now;
        ll dif=nx-px;
        if(nt<pt+dif)now=s2.erase(now);
        else if(nt==pt+dif && ni>pi)now=s2.erase(now);
        else ++pre;
        if(pre==now)++now;
    }
    for(auto [x,t,i]:s2)s3.insert({-x,t,i});
    pre=s3.begin(),now=++s3.begin();
    ans[get<2>(*pre)]+=get<0>(*pre);
    while(now!=s3.end()){
        auto [px,pt,pi]=*pre;
        auto [nx,nt,ni]=*now;
        if(pt<nt){
            ll pxx=px+nt-pt;
            ll dif=nx-pxx-1;
            pxx+=dif/2;
            ll nxx=nx-(dif/2);
            if(dif^1){
                if(pi<ni)++pxx;
                else --nxx;
            }
            ans[pi]+=pxx-px;
            ans[ni]+=nx-nxx;
        }else{
            ll nxx=nx-(pt-nt);
            ll dif=nxx-px-1;
            nxx-=dif/2;
            ll pxx=px+(dif/2);
            if(dif^1){
                if(pi<ni)++pxx;
                else --nxx;
            }
            ans[pi]+=pxx-px;
            ans[ni]+=nx-nxx;
        }
        ++now,++pre;
    }
    ans[get<2>(*pre)]+=m-get<0>(*pre);
    for(int i=1;i<=n;++i)cout << ans[i] << '\n';
}
