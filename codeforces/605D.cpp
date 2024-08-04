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

struct Info{
    int x,y,t;
    Info(int _x,int _y,int _t):x(_x),y(_y),t(_t){}
    bool operator<(const Info &o)const{
        if(x!=o.x)return x<o.x;
        if(y!=o.y)return y<o.y;
        return t<o.t;
    }
};

void runcase(){
    int n;
    cin >> n;
    vector<Info> a;
    vector<vector<pair<int,int>>> adj;
    int m=0;
    auto add_node=[&](int x,int y,int t){
        a.emplace_back(Info(x,y,t));
        adj.emplace_back();
        return m++;
    };
    auto new_node=[&](){
        adj.emplace_back();
        return m++;
    };
    auto add_edge=[&](int u,int v,int w){
        adj[u].emplace_back(v,w);
    };
    add_node(0,0,1);
    for(int i=0;i<n;i++){
        int a,b,c,d;
        cin >> a >> b >> c >> d;
        int u=add_node(a,b,0);
        int v=add_node(c,d,1);
        add_edge(u,v,1);
    }
    vector<int> ord(m);
    iota(ord.begin(),ord.end(),0);
    sort(ord.begin(),ord.end(),[&](int i,int j){
        return a[i]<a[j];
    });
    vector<int> aux(m),tmp(m);
    function<void(int,int)> dnc=[&](int l,int r){
        if(l==r)return;
        int m=(l+r)/2;
        dnc(l,m);
        dnc(m+1,r);
        int pre=-1;
        for(int i=l;i<=m;i++){
            aux[i]=new_node();
            if(a[ord[i]].t==0)add_edge(aux[i],ord[i],0);
            if(i>l)add_edge(aux[i],aux[i-1],0);
        }
        for(int i=m+1,j=l;i<=r;i++){
            if(a[ord[i]].t==0)continue;
            while(j<=m&&a[ord[j]].y<=a[ord[i]].y)j++;
            if(j>l)add_edge(ord[i],aux[j-1],0);
        }
        for(int i=l,j=m+1,p=l;p<=r;p++){
            if(j>r||(i<=m&&a[ord[i]].y<a[ord[j]].y)){
                tmp[p]=ord[i];
                i++;
            }else{
                tmp[p]=ord[j];
                j++;
            }
        }
        for(int i=l;i<=r;i++)ord[i]=tmp[i];
    };
    dnc(0,m-1);
    deque<int> q;
    vector<int> dp(m,-1),par(m,-1);
    dp[0]=0;
    q.emplace_back(0);
    while(!q.empty()){
        int u=q.front();
        q.pop_front();
        for(auto [v,w]:adj[u]){
            if(dp[v]==-1){
                dp[v]=dp[u]+w;
                par[v]=u;
                if(w){
                    q.emplace_back(v);
                }else{
                    q.emplace_front(v);
                }
            }
        }
    }
    if(dp[n*2]==-1){
        cout << -1 << "\n";
    }else{
        cout << dp[n*2] << "\n";
        vector<int> path;
        for(int u=n*2;u!=0;u=par[u]){
            if(u<=2*n&&u%2==0){
                path.emplace_back(u/2);
            }
        }
        reverse(path.begin(),path.end());
        for(auto x:path)cout << x << " ";
        cout << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}