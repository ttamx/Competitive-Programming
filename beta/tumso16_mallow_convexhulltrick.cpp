#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1e5+5;

struct convexhulltrick{
    struct line{
        ll m,c;
        line(ll m,ll c):m(m),c(c){}
        ll get(ll x){
            return m*x+c;
        }
    };
    bool bad(line l1,line l2,line l3){
        return (__int128_t)(l3.c-l1.c)*(l1.m-l2.m)<=(__int128_t)(l2.c-l1.c)*(l1.m-l3.m);
    }
    deque<line> hull;
    void add(ll m,ll c){
        line l(m,c);
        while(hull.size()>1&&bad(hull.end()[-2],hull.back(),l))hull.pop_back();
        hull.emplace_back(l);
    }
    ll get(ll x){
        while(hull.size()>1&&hull[1].get(x)<=hull[0].get(x))hull.pop_front();
        return hull[0].get(x);
    }
};

int n,k;
ll w[N],f[N],g[N];
ll dp;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for(int i=1;i<=n;i++)cin >> w[i];
    for(int i=1;i<=n;i++)f[i]=f[i-1]+w[i];
    for(int i=1;i<=n;i++)g[i]=g[i-1]+i*w[i];
    convexhulltrick hull;
    hull.add(-1,0);
    for(int i=1;i<=k;i++){
        convexhulltrick newhull;
        for(int j=1;j<=n;j++){
            dp=g[j]+hull.get(f[j]);
            newhull.add(-j-1,dp-g[j]+(j+1)*f[j]);
        }
        swap(hull,newhull);
    }
    cout << dp;
}