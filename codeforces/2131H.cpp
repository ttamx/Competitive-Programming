#pragma GCC optimize("Ofast,unroll-loops")
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

const int N=1e6+5;

int mob[N];
vector<int> divisors[N];

int cnt[N];
bool vis[N];

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    for(int t=0;t<40;t++){
        vector<int> b,c;
        for(int i=0;i<n;i++){
            (rng()%2?b:c).emplace_back(i);
        }
        if(b.size()<2||c.size()<2)continue;
        vector<int> ans;
        for(int tt=0;tt<2;tt++){
            shuffle(b.begin(),b.end(),rng);
            bool ok=false;
            for(auto i:b){
                for(auto d:divisors[a[i]]){
                    cnt[d]++;
                }
            }
            for(auto i:b){
                if(vis[a[i]])continue;;
                vis[a[i]]=true;
                int cur=0;
                for(auto d:divisors[a[i]]){
                    cur+=mob[d]*cnt[d];
                }
                if(cur>0){
                    for(auto j:b){
                        if(j!=i&&gcd(a[i],a[j])==1){
                            ans.emplace_back(i);
                            ans.emplace_back(j);
                            ok=true;
                            break;
                        }
                    }
                    assert(ok);
                    if(ok)break;
                }
            }
            for(auto i:b){
                for(auto d:divisors[a[i]]){
                    cnt[d]=0;
                }
            }
            for(auto x:a){
                vis[x]=false;
            }
            if(!ok)break;
            swap(b,c);
        }
        if(ans.size()==4){
            for(auto x:ans){
                cout << x+1 << " ";
            }
            cout << "\n";
            return;
        }
    }
    cout << 0 << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    mob[1]=1;
    for(int i=1;i<N;i++){
        for(int j=i;j<N;j+=i){
            divisors[j].emplace_back(i);
        }
        for(int j=i*2;j<N;j+=i){
            mob[j]-=mob[i];
        }
    }
    int t(1);
    cin >> t;
    while(t--)runcase();
}