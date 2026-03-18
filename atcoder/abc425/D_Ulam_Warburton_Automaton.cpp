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
    int n,m;
    cin >> n >> m;
    vector<string> a(n);
    for(auto &x:a){
        cin >> x;
    }
    set<pair<int,int>> s;
    auto val=[&](int i,int j){
        if(i<0||i>=n||j<0||j>=m||a[i][j]=='.')return 0;
        return 1;
    };
    auto check=[&](int i,int j){
        if(i<0||i>=n||j<0||j>=m||a[i][j]=='#')return;
        int c=val(i-1,j)+val(i,j-1)+val(i,j+1)+val(i+1,j);
        if(c==1){
            s.emplace(i,j);
        }
    };
    int ans=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(a[i][j]=='#'){
                ans++;
            }else{
                check(i,j);
            }
        }
    }
    while(!s.empty()){
        set<pair<int,int>> t;
        swap(s,t);
        for(auto [i,j]:t){
            a[i][j]='#';
            ans++;
        }
        for(auto [i,j]:t){
            check(i-1,j);
            check(i,j-1);
            check(i,j+1);
            check(i+1,j);
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}