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
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    vector<int> st,lch(n,-1),rch(n,-1);
    int root=-1;
    for(int i=0;i<n;i++){
        while(!st.empty()&&a[st.back()]<a[i]){
            lch[i]=st.back();
            st.pop_back();
        }
        (st.empty()?root:rch[st.back()])=i;
        st.emplace_back(i);
    }
    function<ll(int)> dfs=[&](int u){
        ll res=0;
        if(lch[u]!=-1){
            res=max(res,dfs(lch[u])+abs(u-lch[u]));
        }
        if(rch[u]!=-1){
            res=max(res,dfs(rch[u])+abs(u-rch[u]));
        }
        return res;
    };
    cout << dfs(root) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}