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
    int x,n,m;
    cin >> x >> n >> m;
    int mx=x,mn=x;
    {
        int cn=n,cm=m;
        while(mn>0&&(cn>0||cm>0)){
            if((mn&1)&&cn){
                cn--;
                mn/=2;
            }else if(cm){
                cm--;
                mn=(mn+1)/2;
            }else{
                assert(cn>0);
                cn--;
                mn/=2;
            }
        }
    }
    {
        int cn=n,cm=m;
        while(mx>0&&(cn>0||cm>0)){
            if((mx&1)&&cm){
                cm--;
                mx=(mx+1)/2;
            }else if(cn){
                cn--;
                mx/=2;
            }else{
                assert(cm>0);
                cm--;
                mx/=2;
            }
        }
    }
    cout << mn << " " << mx << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}