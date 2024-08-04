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
    vector<vi> id(n,vi(m)),siz(n,vi(m));
    int cur_id=0;
    for(int i=0;i<n;i++)for(int j=0;j<m;j++)if(a[i][j]=='#'&&!vis[i][j]){
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
        for(auto [x,y]:q){
            id[x][y]=cur_id;
            siz[x][y]=sz(q);
        }
        cur_id++;
    }
    int ans=0;
    for(int i=0;i<n;i++){
        int res=0;
        map<int,bool> added;
        for(int j=0;j<m;j++){
            if(a[i][j]=='#'){
                if(!added[id[i][j]]){
                    res+=siz[i][j];
                    added[id[i][j]]=true;
                }
            }else{
                res++;
                if(i>0&&a[i-1][j]=='#'&&!added[id[i-1][j]]){
                    res+=siz[i-1][j];
                    added[id[i-1][j]]=true;
                }
                if(i<n-1&&a[i+1][j]=='#'&&!added[id[i+1][j]]){
                    res+=siz[i+1][j];
                    added[id[i+1][j]]=true;
                }
            }
        }
        ans=max(ans,res);
    }
    for(int j=0;j<m;j++){
        int res=0;
        map<int,bool> added;
        for(int i=0;i<n;i++){
            if(a[i][j]=='#'){
                if(!added[id[i][j]]){
                    res+=siz[i][j];
                    added[id[i][j]]=true;
                }
            }else{
                res++;
                if(j>0&&a[i][j-1]=='#'&&!added[id[i][j-1]]){
                    res+=siz[i][j-1];
                    added[id[i][j-1]]=true;
                }
                if(j<m-1&&a[i][j+1]=='#'&&!added[id[i][j+1]]){
                    res+=siz[i][j+1];
                    added[id[i][j+1]]=true;
                }
            }
        }
        ans=max(ans,res);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}