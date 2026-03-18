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
    int n;
    cin >> n;
    vector<int> a(n),b(n);
    for(int i=0;i<n;i++){
        cin >> a[i] >> b[i];
    }
    vector<int> oa(n),ob(n);
    iota(oa.begin(),oa.end(),0);
    sort(oa.begin(),oa.end(),[&](int i,int j){return a[i]<a[j];});
    iota(ob.begin(),ob.end(),0);
    sort(ob.begin(),ob.end(),[&](int i,int j){return b[i]<b[j];});
    vector<int> t(n);
    for(int i=0;i<n/2;i++)t[oa[i]]|=1;
    for(int i=0;i<n/2;i++)t[ob[i]]|=2;
    vector<int> p[4];
    for(int i=0;i<n;i++)p[t[i]].emplace_back(i);
    assert(p[0].size()==p[3].size());
    assert(p[1].size()==p[2].size());
    for(int i=0;i<p[0].size();i++){
        cout << p[0][i]+1 << " " << p[3][i]+1 << "\n";
    }
    for(int i=0;i<p[1].size();i++){
        cout << p[1][i]+1 << " " << p[2][i]+1 << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}