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
        x--;
    }
    vector<int> pre(n),suf(n);
    {
        vector<int> s;
        for(int i=0;i<n;i++){
            while(!s.empty()&&a[s.back()]<a[i]){
                s.pop_back();
            }
            pre[i]=s.empty()?-1:s.back();
            s.emplace_back(i);
        }
    }
    {
        vector<int> s;
        for(int i=n-1;i>=0;i--){
            while(!s.empty()&&a[s.back()]>a[i]){
                s.pop_back();
            }
            suf[i]=s.empty()?n:s.back();
            s.emplace_back(i);
        }
    }
    vector<int> b(n,n-1);
    for(int i=0;i<n;i++){
        if(pre[i]!=-1){
            b[pre[i]]=min(b[pre[i]],suf[i]-1);
        }
    }
    for(int i=n-2;i>=0;i--){
        b[i]=min(b[i],b[i+1]);
    }
    while(q--){
        int l,r;
        cin >> l >> r;
        l--,r--;
        cout << (r<=b[l]?"YES":"NO") << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}