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
    vector<int> l(n),r(n);
    map<pair<int,int>,int> cnt;
    for(int i=0;i<n;i++){
        cin >> l[i] >> r[i];
        cnt[{l[i],r[i]}]++;
    }
    vector<int> ans(n);
    for(int t=0;t<2;t++){
        vector<int> ord(n);
        iota(ord.begin(),ord.end(),0);
        sort(ord.begin(),ord.end(),[&](int i,int j){
            return l[i]<l[j]||(l[i]==l[j]&&r[i]>r[j]);
        });
        multiset<int> ms;
        for(auto i:ord){
            auto it=ms.lower_bound(r[i]);
            if(it!=ms.end()){
                ans[i]+=*it-r[i];
            }
            ms.emplace(r[i]);
        }
        for(int i=0;i<n;i++){
            tie(l[i],r[i])=make_pair(-r[i],-l[i]);
        }
    }
    for(int i=0;i<n;i++){
        if(cnt[{l[i],r[i]}]>1){
            ans[i]=0;
        }
    }
    for(auto x:ans){
        cout << x << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}