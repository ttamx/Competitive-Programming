#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1e5+5;
const int K=205;
const ll inf=1e18;

int n,k;
int a[N];
ll qs[N],dp[2][N];
int opt[K][N];

struct convexhull{
    struct line{
        ll m,c;
        int id;
        line(){}
        line(ll m,ll c,int id):m(m),c(c),id(id){}
        ll get(ll x){
            return m*x+c;
        }
    };
    bool bad(line l1,line l2,line l3){
        return (l3.c-l1.c)*(l1.m-l2.m)<=(l2.c-l1.c)*(l1.m-l3.m);
    }
    deque<line> hull;
    void init(){
        hull.clear();
    }
    void insert(ll m,ll c,int id){
        line l(m,c,id);
        while(hull.size()>1&&bad(hull.end()[-2],hull.back(),l))hull.pop_back();
        hull.emplace_back(l);
    }
    pair<ll,int> query(ll x){
        while(hull.size()>1&&hull[1].get(x)>=hull[0].get(x))hull.pop_front();
        return {hull[0].get(x),hull[0].id};
    }
}hull;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<=n;i++)qs[i]=qs[i-1]+a[i];
    for(int i=1;i<=k;i++){
        hull.init();
        hull.insert(0,0,0);
        for(int j=1;j<=n;j++){
            auto [val,id]=hull.query(qs[j]);
            dp[i&1][j]=qs[j]*(qs[n]-qs[j])+val;
            opt[i][j]=id;
            hull.insert(qs[j],-qs[j]*qs[n]+dp[i&1^1][j],j);
        }
    }
    ll ans=-inf;
    int id=0;
    for(int i=k;i<=n;i++){
        if(dp[k&1][i]>ans){
            ans=dp[k&1][i];
            id=i;
        }
    }
    vector<int> res;
    for(int i=k;i>=1;i--){
        res.emplace_back(id);
        id=opt[i][id];
    }
    reverse(res.begin(),res.end());
    cout << ans << "\n";
    for(auto x:res)cout << x << " ";
}