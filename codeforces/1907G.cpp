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

void runcase(){
    int n;
    string s;
    cin >> n >> s;
    vi a(n);
    for(int i=0;i<n;i++)a[i]=s[i]-'0';
    vector<vector<pii>> adj(n);
    vi deg(n);
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        x--;
        adj[i].emplace_back(x,i);
        adj[x].emplace_back(i,i);
        deg[i]++,deg[x]++;
    }
    vi ans;
    queue<int> q;
    for(int i=0;i<n;i++)if(deg[i]==1)q.emplace(i);
    vector<bool> del(n);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        del[u]=true;
        for(auto [v,i]:adj[u])if(!del[v]){
            if(a[u]){
                ans.emplace_back(i);
                a[v]^=1;
            }
            if(--deg[v]==1)q.emplace(v);
        }
    }
    for(int i=0;i<n;i++)if(!del[i]&&a[i]){
        int u=i;
        vector<pii> p;
        int cnt=0;
        while(!del[u]){
            del[u]=true;
            cnt^=a[u];
            for(auto [v,i]:adj[u])if(!del[v]){
                p.emplace_back(u,i);
                u=v;
                break;
            }
        }
        for(auto [v,j]:adj[u])if(v==i)p.emplace_back(u,j);
        if(cnt)return void(cout << "-1\n");
        vi d[2];
        int c=0;
        for(auto [u,i]:p){
            c^=a[u];
            d[c].emplace_back(i);
        }
        if(sz(d[0])>sz(d[1]))swap(d[0],d[1]);
        for(auto x:d[0])ans.emplace_back(x);
    }
    cout << ans.size() << "\n";
    for(auto x:ans)cout << x+1 << " ";
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}