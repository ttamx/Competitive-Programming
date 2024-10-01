#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

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

template<class T>
using ordered_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
template<class T>
using ordered_multiset = tree<T,null_type,less_equal<T>,rb_tree_tag,tree_order_statistics_node_update>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());

void runcase(){
    string s;
    cin >> s;
    int n=s.size();
    int m=26*26;
    auto encode=[&](char a,char b){
        return int((a-'a')*26+b-'a');
    };
    vector<vector<int>> l(n+1,vector<int>(m,-1)),r(n+1,vector<int>(m,n));
    vector<vector<int>> comp(m);
    for(int i=1;i<n;i++){
        int u=encode(s[i-1],s[i]);
        comp[u].emplace_back(i);
    }
    for(int i=1;i<n;i++){
        l[i]=l[i-1];
        l[i][encode(s[i-1],s[i])]=i;
    }
    for(int i=n-1;i>=1;i--){
        r[i]=r[i+1];
        r[i][encode(s[i-1],s[i])]=i;
    }
    int q;
    cin >> q;
    vector<pair<int,int>> qr(q);
    vector<int> ans(q);
    for(int i=0;i<q;i++){
        auto &[l,r]=qr[i];
        cin >> l >> r;
        ans[i]=abs(r-l);
    }
    for(int i=0;i<m;i++){
        queue<int> qu;
        vector<int> dist(n,INF);
        vector<bool> vis(m);
        vis[i]=true;
        for(auto u:comp[i]){
            dist[u]=0;
            qu.emplace(u);
        }
        while(!qu.empty()){
            int u=qu.front();
            qu.pop();
            if(u>1&&dist[u-1]==INF){
                dist[u-1]=dist[u]+1;
                qu.emplace(u-1);
            }
            if(u+1<n-1&&dist[u+1]==INF){
                dist[u+1]=dist[u]+1;
                qu.emplace(u+1);
            }
            int c=encode(s[u-1],s[u]);
            if(!vis[c]){
                vis[c]=true;
                for(auto v:comp[c]){
                    if(dist[v]==INF){
                        dist[v]=dist[u]+1;
                        qu.emplace(v);
                    }
                }
            }
        }
        for(int j=0;j<q;j++){
            auto [x,y]=qr[j];
            int d=INF;
            if(l[x][i]!=-1)d=min(d,x-l[x][i]);
            if(r[x][i]!=n)d=min(d,r[x][i]-x);
            ans[j]=min(ans[j],d+dist[y]+1);
        }
        for(int j=0;j<q;j++){
            auto [y,x]=qr[j];
            int d=INF;
            if(l[x][i]!=-1)d=min(d,x-l[x][i]);
            if(r[x][i]!=n)d=min(d,r[x][i]-x);
            ans[j]=min(ans[j],d+dist[y]+1);
        }
    }
    for(int i=0;i<q;i++){
        cout << ans[i] << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}