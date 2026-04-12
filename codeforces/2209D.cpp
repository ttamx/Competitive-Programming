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
    int r,g,b;
    cin >> r >> g >> b;
    while(max({r,g,b})>(r+g+b+1)/2){
        if(r==max({r,g,b}))r--;
        else if(g==max({r,g,b}))g--;
        else b--;
    }
    int n=r+g+b;
    string ans(n,'x');
    vector<pair<int,char>> a;
    a.emplace_back(r,'R');
    a.emplace_back(g,'G');
    a.emplace_back(b,'B');
    sort(a.rbegin(),a.rend());
    if(max({r,g,b})<=n/2&&min({r,g,b})==1){
        ans.back()=a.back().second;
        a.pop_back();
        n--;
    }
    int i=1-n%2;
    for(auto [x,c]:a){
        while(x--){
            ans[i]=c;
            i+=2;
            if(i>=n)i=n%2;
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}