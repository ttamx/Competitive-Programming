#include<bits/stdc++.h>

using namespace std;

template<int MOD>
struct Mint{
    int x;
    constexpr Mint(long long x=0LL):x(norm(x%MOD)){}
    constexpr int norm(int x)const{if(x<0)x+=MOD;if(x>=MOD)x-=MOD;return x;}
    explicit constexpr operator int()const{return x;}
    constexpr int mul(int a,int b){return 1LL*a*b%MOD;}
    constexpr Mint operator-()const{return Mint(-x);}
    constexpr Mint inv()const{return binpow(Mint(*this),MOD-2);}
    constexpr Mint &operator+=(const Mint &rhs){x=norm(x+rhs.x);return *this;}
    constexpr Mint &operator-=(const Mint &rhs){x=norm(x-rhs.x);return *this;}
    constexpr Mint &operator*=(const Mint &rhs){x=mul(x,rhs.x);return *this;}
    constexpr Mint &operator/=(const Mint &rhs){x=mul(x,rhs.inv().x);return *this;}
    constexpr Mint &operator++(){return *this+=1;}
    constexpr Mint &operator--(){return *this-=1;}
    constexpr Mint operator++(int){Mint res=*this;*this+=1;return res;}
    constexpr Mint operator--(int){Mint res=*this;*this-=1;return res;}
    friend constexpr Mint operator+(Mint lhs,const Mint &rhs){return lhs+=rhs;}
    friend constexpr Mint operator-(Mint lhs,const Mint &rhs){return lhs-=rhs;}
    friend constexpr Mint operator*(Mint lhs,const Mint &rhs){return lhs*=rhs;}
    friend constexpr Mint operator/(Mint lhs,const Mint &rhs){return lhs/=rhs;}
    friend istream &operator>>(istream &is,Mint &o){long long x{};is>>x;o=Mint(x);return is;}
    friend ostream &operator<<(ostream &os,const Mint &o){return os<<o.x;}
    friend constexpr bool operator==(const Mint &lhs,const Mint &rhs){return lhs.x==rhs.x;};
    friend constexpr bool operator!=(const Mint &lhs,const Mint &rhs){return lhs.x!=rhs.x;};
};
using mint = Mint<998244353>;

struct StaticTopTree{
    enum Type{Vertex,Compress,Rake,AddEdge,AddVertex};
    vector<vector<int>> &adj;
    int root;
    vector<int> p,l,r;
    vector<Type> type;
    int node_id;

    StaticTopTree(vector<vector<int>> &_adj, int _root=0):adj(_adj){
        int n=adj.size();
        p.assign(4*n,-1),l.assign(4*n,-1),r.assign(4*n,-1);
        type.assign(4*n,Type::Vertex);
        node_id=n;
        build(_root);
    }

    int dfs(int u){
        int su=1,hv=0;
        for(int &v:adj[u]){
            int sv=dfs(v);
            su+=sv;
            if(sv>hv){
                hv=sv;
                swap(v,adj[u][0]);
            }
        }
        return su;
    }
    int add(int i,int lc,int rc,Type t){
        if(i==-1)i=node_id++;
        p[i]=-1,l[i]=lc,r[i]=rc,type[i]=t;
        if(lc!=-1)p[lc]=i;
        if(rc!=-1)p[rc]=i;
        return i;
    }
    pair<int, int> merge(const vector<pair<int, int>>& a, Type t) {
        if(a.size()==1)return a[0];
        int u=0;
        for(auto &[i,s]:a)u+=s;
        vector<pair<int,int>> b,c;
        for(auto &[i,s]:a){
            (u>s?b:c).emplace_back(i,s);
            u-=s*2;
        }
        auto [i,si]=merge(b,t);
        auto [j,sj]=merge(c,t);
        return {add(-1,i,j,t),si+sj};
    }
    pair<int,int> compress(int i){
        vector<pair<int,int>> path{add_vertex(i)};
        while(!adj[i].empty())path.emplace_back(add_vertex(i=adj[i][0]));
        return merge(path,Type::Compress);
    }
    pair<int,int> rake(int i){
        vector<pair<int,int>> child;
        for(int j=1;j<adj[i].size();j++)child.emplace_back(add_edge(adj[i][j]));
        return child.empty()?make_pair(-1,0):merge(child,Type::Rake);
    }
    pair<int,int> add_edge(int i){
        auto [j,s]=compress(i);
        return {add(-1,j,-1,Type::AddEdge),s};
    }
    pair<int,int> add_vertex(int i){
        auto [j,s]=rake(i);
        return {add(i,j,-1,j==-1?Type::Vertex:Type::AddVertex),s+1};
    }
    void build(int _root){
        dfs(_root);
        root = compress(_root).first;
    }
};

using Point = mint;
struct Path{
    mint a,b;
    Path(){}
    Path(mint _a,mint _b):a(_a),b(_b){}
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,q;
    cin >> n >> q;
    vector<vector<int>> adj(n);
    for(int i=1;i<n;i++){
        int p;
        cin >> p;
        p--;
        adj[p].emplace_back(i);
    }
    vector<mint> a(n);
    for(auto &x:a)cin >> x;
    StaticTopTree stt(adj);
    vector<Point> point(4*n);
    vector<Path> path(4*n);
    auto compress=[&](Path p,Path c){
        return Path(p.a*c.a,p.a*c.b+p.b);
    };
    auto rake=[&](Point l,Point r){
        return l*r;
    };
    auto add_edge=[&](Path p){
        return p.b;
    };
    auto add_vertex=[&](Point p,int i){
        return Path(p,a[i]);
    };
    auto vertex=[&](int i){
        return Path(1,a[i]);
    };
    auto update=[&](int i){
        if(stt.type[i]==stt.Type::Compress){
            path[i]=compress(path[stt.l[i]],path[stt.r[i]]);
        }else if(stt.type[i]==stt.Type::Rake){
            point[i]=rake(point[stt.l[i]],point[stt.r[i]]);
        }else if(stt.type[i]==stt.Type::AddEdge){
            point[i]=add_edge(path[stt.l[i]]);
        }else if(stt.type[i]==stt.Type::AddVertex){
            path[i]=add_vertex(point[stt.l[i]],i);
        }else{
            path[i]=vertex(i);
        }
    };
    function<void(int)> dfs=[&](int u){
        if(u==-1)return;
        dfs(stt.l[u]);
        dfs(stt.r[u]);
        update(u);
    };
    dfs(stt.root);
    while(q--){
        int u,x;
        cin >> u >> x;
        u--;
        a[u]=x;
        for(;u!=-1;u=stt.p[u])update(u);
        cout << path[stt.root].b << "\n";
    }
}