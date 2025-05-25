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
    int n,m,k;
    cin >> n >> m >> k;
    vector<int> a(n),b(m);
    ll ans=0;
    for(auto &x:a){
        cin >> x;
        ans+=x;
    }
    for(auto &x:b){
        cin >> x;
    }
    int mm=1<<m;
    vector<int> mask(mm),cnt(mm);
    for(int i=0;i<mm;i++){
        mask[i]=(1<<30)-1;
        for(int j=0;j<m;j++){
            if(i>>j&1){
                mask[i]&=b[j];
                cnt[i]++;
            }
        }
    }
    vector<int> c;
    for(auto x:a){
        vector<int> d(m,INF);
        for(int i=1;i<mm;i++){
            d[cnt[i]-1]=min(d[cnt[i]-1],(x&mask[i]));
        }
        for(int i=0;i<m;i++){
            d[i]=x-d[i];
        }
        for(int i=m-1;i>0;i--){
            d[i]-=d[i-1];
        }
        for(int i=0;i<m;i++){
            c.emplace_back(d[i]);
        }
    }
    sort(c.rbegin(),c.rend());
    for(int i=0;i<k;i++){
        ans-=c[i];
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}