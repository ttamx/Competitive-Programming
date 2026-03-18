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
    int n,q;
    cin >> n >> q;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    auto b=a;
    sort(b.begin(),b.end());
    b.erase(unique(b.begin(),b.end()),b.end());
    for(auto &x:a){
        x=lower_bound(b.begin(),b.end(),x)-b.begin();
    }
    vector<vector<int>> pos(n);
    for(int i=0;i<n;i++){
        pos[a[i]].emplace_back(i);
    }
    while(q--){
        int l,r;
        cin >> l >> r;
        l--,r--;
        vector<int> cands;
        int req=(r-l+1)/3;
        for(int t=0;t<100;t++){
            cands.emplace_back(a[uniform_int_distribution<int>(l,r)(rng)]);
        }
        sort(cands.begin(),cands.end());
        cands.erase(unique(cands.begin(),cands.end()),cands.end());
        vector<int> ans;
        for(auto x:cands){
            if(upper_bound(pos[x].begin(),pos[x].end(),r)-lower_bound(pos[x].begin(),pos[x].end(),l)>req){
                ans.emplace_back(x);
            }
        }
        if(ans.empty()){
            cout << "-1\n";
        }else{
            for(auto x:ans){
                cout << b[x] << " ";
            }
            cout << "\n";
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}