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
    int n;
    cin >> n;
    vector a(n,vector<db>(n));
    for(auto &v:a)for(auto &x:v){
        ll v;
        cin >> v;
        x=db(v)/100;
    }
    vector<db> dp(n,DINF),mul(n,db(1)),add(n,db(0));
    vector<bool> vis(n);
    dp[n-1]=0;
    for(int i=0;i<n;i++){
        int u=-1;
        for(int j=0;j<n;j++)if(!vis[j]){
            if(u==-1||dp[j]<dp[u])u=j;
        }
        vis[u]=true;
        db e=dp[u];
        for(int v=0;v<n;v++)if(!vis[v]){
            add[v]+=mul[v]*a[v][u]*dp[u];
            mul[v]*=(1-a[v][u]);
            if(1-mul[v]>EPS)dp[v]=(1+add[v])/(1-mul[v]);
        }
    }
    cout << fixed << setprecision(15);
    cout << dp[0] << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}