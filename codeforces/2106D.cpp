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
    vector<int> a(n),b(m);
    for(auto &x:a)cin >> x;
    for(auto &x:b)cin >> x;
    int cur=-1;
    vector<int> pre(m),suf(m);
    for(int i=0;i<m;i++){
        cur++;
        while(cur<n&&a[cur]<b[i])cur++;
        pre[i]=cur;
    }
    if(cur<n){
        cout << 0 << "\n";
        return;
    }
    if(m==1){
        cout << b[0] << "\n";
        return;
    }
    cur=n;
    for(int i=m-1;i>=0;i--){
        cur--;
        while(cur>=0&&a[cur]<b[i])cur--;
        suf[i]=cur;
    }
    int ans=INF;
    for(int i=0;i<m;i++){
        if(i==0){
            if(suf[i+1]>=0)ans=min(ans,b[i]);
        }else if(i==m-1){
            if(pre[i-1]<n)ans=min(ans,b[i]);
        }else if(pre[i-1]<suf[i+1]){
            ans=min(ans,b[i]);
        }
    }
    cout << (ans<INF?ans:-1) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}