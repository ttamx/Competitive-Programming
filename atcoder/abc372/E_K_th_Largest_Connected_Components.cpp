#include<bits/stdc++.h>
#include<bits/extc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()

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

void runcase(){
    int n,q;
    cin >> n >> q;
    vector<int> p(n);
    iota(p.begin(),p.end(),0);
    function<int(int)> fp=[&](int u){
        return p[u]=u==p[u]?u:fp(p[u]);
    };
    vector<ordered_set<int>> a(n);
    for(int i=0;i<n;i++){
        a[i].insert(i);
    }
    while(q--){
        int op;
        cin >> op;
        if(op==1){
            int u,v;
            cin >> u >> v;
            u--,v--;
            u=fp(u),v=fp(v);
            if(u==v)continue;
            if(a[u].size()<a[v].size()){
                swap(u,v);
            }
            for(auto x:a[v]){
                a[u].insert(x);
            }
            a[v].clear();
            p[v]=u;
        }else{
            int x,k;
            cin >> x >> k;
            x--;
            x=fp(x);
            int s=a[x].size();
            if(k<=s){
                cout << *a[x].find_by_order(s-k)+1 << "\n";
            }else{
                cout << -1 << "\n";
            }
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}