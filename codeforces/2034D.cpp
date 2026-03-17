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
    auto b=a;
    sort(b.begin(),b.end());
    set<int> s[3];
    for(int i=0;i<n;i++){
        if(a[i]!=b[i]){
            s[a[i]].insert(i);
        }
    }
    vector<pair<int,int>> ans;
    auto work=[&](int i,int j){
        ans.emplace_back(i,j);
        if(a[i]!=b[i])s[a[i]].erase(i);
        if(a[j]!=b[j])s[a[j]].erase(j);
        swap(a[i],a[j]);
        if(a[i]!=b[i])s[a[i]].emplace(i);
        if(a[j]!=b[j])s[a[j]].emplace(j);
    };
    function<void(int)> upd=[&](int i){
        if(a[i]!=1)return;
        if(b[i]==1)return;
        if(b[i]==0){
            int j=*s[0].begin();
            work(i,j);
            upd(j);
        }else{
            int j=*s[2].begin();
            work(i,j);
            upd(j);
        }
    };
    for(int i=0;i<n;i++){
        upd(i);
    }
    int l=0,r=n-1;
    while(l<n&&a[l]==b[l])l++;
    while(r>=0&&a[r]==b[r])r--;
    int pos=0;
    while(a[pos]!=1){
        pos++;
    }
    if(l<r){
        work(l,pos);
        upd(l);
    }
    assert(a==b);
    cout << ans.size() << "\n";
    for(auto [i,j]:ans){
        cout << i+1 << " " << j+1 << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}