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
    int n,k;
    cin >> n >> k;
    vector<int> a(n+1);
    for(int i=1;i<=n;i++){
        cin >> a[i];
        a[i]--;
    }
    vector<int> dp(n+1);
    vector<int> cnt(n);
    int st=0,ed=-1,uniq=0;
    auto update=[&](int i,int v){
        if(cnt[a[i]])uniq--;
        cnt[a[i]]+=v;
        if(cnt[a[i]])uniq++;
    };
    auto query=[&](int l,int r){
        while(ed<r)update(++ed,+1);
        while(st>l)update(--st,+1);
        while(ed>r)update(ed--,-1);
        while(st<l)update(st++,-1);
        return uniq;
    };
    for(int i=1;i<=n;i++){
        dp[i]=query(1,i);
    }
    for(int t=2;t<=k;t++){
        vector<int> ndp(n+1);
        queue<tuple<int,int,int,int>> q;
        q.emplace(t,n,t,n);
        while(!q.empty()){
            auto [l,r,optl,optr]=q.front();
            q.pop();
            if(l>r)continue;
            pair<int,int> best(-INF,-1);
            int m=(l+r)/2;
            for(int i=min(optr,m);i>=optl;i--){
                best=max(best,{dp[i-1]+query(i,m),i});
            }
            int opt;
            tie(ndp[m],opt)=best;
            q.emplace(l,m-1,optl,opt);
            q.emplace(m+1,r,opt,optr);
        }
        dp=move(ndp);
    }
    cout << dp[n] << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}