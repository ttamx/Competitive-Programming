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
    for(auto &x:a)cin >> x;
    for(auto &x:b)cin >> x;
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    using P = pair<int,int>;
    priority_queue<P,vector<P>,greater<P>> pql,pqr;
    for(int i=0;i<n;i++){
        auto it=lower_bound(b.begin(),b.end(),a[i]);
        if(it!=b.end())pqr.emplace(*it-a[i],i);
        if(it!=b.begin())pql.emplace(a[i]-*prev(it),i);
    }
    vector<bool> mark(n);
    string s;
    cin >> s;
    int p=0,l=0,r=0,ans=n;
    for(auto x:s){
        if(x=='L')p--;
        else p++;
        l=min(l,p);
        r=max(r,p);
        while(!pql.empty()&&pql.top().first<=-l){
            int i=pql.top().second;
            pql.pop();
            if(!mark[i]){
                mark[i]=true;
                ans--;
            }
        }
        while(!pqr.empty()&&pqr.top().first<=r){
            int i=pqr.top().second;
            pqr.pop();
            if(!mark[i]){
                mark[i]=true;
                ans--;
            }
        }
        cout << ans << " ";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}