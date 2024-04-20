#include<bits/stdc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()

using namespace std;

using ll = long long;
using db = long double;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<db>;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using pdd = pair<db,db>;
const int INF=0x3fffffff;
// const int MOD=1000000007;
const int MOD=998244353;
const ll LINF=0x1fffffffffffffff;
const db DINF=numeric_limits<db>::infinity();
const db EPS=1e-9;
const db PI=acos(db(-1));

using G=array<array<int,3>,3>;

ll a[3][3];
map<G,ll> dp;

ll solve(G g,int t){
    auto it=dp.find(g);
    if(it!=dp.end())return it->second;
    auto &x=dp[g];
    for(int i=0;i<3;i++)if(g[i][0]&&g[i][0]==g[i][1]&&g[i][0]==g[i][2])return x=(g[i][0]==1?LINF:-LINF);
    for(int i=0;i<3;i++)if(g[0][i]&&g[0][i]==g[1][i]&&g[0][i]==g[2][i])return x=(g[0][i]==1?LINF:-LINF);
    if(g[0][0]&&g[0][0]==g[1][1]&&g[0][0]==g[2][2])return x=(g[1][1]==1?LINF:-LINF);
    if(g[0][2]&&g[0][2]==g[1][1]&&g[0][2]==g[2][0])return x=(g[1][1]==1?LINF:-LINF);
    if(t==1){
        x=-LINF;
        bool ok=false;
        for(int i=0;i<3;i++)for(int j=0;j<3;j++)if(!g[i][j]){
            ok=true;
            g[i][j]=1;
            x=max(x,solve(g,2)+a[i][j]);
            g[i][j]=0;
        }
        if(!ok)x=0;
    }else{
        x=LINF;
        bool ok=false;
        for(int i=0;i<3;i++)for(int j=0;j<3;j++)if(!g[i][j]){
            ok=true;
            g[i][j]=2;
            x=min(x,solve(g,1)-a[i][j]);
            g[i][j]=0;
        }
        if(!ok)x=0;
    }
    return x;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=0;i<3;i++)for(int j=0;j<3;j++)cin >> a[i][j];
    G g;
    for(auto &x:g)for(auto &y:x)y=0;
    cout << (solve(g,1)>0?"Takahashi":"Aoki");
}