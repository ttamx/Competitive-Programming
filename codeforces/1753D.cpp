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
    ll p,q;
    cin >> p >> q;
    vector<string> a(n);
    for(auto &x:a)cin >> x;
    using T= tuple<ll,ll,ll>;
    vector<vector<vector<T>>> adj(n,vector<vector<T>>(m));
    auto valid=[&](int i,int j){
        return 0<=i&&i<n&&0<=j&&j<m&&a[i][j]!='#';
    };
    auto add_edge=[&](int ui,int uj,int vi,int vj,ll w){
        if(!valid(ui,uj)||!valid(vi,vj))return;
        assert((ui+uj)%2==(vi+vj)%2);
        adj[ui][uj].emplace_back(vi,vj,w);
    };
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(a[i][j]=='L'){
                add_edge(i,j+2,i,j,q);
                add_edge(i-1,j+1,i,j,p);
                add_edge(i+1,j+1,i,j,p);
            }
            if(a[i][j]=='R'){
                add_edge(i,j-2,i,j,q);
                add_edge(i-1,j-1,i,j,p);
                add_edge(i+1,j-1,i,j,p);
            }
            if(a[i][j]=='U'){
                add_edge(i+2,j,i,j,q);
                add_edge(i+1,j-1,i,j,p);
                add_edge(i+1,j+1,i,j,p);
            }
            if(a[i][j]=='D'){
                add_edge(i-2,j,i,j,q);
                add_edge(i-1,j-1,i,j,p);
                add_edge(i-1,j+1,i,j,p);
            }
        }
    }
    priority_queue<T,vector<T>,greater<T>> pq;
    vector dist(n,vector<ll>(m,LINF));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(a[i][j]=='.'){
                pq.emplace(0,i,j);
                dist[i][j]=0;
            }
        }
    }
    while(!pq.empty()){
        auto [d,i,j]=pq.top();
        pq.pop();
        if(d>dist[i][j])continue;
        for(auto [ni,nj,w]:adj[i][j]){
            if(d+w<dist[ni][nj]){
                dist[ni][nj]=d+w;
                pq.emplace(d+w,ni,nj);
            }
        }
    }
    ll ans=LINF;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(valid(i,j+1)){
                ans=min(ans,dist[i][j]+dist[i][j+1]);
            }
            if(valid(i+1,j)){
                ans=min(ans,dist[i][j]+dist[i+1][j]);
            }
        }
    }
    cout << (ans<LINF?ans:-1LL) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}