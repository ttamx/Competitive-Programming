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
    int n,m,a,b;
    cin >> n >> m >> a >> b;
    ll g,x,y,z;
    cin >> g >> x >> y >> z;
    auto get=[&](){
        ll gg=g;
        g=(g*x+y)%z;
        return gg;
    };
    vector<deque<pair<ll,int>>> dq(m);
    ll ans=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            ll v=get();
            if(!dq[j].empty()&&i-dq[j].front().second>=a){
                dq[j].pop_front();
            }
            while(!dq[j].empty()&&dq[j].back().first>=v){
                dq[j].pop_back();
            }
            dq[j].emplace_back(v,i);
        }
        if(i>=a-1){
            deque<pair<ll,int>> dq2;
            for(int j=0;j<m;j++){
                ll v=dq[j].front().first;
                if(!dq2.empty()&&j-dq2.front().second>=b){
                    dq2.pop_front();
                }
                while(!dq2.empty()&&dq2.back().first>=v){
                    dq2.pop_back();
                }
                dq2.emplace_back(v,j);
                if(j>=b-1){
                    ans+=dq2.front().first;
                }
            }
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}