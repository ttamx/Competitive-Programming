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
    vector<vi> a(n,vi(m)),d(n,vi(m,INF));
    for(auto &x:a)for(auto &y:x)cin >> y;
    queue<pair<int,int>> q;
    d[0][0]=0;
    q.emplace(0,0);
    auto go=[&](int i,int j,int nd){
        if(a[i][j]||d[i][j]!=INF)return;
        d[i][j]=nd;
        q.emplace(i,j);
    };
    while(!q.empty()){
        auto [i,j]=q.front();
        q.pop();
        if(!a[(i+1)%n][j])go((i+2)%n,j,d[i][j]+1);
        go((i+1)%n,j+1,d[i][j]+1);
    }
    int ans=INF;
    for(int i=0;i<n;i++){
        int t=d[i][m-1];
        if(t==INF)continue;
        int p=(n-1+t)%n;
        if(p>i)p-=n;
        t+=i-p;
        ans=min(ans,t);
    }
    cout << (ans==INF?-1:ans) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}