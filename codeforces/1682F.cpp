#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=2e5+5;
const int MOD=1e9+7;

int n,q;
ll a[N],b[N],qs[N],c[N];
vector<tuple<ll,int,int>> qr[N];
ll ans[N];

inline ll norm(ll x){return (x%=MOD)<0?x+MOD:x;}
inline ll add(ll x,ll y){return (x+=y)>=MOD?x-MOD:x;}

struct Fenwick{
    ll t[N];
    void update(int i,ll v){
        v=norm(v);
        for(;i<=n;i+=i&-i)t[i]=add(t[i],v);
    }
    ll query(int i){
        ll res=0;
        for(;i>0;i-=i&-i)res=add(res,t[i]);
        return res;
    }
    void update(int l,int r,ll v){
        update(l,v);
        update(r,-v);
    }
}f1,f2;

inline int lb(ll v){return lower_bound(c,c+n,v)-c+1;}
inline int ub(ll v){return upper_bound(c,c+n,v)-c+1;}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<=n;i++)cin >> b[i];
    for(int i=1;i<=n;i++)qs[i]=qs[i-1]+b[i];
    for(int i=1;i<=n;i++)c[i]=qs[i];
    sort(c,c+n);
    for(int i=1;i<=q;i++){
        int l,r;
        cin >> l >> r;
        qr[l].emplace_back(qs[l-1],i,1);
        qr[r].emplace_back(qs[l-1],i,-1);
    }
    for(int i=n;i>=1;i--){
        if(b[i]>0){
            int l=ub(qs[i]),r=ub(qs[i]+b[i]);
            f1.update(1,l,-a[i]*b[i]);
            f1.update(l,r,norm(-b[i]-2*qs[i])*a[i]);
            f2.update(l,r,2*a[i]);
            f1.update(r,a[i]*b[i]);
        }else if(b[i]<0){
            int l=ub(qs[i]+b[i]),r=ub(qs[i]);
            f1.update(1,l,-a[i]*b[i]);
            f1.update(l,r,norm(-b[i]-2*(qs[i]+b[i]))*a[i]);
            f2.update(l,r,-2*a[i]);
            f1.update(r,a[i]*b[i]);
        }
        for(auto [s,j,m]:qr[i]){
            int p=lb(s);
            ans[j]=add(ans[j],norm((f1.query(p)+s*f2.query(p))*m));
        }
    }
    for(int i=1;i<=q;i++){
        cout << ans[i] << "\n";
    }
}