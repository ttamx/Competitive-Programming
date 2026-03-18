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

const int N=1e7+5;

vector<int> prime;
int lp[N];


void runcase(){
    int n,m;
    cin >> n >> m;
    if(lp[n]==n){
        cout << 0 << "\n";
        return;
    }
    int k=n;
    while(lp[k]!=k)k--;
    ll ans=0;
    set<int> cands;
    auto calc=[&](int x,int d){
        int res=0;
        while(x>0){
            x/=d;
            res+=x;
        }
        return res;
    };
    for(int v=n-1;v>=k;v--){
        int x=v+1;
        while(x>1){
            int p=lp[x];
            cands.emplace(p);
            x/=p;
        }
        int res=INF;
        for(auto x:cands){
            int a=calc(v,x),b=calc(n,x);
            ll ex=x;
            for(int c=1;ex<=m;c++,ex*=x){
                if(a/c!=b/c){
                    res=min(res,a/c);
                }
            }
        }
        ans+=res;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=2;i<N;i++){
        if(lp[i]==0){
            lp[i]=i;
            prime.emplace_back(i);
        }
        for(int j=0;i*prime[j]<N;j++){
            lp[i*prime[j]]=prime[j];
            if(prime[j]==lp[i]){
                break;
            }
        }
    }
    int t(1);
    cin >> t;
    while(t--)runcase();
}