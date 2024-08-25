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
    int mx=0;
    vector<pair<int,int>> edges;
    map<int,int> cnt;
    for(int i=0;i<n;i++){
        int s;
        cin >> s;
        mx=max(mx,s+3);
        vector<bool> seen(s+3);
        for(int i=0;i<s;i++){
            int x;
            cin >> x;
            if(x<s+3)seen[x]=true;
        }
        int u=0;
        while(seen[u])u++;
        int v=u+1;
        while(seen[v])v++;
        edges.emplace_back(u,v);
        cnt[u]++;
    }
    vector<vector<int>> adj(mx);
    for(auto [u,v]:edges){
        adj[u].emplace_back(v);
    }
    vector<int> dp(mx);
    for(int i=mx-1;i>=0;i--){
        dp[i]=i;
        for(auto j:adj[i]){
            dp[i]=max(dp[i],dp[j]);
        }
    }
    long long ans=0;
    int val=0;
    for(auto [i,x]:cnt){
        if(x>=2){
            val=max(val,dp[i]);
        }else{
            val=max(val,i);
        }
    }
    mx=min(mx,m+1);
    for(int i=0;i<mx;i++){
        ans+=max(val,dp[i]);
    }
    int pos=min(max(val,mx),m+1);
    ans+=1LL*(pos-mx)*val;
    ans+=1LL*(m+pos)*(m-pos+1)/2;
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}