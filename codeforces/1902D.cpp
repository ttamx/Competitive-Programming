#include<bits/stdc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()

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
const int MOD=1000000007;
// const int MOD=998224353;
const ll LINF=0x1fffffffffffffff;
const db DINF=numeric_limits<db>::infinity();
const db EPS=1e-9;
const db PI=acos(db(-1));

const int N=2e5+5;

int n,q;
string s;
bool ans[N];
int x[N],y[N],qx[N],qy[N],l[N],r[N];
map<pii,int> vis;
vector<int> pre[N],suf[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    cin >> s;
    s=" "+s+" ";
    for(int i=1;i<=n+1;i++){
        x[i]=x[i-1],y[i]=y[i-1];
        if(s[i]=='U')y[i]++;
        if(s[i]=='D')y[i]--;
        if(s[i]=='L')x[i]--;
        if(s[i]=='R')x[i]++;
    }
    for(int i=1;i<=q;i++){
        cin >> qx[i] >> qy[i] >> l[i] >> r[i];
        pre[l[i]].emplace_back(i);
        suf[r[i]].emplace_back(i);
    }
    vis[{0,0}]=true;
    for(int i=1;i<=n;i++){
        for(auto j:pre[i])ans[j]|=vis[{qx[j],qy[j]}];
        vis[{x[i],y[i]}]=1;
    }
    vis.clear();
    for(int i=n;i>=1;i--){
        vis[{x[i],y[i]}]=1;
        for(auto j:suf[i])ans[j]|=vis[{qx[j],qy[j]}];
    }
    vis.clear();
    vis[{0,0}]=0;
    for(int i=1;i<=n;i++){
        vis[{x[i],y[i]}]=i;
        for(auto j:suf[i]){
            int p=l[j]-1;
            int dx=qx[j]-x[p];
            int dy=qy[j]-y[p];
            int nx=x[i]-dx,ny=y[i]-dy;
            ans[j]|=vis[{nx,ny}]>p;
        }
    }
    for(int i=1;i<=q;i++)cout << (ans[i]?"YES":"NO") << "\n";
}