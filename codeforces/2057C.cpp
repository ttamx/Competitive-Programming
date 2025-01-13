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
    int l,r;
    cin >> l >> r;
    for(int t=0;t<2;t++){
        int cur=0;
        int a=0,b=0,c=0;
        for(int i=29;i>=0;i--){
            int bl=(l>>i&1);
            int br=(r>>i&1);
            if(cur==0){
                if(bl!=br){
                    cur=1;
                    a|=1<<i;
                    if(t==0){
                        b|=1<<i;
                    }
                }else if(bl){
                    a|=1<<i;
                    b|=1<<i;
                    c|=1<<i;
                }
            }else{
                if(t==0){
                    if(cur==1&&a+(1<<i)<=r){
                        a|=1<<i;
                        c|=1<<i;
                        cur=2;
                    }else{
                        c|=1<<i;
                    }
                }else{
                    if(cur==1&&c>=l){
                        b|=1<<i;
                        cur=2;
                    }else{
                        b|=1<<i;
                        c|=1<<i;
                    }
                }
            }
        }
        if(cur==2){
            cout << a << " " << b << " " << c << "\n";
            return;
        }
    }
    assert(false);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}