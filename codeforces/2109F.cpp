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

int dx[4]={-1,0,1,0};
int dy[4]={0,1,0,-1};

void runcase(){
    int n,p,k;
    cin >> n >> p >> k;
    p--;
    vector<vector<int>> a(n,vector<int>(n));
    for(auto &v:a){
        for(auto &x:v){
            cin >> x;
        }
    }
    vector<string> s(n);
    for(auto &x:s)cin >> x;
    int ans1,ans2;
    {
        vector<vector<int>> dist(n,vector<int>(n,INF));
        using T = tuple<int,int,int>;
        priority_queue<T,vector<T>,greater<T>> pq;
        auto push=[&](int d,int i,int j){
            d=max(d,a[i][j]);
            if(d<dist[i][j])pq.emplace(dist[i][j]=d,i,j);
        };
        push(0,p,n-1);
        while(!pq.empty()){
            auto [d,i,j]=pq.top();
            pq.pop();
            if(d>dist[i][j])continue;
            for(int dir=0;dir<4;dir++){
                int ii=i+dx[dir],jj=j+dy[dir];
                if(0<=ii&&ii<n&&0<=jj&&jj<n)push(d,ii,jj);
            }
        }
        ans1=dist[0][0];
        ans2=dist[n-1][0];
    }
    vector<vector<bool>> vis(n,vector<bool>(n));
    {
        queue<pair<int,int>> q;
        auto push=[&](int i,int j){
            if(vis[i][j])return;
            vis[i][j]=true;
            q.emplace(i,j);
        };
        for(int i=0;i<n;i++)push(0,i);
        for(int i=1;i<=p;i++)push(i,n-1);
        while(!q.empty()){
            auto [i,j]=q.front();
            q.pop();
            if(a[i][j]<=ans1)continue;
            for(int di=-1;di<=1;di++){
                for(int dj=-1;dj<=1;dj++){
                    int ii=i+di,jj=j+dj;
                    if(0<=ii&&ii<n&&0<=jj&&jj<n)push(ii,jj);
                }
            }
        }
    }
    auto check=[&](int m)->bool {
        vector<vector<int>> b(n,vector<int>(n));
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(a[i][j]<m)b[i][j]=(s[i][j]=='1'?m-a[i][j]:INF);
                else b[i][j]=0;
                if(vis[i][j]&&m>ans1)b[i][j]=INF;
            }
        }
        vector<vector<int>> dist(n,vector<int>(n,INF));
        using T = tuple<int,int,int>;
        priority_queue<T,vector<T>,greater<T>> pq;
        auto push=[&](int d,int i,int j){
            d+=b[i][j];
            if(d<dist[i][j])pq.emplace(dist[i][j]=d,i,j);
        };
        for(int i=0;i<n;i++)push(0,0,i);
        for(int i=1;i<n;i++)push(0,i,0);
        for(int i=1;i<=p;i++)push(0,i,n-1);
        while(!pq.empty()){
            auto [d,i,j]=pq.top();
            pq.pop();
            if(d>k)break;
            if(i==n-1||(j==n-1&&i>=p))return true;
            if(d>dist[i][j])continue;
            for(int di=-1;di<=1;di++){
                for(int dj=-1;dj<=1;dj++){
                    int ii=i+di,jj=j+dj;
                    if(0<=ii&&ii<n&&0<=jj&&jj<n)push(d,ii,jj);
                }
            }
        }
        return false;
    };
    int l=ans2,r=2e6;
    while(l<r){
        int m=(l+r+1)/2;
        if(check(m))l=m;
        else r=m-1;
    }
    cout << ans1 << " " << l << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}