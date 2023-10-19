#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

struct convex_t{
    struct line_t{
        ll m,c;
        line_t(ll m,ll c):m(m),c(c){}
        ll get(ll x){
            return m*x+c;
        }
    };
    deque<line_t> hull;
    bool bad(line_t l1,line_t l2,line_t l3){
        return (l3.c-l1.c)*(l1.m-l2.m)<=(l2.c-l1.c)*(l1.m-l3.m);
    }
    void add(ll m,ll c){
        line_t l(m,c);
        while(hull.size()>=2&&bad(hull.end()[-2],hull.back(),l))hull.pop_back();
        hull.emplace_back(l);
    }
    ll query(ll x){
        while(hull.size()>1&&hull[0].get(x)<=hull[1].get(x))hull.pop_front();
        return hull[0].get(x);
    }
};

void runcase(){
    int n;
    ll a,b,c;
    cin >> n >> a >> b >> c;
    vector<ll> x(n+2),qs(n+2),dp(n+2);
    for(int i=1;i<=n;i++)cin >> x[i];
    for(int i=1;i<=n;i++)qs[i]=qs[i-1]+x[i];
    convex_t ch;
    ch.add(0,0);
    for(int i=1;i<=n;i++){
        dp[i]=a*qs[i]*qs[i]+b*qs[i]+c+ch.query(qs[i]);
        ch.add(-2*a*qs[i],a*qs[i]*qs[i]-b*qs[i]+dp[i]);
    }
    cout << dp[n] << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}