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

const int K=650;
const int N=4e5+5;

int lp[N];
vector<int> adj[N];
bitset<N> vis[K];

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
        if(x%2==1&&x!=lp[x]){
            x-=lp[x];
        }
    }
    int pr=-1;
    for(auto x:a){
        if(lp[x]==x){
            if(pr==-1){
                pr=x;
            }else if(pr!=x){
                cout << -1 << "\n";
                return;
            }
        }
    }
    if(pr==-1){
        pr=2;
    }
    for(auto x:a){
        if(x!=pr&&x<pr*2){
            cout << -1 << "\n";
            return;
        }
    }
    cout << pr << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=2;i<N;i++){
        if(lp[i])continue;
        for(int j=i;j<N;j+=i){
            if(!lp[j]){
                lp[j]=i;
            }
        }
    }
    int t(1);
    cin >> t;
    while(t--)runcase();
}