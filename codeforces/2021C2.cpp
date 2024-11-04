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
    int n,m,q;
    cin >> n >> m >> q;
    vector<int> a(n),c(n);
    for(auto &x:a){
        cin >> x;
        x--;
    }
    for(int i=0;i<n;i++){
        c[a[i]]=i;
    }
    vector<multiset<int>> pos(n);
    vector<int> b(m);
    for(auto &x:b){
        cin >> x;
        x--;
    }
    for(int i=0;i<m;i++){
        pos[b[i]].emplace(i);
    }
    int cnt=0;
    auto calc=[&](int l,int r){
        if(pos[r].empty())return 0;
        if(pos[l].empty())return 1;
        if(*pos[l].begin()>*pos[r].begin())return 1;
        return 0;
    };
    for(int i=0;i+1<n;i++){
        cnt+=calc(a[i],a[i+1]);
    }
    cout << (cnt==0?"YA":"TIDAK") << "\n";
    while(q--){
        int s,t;
        cin >> s >> t;
        s--,t--;
        int p=c[b[s]];
        set<int> upd;
        if(p>0)upd.emplace(p-1);
        if(p+1<n)upd.emplace(p);
        p=c[t];
        if(p>0)upd.emplace(p-1);
        if(p+1<n)upd.emplace(p);
        for(auto i:upd)cnt-=calc(a[i],a[i+1]);
        pos[b[s]].erase(pos[b[s]].find(s));
        b[s]=t;
        pos[b[s]].emplace(s);
        for(auto i:upd)cnt+=calc(a[i],a[i+1]);
        cout << (cnt==0?"YA":"TIDAK") << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}