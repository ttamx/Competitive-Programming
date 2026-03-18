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
    int n,k;
    cin >> n >> k;
    string s,t;
    cin >> s >> t;
    int p=n-1;
    for(int i=n-1;i>=0;i--){
        p=min(p,i);
        while(p>=0&&s[p]!=t[i])p--;
        if(p==-1||i-p>k){
            cout << -1 << "\n";
            return;
        }
    }
    vector<string> ans;
    int step=0;
    while(s!=t){
        step++;
        if(step>k){
            cout << -1 << "\n";
            return;
        }
        p=n-1;
        int last=n;
        for(int i=n-1;i>=0;i--){
            p=min(p,i);
            while(p>=0&&s[p]!=t[i])p--;
            if(p<i){
                s[p+1]=s[p];
            }
        }
        ans.emplace_back(s);
    }
    cout << ans.size() << "\n";
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