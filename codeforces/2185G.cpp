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
    int nn=0;
    for(auto &v:a){
        int k;
        cin >> k;
        nn+=k;
        v.resize(k);
        for(auto &x:v)cin >> x;
        sort(v.begin(),v.end());
    }
    ll ans=0,tot=0;
    for(auto &v:a){
        int k=v.size();
        vector<int> cnt(k+1);
        for(auto &x:v){
            if(x<=k){
                cnt[x]++;
            }
        }
        int mex=0;
        while(cnt[mex])mex++;
        tot+=mex;
        for(int i=0;i<mex;i++){
            if(cnt[i]==1){
                ans+=i-mex;
            }
        }
    }
    ans*=n-1;
    vector<int> cnt(nn+1);
    for(auto &v:a){
        for(auto &x:v){
            if(x<=nn)cnt[x]++;
        }
    }
    for(auto &v:a){
        int k=v.size();
        vector<int> cur(k+2);
        for(auto &x:v){
            if(x<=k+1)cur[x]++;
            if(x<=nn)cnt[x]--;
        }
        int mex=0;
        while(cur[mex])mex++;
        int mex2=mex+1;
        while(cur[mex2])mex2++;
        ans+=1LL*cnt[mex]*(mex2-mex);
        for(auto &x:v){
            if(x<=nn)cnt[x]++;
        }
    }
    ans+=tot*(n-1)*nn;
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}