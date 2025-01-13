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
    int n,m,q;
    cin >> n >> m >> q;
    int l=m,r=m,pre=0,suf=n+1;
    for(int i=0;i<q;i++){
        int x;
        cin >> x;
        if(x<=pre){
            l--,suf--;
        }else if(x>=suf){
            r++,pre++;
        }else if(x<l){
            l--;
            if(pre>=1)pre++;
            if(suf<=n)suf--;
        }else if(x>r){
            r++;
            if(pre>=1)pre++;
            if(suf<=n)suf--;
        }else if(l==r){
            pre++;
            suf--;
            l=1,r=pre;
        }else{
            pre++;
            suf--;
        }
        if(pre>=l){
            l=1;
            r=max(pre,r);
            pre=0;
        }
        if(suf<=r){
            l=min(l,suf);
            r=n;
            suf=n+1;
        }
        cout << pre+r-l+1+n-suf+1 << " ";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}