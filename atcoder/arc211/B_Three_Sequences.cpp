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
    vector<int> a(3);
    for(auto &x:a){
        cin >> x;
    }
    vector<pair<int,int>> b;
    for(int i=0;i<3;i++){
        b.emplace_back(a[i],i);
    }
    vector<vector<int>> ans(3);
    auto work=[&](int i,int x,int y,int z){
        while(x--)ans[i].emplace_back(0);
        while(y--)ans[i].emplace_back(1);
        while(z--)ans[i].emplace_back(0);
    };
    sort(b.begin(),b.end());
    if(b[0].first==b[1].first){
        work(0,b[0].first,0,0);
        work(1,b[0].first,0,0);
        work(2,b[2].first,0,0);
    }else{
        vector<int> ord(3);
        for(int i=0;i<3;i++){
            ord[b[i].second]=i;
        }
        vector<int> idx(4);
        idx[ord[0]|ord[1]]=0;
        idx[ord[0]|ord[2]]=1;
        idx[ord[1]|ord[2]]=2;
        work(idx[1],b[0].first,b[1].first,0);
        work(idx[2],b[2].first,0,0);
        work(idx[3],0,b[1].first,b[2].first);
    }
    for(auto v:ans){
        cout << v.size();
        for(auto x:v){
            cout << " " << x;
        }
        cout << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}