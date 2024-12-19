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
    int n,m;
    cin >> n >> m;
    vector<int> a(1),b;
    cin >> a[0];
    for(int i=0;i<n-1;i++){
        int x;
        cin >> x;
        if(x>a[0]){
            a.emplace_back(x);
        }
    }
    for(int i=0;i<m;i++){
        int x;
        cin >> x;
        if(x>a[0]){
            b.emplace_back(x);
        }
    }
    sort(a.rbegin(),a.rend());
    sort(b.rbegin(),b.rend());
    n=a.size();
    int k=b.size();
    int f=m-k;
    vector<int> cnt(m);
    for(int i=0,p=0;i<k;i++){
        while(a[p]>=b[i]){
            p++;
        }
        cnt[i]=p;
    }
    for(int i=1;i<=m;i++){
        ll ans=m/i;
        for(int j=i-1-(f%i);j<k;j+=i){
            ans+=cnt[j];
        }
        cout << ans << " \n"[i==m];
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}