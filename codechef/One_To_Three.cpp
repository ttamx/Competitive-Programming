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
        x--;
    }
    int ans=0;
    vector<vector<int>> b;
    vector<int> cur;
    for(int i=0;i<n;i++){
        if(a[i]==1){
            ans++;
            if(cur.size()==1&&i>1){
                ans+=min(cur[0],2-cur[0]);
            }else if(!cur.empty()){
                b.emplace_back(cur);
            }
            cur.clear();
        }else{
            cur.emplace_back(a[i]);
        }
    }
    if(!cur.empty()){
        b.emplace_back(cur);
    }
    for(auto v:b){
        int m=v.size();
        int c0=0,c1=0;
        for(int i=1;i<v.size();i++){
            (v[i]==v[i-1]?c0:c1)++;
        }
        if(c1==0){
            for(auto x:v){
                ans+=x;
            }
            continue;
        }
        if(v[0]==0){
            ans+=(c1+1)/2*2;
        }else{
            ans+=(c1+2)/2*2;
        }
    }
    cout << ans+n << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}