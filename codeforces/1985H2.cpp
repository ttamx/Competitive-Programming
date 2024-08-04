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

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<string> a(n);
    for(auto &x:a)cin >> x;
    vector<vector<bool>> vis(n,vector<bool>(m));
    vector<vi> b(n+1,vi(m+1));
    auto add_rect=[&](int x1,int x2,int y1,int y2,int v){
        x2++,y2++;
        b[x1][y1]+=v;
        b[x2][y2]+=v;
        b[x1][y2]-=v;
        b[x2][y1]-=v;
    };
    auto add_cross=[&](int x1,int x2,int y1,int y2,int v){
        add_rect(x1,x2,0,m-1,v);
        add_rect(0,n-1,y1,y2,v);
        add_rect(x1,x2,y1,y2,-v);
    };
    for(int i=0;i<n;i++)for(int j=0;j<m;j++)if(!vis[i][j]&&a[i][j]=='#'){
        vector<pii> q;
        q.emplace_back(i,j);
        vis[i][j]=true;
        for(int k=0;k<sz(q);k++){
            auto [x,y]=q[k];
            if(x>0&&!vis[x-1][y]&&a[x-1][y]=='#'){
                q.emplace_back(x-1,y);
                vis[x-1][y]=true;
            }
            if(x<n-1&&!vis[x+1][y]&&a[x+1][y]=='#'){
                q.emplace_back(x+1,y);
                vis[x+1][y]=true;
            }
            if(y>0&&!vis[x][y-1]&&a[x][y-1]=='#'){
                q.emplace_back(x,y-1);
                vis[x][y-1]=true;
            }
            if(y<m-1&&!vis[x][y+1]&&a[x][y+1]=='#'){
                q.emplace_back(x,y+1);
                vis[x][y+1]=true;
            }
        }
        int cnt=sz(q);
        int x1=INF,x2=-INF,y1=INF,y2=-INF;
        for(auto [x,y]:q){
            x1=min(x1,x);
            x2=max(x2,x);
            y1=min(y1,y);
            y2=max(y2,y);
        }
        x1=max(0,x1-1);
        x2=min(n-1,x2+1);
        y1=max(0,y1-1);
        y2=min(m-1,y2+1);
        add_cross(x1,x2,y1,y2,cnt);
    }
    for(int i=0;i<n;i++)for(int j=0;j<m;j++)if(!vis[i][j]){
        add_cross(i,i,j,j,1);
    }
    int ans=0;
    for(int i=0;i<n;i++)for(int j=0;j<m;j++){
        if(i)b[i][j]+=b[i-1][j];
        if(j)b[i][j]+=b[i][j-1];
        if(i&&j)b[i][j]-=b[i-1][j-1];
        ans=max(ans,b[i][j]);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}