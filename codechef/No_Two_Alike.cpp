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
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
        x--;
    }
    vector<int> l(n,-1),r(n,-1);
    for(int i=0;i<n;i++){
        if(l[a[i]]==-1){
            l[a[i]]=i;
        }
        r[a[i]]=i;
    }
    vector<pair<int,int>> b;
    for(int i=0;i<n;i++){
        if(l[i]!=r[i]){
            b.emplace_back(l[i],r[i]);
        }
    }
    int ans=0;
    sort(b.begin(),b.end());
    for(int i=0;i<b.size();i++){
        int l=b[i].first;
        int r=b[i].second;
        while(i+1<b.size()&&b[i+1].first<=r){
            i++;
            r=max(r,b[i].second);
        }
        set<int> s;
        for(int j=l;j<=r;j++){
            s.emplace(a[j]);
        }
        ans+=s.size();
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}