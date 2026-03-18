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
    ll m;
    cin >> n >> m;
    int L=1;
    vector<int> a(n),b(n);
    for(auto &x:a){
        cin >> x;
        L=lcm(L,x);
    }
    for(auto &x:b){
        cin >> x;
    }
    auto mul=[&](const vector<vector<ll>> &a,const vector<vector<ll>> &b){
        vector<vector<ll>> c(n,vector<ll>(n,LINF));
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                for(int k=0;k<n;k++){
                    c[i][j]=min(c[i][j],a[i][k]+b[k][j]);
                }
            }
        }
        return c;
    };
    vector<vector<vector<ll>>> pre;
    vector<vector<ll>> base(n,vector<ll>(n,LINF));
    for(int i=0;i<n;i++){
        base[i][i]=0;
    }
    for(int l=0;l<L;l++){
        vector<vector<ll>> cost1(n,vector<ll>(n,LINF));
        for(int i=0;i<n;i++){
            cost1[i][i]=0;
        }
        if(n>1){
            for(int i=0;i<n;i++){
                if(l%a[i]==b[i])continue;
                int j=(i+1)%n;
                cost1[i][j]=1;
            }
        }
        for(int x=0;x<n;x++){
            for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                    cost1[i][j]=min(cost1[i][j],cost1[i][x]+cost1[x][j]);
                }
            }
        }
        vector<vector<ll>> cost2(n,vector<ll>(n,LINF));
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if((l+1)%a[j]==b[j])continue;
                int k=(j+1)%n;
                cost2[i][k]=cost1[i][j]+1;
            }
        }
        base=mul(base,cost2);
        pre.emplace_back(base);
    }
    vector<vector<ll>> cur(n,vector<ll>(n,LINF));
    for(int i=0;i<n;i++){
        cur[i][i]=0;
    }
    ll t=m/L;
    while(t>0){
        if(t&1){
            cur=mul(cur,base);
        }
        base=mul(base,base);
        t>>=1;
    }
    m%=L;
    if(m>0){
        cur=mul(cur,pre[m-1]);
    }
    ll ans=LINF;
    for(int i=0;i<n;i++){
        ans=min(ans,cur[0][i]);
    }
    cout << (ans<LINF?ans:-1LL) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}