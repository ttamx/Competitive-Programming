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
    vector<vector<int>> a(n);
    for(auto &v:a){
        int k;
        cin >> k;
        v.resize(k);
        for(auto &x:v)cin >> x;
    }
    vector<int> opt,rem(n);
    iota(rem.begin(),rem.end(),0);
    for(int pos=0;!opt.empty()||!rem.empty();pos++){
        if(opt.empty()){
            swap(opt,rem);
        }
        for(auto i:opt){
            if(a[i].size()==pos){
                opt.insert(opt.end(),rem.begin(),rem.end());
                rem.clear();
                break;
            }
        }
        int mn=INF;
        for(auto i:opt){
            if(pos<a[i].size()){
                mn=min(mn,a[i][pos]);
            }
        }
        if(mn==INF)break;
        vector<int> new_opt,new_rem;
        for(auto i:opt){
            if(pos<a[i].size()){
                if(a[i][pos]==mn){
                    new_opt.emplace_back(i);
                }else{
                    new_rem.emplace_back(i);
                }
            }
        }
        for(auto i:rem){
            if(pos<a[i].size()){
                new_rem.emplace_back(i);
            }
        }
        opt=move(new_opt);
        rem=move(new_rem);
        cout << mn << " ";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}