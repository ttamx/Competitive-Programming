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
    string s;
    cin >> s;
    ll ans=0;
    auto f=[&](ll x){
        return x*(x-1)/2;
    };
    for(int t=0;t<2;t++){
        vector<int> l(n),r(n);
        int p=-1;
        for(int i=0;i<n;i++){
            l[i]=p;
            if(s[i]=='1')p=i;
        }
        p=n;
        for(int i=n-1;i>=0;i--){
            r[i]=p;
            if(s[i]=='1')p=i;
        }
        for(int i=0;i<n;i++){
            if(s[i]=='1'){
                ll res=1;
                res+=1LL*(i-l[i]-1)*(n-i);
                res+=1LL*(r[i]-i-1)*(i+1);
                res+=f(i-l[i]-1)+f(r[i]-i-1);
                ans=max(ans,res);
            }else{
                ll res=1LL*(l[i]+1)*(i-l[i]);
                res+=f(i-l[i]);
                ans=max(ans,res);
            }
        }
        reverse(s.begin(),s.end());
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}