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
    vector<pair<int,int>> a(n);
    for(auto &[y,x]:a)cin >> x >> y;
    for(int i=0;i<=n;i++)a.emplace_back(i,0);
    sort(a.rbegin(),a.rend());
    priority_queue<int,vector<int>,greater<int>> pq;
    ll base=0,sum=0;
    int last=n;
    for(auto [y,x]:a){
        sum+=x;
        pq.emplace(x);
        while(pq.size()>y+1){
            sum-=pq.top();
            pq.pop();
        }
        base=max(base,sum);
    }
    while(!pq.empty())pq.pop();
    vector<ll> ans(n+1);
    sum=0;
    for(auto [y,x]:a){
        sum+=x;
        pq.emplace(x);
        while(pq.size()>y){
            sum-=pq.top();
            pq.pop();
        }
        ans[y]=max(ans[y],sum);
    }
    for(int i=1;i<=n;i++)ans[i]=max(ans[i],ans[i-1]);
    for(int i=0;i<m;i++){
        int x,y;
        cin >> x >> y;
        cout << max(base,ans[y]+x) << " \n"[i==m-1];
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}