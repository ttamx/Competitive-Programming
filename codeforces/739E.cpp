#include<bits/stdc++.h>

using namespace std;

typedef long double ld;

const int N=2005;
const ld eps=1e-15;

int n,a,b;
ld p[N],u[N];

struct item{
    ld val;
    int p,u;
    item():val(0),p(0),u(0){}
    item(ld val,int p,int u):val(val),p(p),u(u){}
    bool operator<(const item &o)const{
        if(abs(val-o.val)>eps)return val<o.val;
        if(p!=o.p)return p<o.p;
        return u<o.u;
    }
}dp[N];

item calc(ld x,ld y){
    for(int i=1;i<=n;i++){
        dp[i]=dp[i-1];
        dp[i]=max(dp[i],item(dp[i-1].val+p[i]-x,dp[i-1].p+1,dp[i-1].u));
        dp[i]=max(dp[i],item(dp[i-1].val+u[i]-y,dp[i-1].p,dp[i-1].u+1));
        dp[i]=max(dp[i],item(dp[i-1].val+p[i]+u[i]-p[i]*u[i]-x-y,dp[i-1].p+1,dp[i-1].u+1));
    }
    return dp[n];
}

item calc2(ld x){
    ld l=0,r=1;
    while(r-l>eps){
        ld m=(l+r)/2;
        if(calc(x,m).u>=b)l=m;
        else r=m;
    }
    auto res=calc(x,l);
    res.val+=b*l;
    return res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> a >> b;
    for(int i=1;i<=n;i++)cin >> p[i];
    for(int i=1;i<=n;i++)cin >> u[i];
    ld ans=0;
    ld l=0,r=1;
    while(r-l>eps){
        ld m=(l+r)/2;
        if(calc2(m).p>=a)l=m;
        else r=m;
    }
    cout << fixed << setprecision(15) << calc2(l).val+a*l << "\n";
}