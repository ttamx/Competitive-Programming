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

int binpow(int a,int b,int mod){
    if(b==0)return 1;
    ll res=binpow(a,b>>1,mod);
    res=res*res%mod;
    if(b&1)res=res*a%mod;
    return res;
}

void runcase(){
    int n,k;
    cin >> n >> k;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
        x--;
    }
    auto ans=a;
    vector<pair<int,int>> odd,even;
    vector<bool> vis(n);
    vector<vector<int>> group;
    for(int i=0;i<n;i++){
        if(vis[i])continue;
        int sz=0;
        vector<int> tmp;
        for(int u=i;!vis[u];u=a[u]){
            tmp.emplace_back(u);
            vis[u]=true;
            sz++;
        }
        int id=group.size();
        group.emplace_back(tmp);
        (sz%2==0?even:odd).emplace_back(sz,id);
    }
    int m=group.size();
    vector<int> fa(m);
    iota(fa.begin(),fa.end(),0);
    function<int(int)> fp=[&](int u){
        return fa[u]=(u==fa[u]?u:fp(fa[u]));
    };
    if(!even.empty()){
        sort(even.begin(),even.end());
        for(int t=0;t<k;t++){
            if(even.size()%2==1){
                cout << "NO\n";
                return;
            }
            vector<pair<int,int>> b;
            for(int i=0;i<even.size();i+=2){
                if(even[i].first!=even[i+1].first){
                    cout << "NO\n";
                    return;
                }
                fa[fp(even[i+1].second)]=fp(even[i].second);
                b.emplace_back(even[i]);
            }
            even=move(b);
        }
    }
    vector<int> val(m);
    sort(odd.begin(),odd.end());
    for(int t=0;t<k&&!odd.empty();t++){
        vector<pair<int,int>> b;
        int pre=-1,id=-1;
        for(auto [x,i]:odd){
            if(x==pre){
                fa[fp(i)]=fp(id);
                b.emplace_back(pre,id);
                pre=-1,id=-1;
            }else{
                if(pre!=-1){
                    val[fp(id)]=k-t;
                }
                pre=x;
                id=i;
            }
        }
        if(pre!=-1){
            val[fp(id)]=k-t;
        }
        odd=move(b);
    }
    vector<vector<int>> comp(m);
    for(int i=0;i<m;i++){
        comp[fp(i)].emplace_back(i);
    }
    for(int id=0;id<m;id++){
        auto &c=comp[id];
        if(c.empty()){
            continue;
        }
        int sz=group[c[0]].size();
        vector<int> p;
        int t=binpow(2%sz,val[id],sz)%sz;
        for(auto i:c){
            vector<int> b(group[i].size());
            int cur=0;
            for(int j=0;j<group[i].size();j++){
                b[cur]=group[i][j];
                cur=(cur+t)%sz;
            }
            group[i]=move(b);
        }
        for(int i=0;i<sz;i++){
            for(auto j:c){
                p.emplace_back(group[j][i]);
            }
        }
        for(int i=0;i<p.size();i++){
            ans[p[i]]=p[(i+1)%p.size()];
        }
    }
    cout << "YES\n";
    for(auto x:ans){
        cout << x+1 << " ";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}