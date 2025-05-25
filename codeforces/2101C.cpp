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
    vector<vector<int>> pos(n);
    for(int i=0;i<n;i++){
        cin >> a[i];
        a[i]--;
        pos[a[i]].emplace_back(i);
    }
    vector<ll> ans(n);
    for(int t=0;t<2;t++){
        priority_queue<int,vector<int>,greater<int>> pq;
        for(int i=0;i<n;i++){
            for(auto j:pos[i]){
                pq.emplace(t?-j:j);
            }
            while(pq.size()>i+1)pq.pop();
        }
        vector<ll> b;
        while(!pq.empty()){
            b.emplace_back(pq.top());
            pq.pop();
        }
        reverse(b.begin(),b.end());
        ll cur=0;
        for(int i=0;i<b.size();i++){
            cur+=b[i];
            ans[i]+=cur;
        }
    }
    cout << *max_element(ans.begin(),ans.end()) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}