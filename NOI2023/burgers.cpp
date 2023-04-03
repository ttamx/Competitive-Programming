#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

const int N=1e5+5;

struct line{
    ld m,c;
    line(ld m,ld c):m(m),c(c){}
    ld get(ld x){
        return m*x+c;
    }
    ld inter(line l){
        return (l.c-c)/(m-l.m);
    }
};

int n;
ll a[N],b[N],c[N];
vector<line> vec,vec2;
deque<line> dq;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++)cin >> c[i];
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<=n;i++)cin >> b[i];
    for(int i=1;i<=n;i++)vec.emplace_back(-1.0*a[i]/b[i],1.0*c[i]/b[i]);
    sort(vec.begin(),vec.end(),[&](line a,line b){
        if(a.m==b.m)return a.c<b.c;
        return a.m>b.m;
    });
    vec2.emplace_back(vec[0]);
    for(int i=1;i<n;i++)if(vec[i].m!=vec[i-1].m)vec2.emplace_back(vec[i]);
    dq.emplace_back(0,1e18);
    for(auto l:vec2){
        while(dq.size()>1&&dq.back().inter(l)<=dq[dq.size()-2].inter(l))dq.pop_back();
        dq.emplace_back(l);
    }
    while(dq.size()>1&&dq[0].inter(dq[1])<0)dq.pop_front();
    while(dq.size()>1&&dq.back().get(dq.back().inter(dq[dq.size()-2]))<0)dq.pop_back();
    dq.emplace_back(0,0);
    ld pre=0;
    ll ans=0;
    for(int i=0;i<dq.size()-1;i++){
        ld cur=dq[i].inter(dq[i+1]);
        ld x=floor(cur);
        if(x>=pre)ans=max(ans,ll(x+floor(dq[i].get(x))));
        x=ceil(pre);
        if(x<=cur)ans=max(ans,ll(x+floor(dq[i].get(x))));
        pre=cur;
    }
    cout << ans;
}