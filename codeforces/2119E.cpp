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

const int B=31;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n-1),b(n),c(n);
    for(auto &x:a)cin >> x;
    for(auto &x:b)cin >> x;
    for(int i=0;i<n-1;i++){
        c[i]|=a[i];
        c[i+1]|=a[i];
    }
    a.insert(a.begin(),0);
    vector<int> v{0};
    vector<ll> dp{0};
    for(int i=0;i<n;i++){
        int cur=b[i];
        int mask=0;
        vector<int> new_v;
        vector<ll> new_dp;
        if((cur&c[i])==c[i]){
            new_v.emplace_back(cur);
        }
        for(int j=0;j<B;j++){
            if(c[i]>>j&1){
                mask|=1<<j;
                if(!(cur>>j&1)){
                    cur=((cur>>j)<<j)|mask;
                }
                if((cur&c[i])==c[i]){
                    new_v.emplace_back(cur);
                }
            }else{
                int val=cur;
                if(!(val>>j&1)){
                    val=((val>>j)<<j)|mask|(1<<j);
                }
                if((val&c[i])==c[i]){
                    new_v.emplace_back(val);
                }
            }
        }
        sort(new_v.begin(),new_v.end());
        new_v.erase(unique(new_v.begin(),new_v.end()),new_v.end());
        new_dp.assign(new_v.size(),LINF);
        for(int x=0;x<v.size();x++){
            for(int y=0;y<new_v.size();y++){
                if((v[x]&new_v[y])!=a[i])continue;
                new_dp[y]=min(new_dp[y],dp[x]+new_v[y]-b[i]);
            }
        }
        v=move(new_v);
        dp=move(new_dp);
    }
    ll ans=*min_element(dp.begin(),dp.end());
    cout << (ans<LINF?ans:-1LL) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}