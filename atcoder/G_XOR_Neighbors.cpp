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
    vector<ll> basis(n),val(n,-1);
    auto calc=[&](ll x){
        ll res=0;
        for(int i=0;i<n;i++){
            if(x>>i&1){
                if(!basis[i]){
                    return -1LL;
                }else{
                    x^=basis[i];
                    res^=val[i];
                }
            }
        }
        return res;
    };
    auto insert=[&](ll a,ll b){
        for(int i=0;i<n;i++){
            if(a>>i&1){
                if(!basis[i]){
                    basis[i]=a;
                    val[i]=b;
                    return true;
                }else{
                    a^=basis[i];
                    b^=val[i];
                }
            }
        }
        assert(b==0);
        return false;
    };
    vector<ll> ans(n);
    vector<ll> adj(n);
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u]|=1LL<<v;
        adj[v]|=1LL<<u;
    }
    for(int i=0;i<n;i++){
        insert(adj[i],0);
    }
    for(int i=0;i<n;i++){
        ans[i]=calc(1LL<<i);
        if(ans[i]==-1LL){
            ans[i]=1LL<<i;
            insert(1LL<<i,1LL<<i);
        }
        if(ans[i]==0LL){
            return void(cout << "No\n");
        }
    }
    cout << "Yes\n";
    for(auto &x:ans)cout << x << " ";
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}