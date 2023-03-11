#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

//BINPOW
template<class T>
T binpow(T num,long long pow){
    T res=1;
    for(;pow;num*=num,pow>>=1)if(pow&1)res*=num;
    return res;
}
//--------------------------------------------------------
//MODULAR
long long mod=1e9+7;

struct modular{
    long long val;
    modular(long long x=0){ val=x%mod; if(val<0)val+=mod;}
    modular inv()const{return binpow(*this,mod-2);}
    modular& operator+=(const modular&o){val=(val+o.val)%mod; return *this;}
    modular& operator-=(const modular&o){val=(val-o.val+mod)%mod; return *this;}
    modular& operator*=(const modular&o){val=(val*o.val)%mod; return *this;}
    modular& operator/=(const modular&o){val=(val*o.inv().val)%mod; return *this;}
    modular& operator++(){return *this+=1;}
    modular& operator--(){return *this-=1;}
    modular operator++(int){modular ret=*this; *this+=1; return ret;}
    modular operator--(int){modular ret=*this; *this-=1; return ret;}
    friend modular operator+(const modular &lhs,const modular &rhs){return modular(lhs)+=rhs;}
    friend modular operator-(const modular &lhs,const modular &rhs){return modular(lhs)-=rhs;}
    friend modular operator*(const modular &lhs,const modular &rhs){return modular(lhs)*=rhs;}
    friend modular operator/(const modular &lhs,const modular &rhs){return modular(lhs)/=rhs;}
    friend istream &operator>>(istream &is,modular &o){long long x; is >> x; o=modular(x); return is;}
    friend ostream &operator<<(ostream &os,modular &o){return os << o.val;}
};
typedef modular mint;
//--------------------------------------------------------

mt19937_64 rng(time(0));

void runcase(){
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    vector<mint> dp(n),hsh(n),pw(n+1);
    vector<int> sz(n);
    for(int i=0;i<n;i++)hsh[i]=rng();
    pw[1]=1;
    for(int i=1;i<=n;i++)pw[i]=pw[i-1]*3;
    function<void(int,int)> dfs=[&](int u,int p){
        dp[u]=1;
        sz[u]=1;
        vector<pair<ll,int>> res;
        for(auto v:adj[u]){
            if(v==p)continue;
            dfs(v,u);
            sz[u]+=sz[v];
            res.emplace_back(dp[v],v);
        }
    };
    dfs(0,-1);
    bool ok=true;
    function<void(int,int)> dfs2=[&](int u,int p){
        deque<pair<ll,int>> res;
        for(auto v:adj[u]){
            if(v==p)continue;
            res.emplace_back(dp[v].val,v);
        }
        sort(res.begin(),res.end());
        while(res.size()>1&&res[0].first==res[1].first)res.pop_front(),res.pop_front();
        while(res.size()>1&&res.back().first==res[res.size()-2].first)res.pop_back(),res.pop_back();
        if(res.size()>1)return void(ok=false);
        if(res.size()==1)dfs2(res[0].second,u);
    };
    dfs2(0,-1);
    cout << (ok?"YES":"NO") << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}