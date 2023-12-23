#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1e5+5;
const ll inf=1e18;

int n,m,p;
ll d[N],a[N],qs[N];
ll dp[2][N];

struct convexhulltrick{
    struct line{
        ll m,c;
        line(ll m,ll c):m(m),c(c){}
        ll get(ll x){
            return m*x+c;
        }
    };
    deque<line> dq;
    bool bad(line x,line y,line z){
        return 1.l*(x.c-y.c)*(z.m-x.m)>=1.l*(x.c-z.c)*(y.m-x.m);
    }
    void clear(){
        dq.clear();
    }
    void insert(ll m,ll c){
        auto l=line(m,c);
        while(dq.size()>1&&bad(dq.end()[-2],dq.back(),l))dq.pop_back();
        dq.emplace_back(l);
    }
    ll get(ll x){
        while(dq.size()>1&&dq[0].get(x)>dq[1].get(x))dq.pop_front();
        return dq[0].get(x);
    }
}cht;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> p;
    for(int i=2;i<=n;i++)cin >> d[i],d[i]+=d[i-1];
    for(int i=1;i<=m;i++){
        int h,t;
        cin >> h >> t;
        a[i]=t-d[h];
    }
    sort(a+1,a+m+1);
    for(int i=1;i<=m;i++)qs[i]=qs[i-1]+a[i];
    for(int i=0;i<=m;i++)dp[0][i]=inf;
    for(int i=1;i<=p;i++){
        cht.clear();
        cht.insert(0,0);
        for(int j=1;j<=m;j++){
            dp[i&1][j]=j*a[j]-qs[j]+cht.get(a[j]);
            if(i>1)cht.insert(-j,dp[i&1^1][j]+qs[j]);
        }
    }
    cout << dp[p&1][m] << "\n";
}