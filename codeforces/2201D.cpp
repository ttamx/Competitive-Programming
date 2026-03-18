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

struct DS{
    ll val;
    map<int,int> dat;
    DS():val(0LL),dat(){}
    ll calc(pair<int,int> e){
        ll n=e.first-e.second+1;
        return n*(n+1)/2;
    }
    auto insert(int x){
        auto it=dat.lower_bound(x);
        if(it==dat.end()||it->second>x+1){
            it=dat.insert(it,{x,x});
        }else{
            assert(it->second==x+1);
            val-=calc(*it);
        }
        it->second=x;
        assert(it->second==x);
        if(it!=dat.begin()&&prev(it)->first==x-1){
            val-=calc(*prev(it));
            it->second=prev(it)->second;
            dat.erase(prev(it));
        }
        val+=calc(*it);
    }
    auto erase(int x){
        auto it=dat.lower_bound(x);
        assert(it!=dat.end());
        assert(it->second<=x);
        val-=calc(*it);
        if(it->second<x){
            dat[x-1]=it->second;
            val+=calc({x-1,it->second});
        }
        if(it->first>x){
            it->second=x+1;
            val+=calc(*it);
        }else{
            dat.erase(it);
        }
    }
};

void runcase(){
    int n,q;
    cin >> n >> q;
    vector<int> a(n);
    for(auto &x:a)cin >> x,x--;
    vector<set<int>> pos(n);
    for(int i=0;i<n;i++){
        pos[a[i]].emplace(i);
    }
    vector<DS> ds(n);
    multiset<int> dif;
    dif.emplace(0);
    auto insert=[&](int i){
        if(pos[i].size()<2)return;
        int l=*pos[i].begin();
        int r=*pos[i].rbegin();
        int d=r-l;
        ds[d].insert(l);
        dif.emplace(d);
    };
    auto erase=[&](int i){
        if(pos[i].size()<2)return;
        int l=*pos[i].begin();
        int r=*pos[i].rbegin();
        int d=r-l;
        ds[d].erase(l);
        dif.erase(dif.find(d));
    };
    for(int i=0;i<n;i++){
        insert(i);
    }
    while(q--){
        int i,x;
        cin >> i >> x;
        i--,x--;
        erase(a[i]);
        pos[a[i]].erase(i);
        insert(a[i]);
        a[i]=x;
        erase(a[i]);
        pos[a[i]].emplace(i);
        insert(a[i]);
        int d=*dif.rbegin();
        if(!d){
            cout << "0 0\n";
        }else{
            cout << d << " " << ds[d].val << "\n";
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}