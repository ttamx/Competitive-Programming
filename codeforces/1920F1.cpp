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

namespace std {

template<class Fun>
class y_combinator_result {
    Fun fun_;
public:
    template<class T>
    explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}

    template<class ...Args>
    decltype(auto) operator()(Args &&...args) {
        return fun_(std::ref(*this), std::forward<Args>(args)...);
    }
};

template<class Fun>
decltype(auto) y_combinator(Fun &&fun) {
    return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}

} // namespace std

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m,q;
    cin >> n >> m >> q;
    vector<string> g(n);
    vector<pii> v,isl;
    for(auto &x:g)cin >> x;
    for(int i=0;i<n;i++)for(int j=0;j<m;j++)if(g[i][j]=='v')v.emplace_back(i,j);
    for(int i=0;i<n;i++)for(int j=0;j<m;j++)if(g[i][j]=='#')isl.emplace_back(i,j);
    auto inside=[&](int x,int y){
        return 0<=x&&x<n&&0<=y&&y<=m;
    };
    auto check=[&](int sx,int sy,int d){
        auto qu=v;
        vector<vector<bool>> vis(n,vector<bool>(m));
        auto vis2=vis,vis3=vis;
        for(auto [x,y]:qu)vis[x][y]=true;
        for(int i=1;i<d;i++){
            vector<pii> nq;
            for(auto [x,y]:qu){
                auto go=[&](int dx,int dy){
                    dx+=x,dy+=y;
                    if(!inside(dx,dy)||vis[dx][dy])return;
                    nq.emplace_back(dx,dy);
                    vis[dx][dy]=true;
                };
                go(-1,0);
                go(1,0);
                go(0,-1);
                go(0,1);
            }
            swap(qu,nq);
        }
        if(vis[sx][sy])return false;
        queue<pii> q;
        q.emplace(sx,sy);
        vis2[sx][sy]=true;
        while(!q.empty()){
            auto [x,y]=q.front();
            q.pop();
            auto go=[&](int dx,int dy){
                dx+=x,dy+=y;
                if(!inside(dx,dy)||vis[dx][dy]||vis2[dx][dy]||g[dx][dy]=='#')return;
                q.emplace(dx,dy);
                vis2[dx][dy]=true;
            };
            go(-1,0);
            go(1,0);
            go(0,-1);
            go(0,1);
        }
        for(auto [x,y]:isl){
            q.emplace(x,y);
            vis3[x][y]=true;
        }
        while(!q.empty()){
            auto [x,y]=q.front();
            q.pop();
            if(x==0||x==n-1||y==0||y==m-1)return false;
            auto go=[&](int dx,int dy){
                dx+=x,dy+=y;
                if(!inside(dx,dy)||vis2[dx][dy]||vis3[dx][dy])return;
                q.emplace(dx,dy);
                vis3[dx][dy]=true;
            };
            for(int i=-1;i<=1;i++)for(int j=-1;j<=1;j++)go(i,j);
        }
        return true;
    };
    while(q--){
        int x,y;
        cin >> x >> y;
        x--,y--;
        int l=0,r=n+m;
        while(l<r){
            int mid=(l+r+1)/2;
            if(check(x,y,mid))l=mid;
            else r=mid-1;
        }
        cout << l << "\n";
    }
}