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
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
        x--;
    }
    vector<int> deg(n);
    vector<bool> vis(n);
    for(int i=0;i<n;i++)deg[a[i]]++;
    queue<int> q;
    vector<int> ord;
    for(int i=0;i<n;i++)if(!deg[i])q.push(i);
    while(!q.empty()){
        int x=q.front();
        q.pop();
        ord.push_back(x);
        vis[x]=true;
        deg[a[x]]--;
        if(deg[a[x]]==0)q.push(a[x]);
    }
    vector<int> dp(n);
    for(int i=0;i<n;i++)if(!vis[i]){
        vector<int> path;
        int x=i;
        while(!vis[x]){
            path.push_back(x);
            vis[x]=true;
            x=a[x];
        }
        for(auto x:path)dp[x]=sz(path);
    }
    reverse(all(ord));
    for(auto x:ord)dp[x]=dp[a[x]]+1;
    cout << accumulate(all(dp),0ll) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}