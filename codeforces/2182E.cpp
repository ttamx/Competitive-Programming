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
    ll k;
    cin >> n >> m >> k;
    vector<tuple<int,int,int>> event;
    for(int i=0;i<m;i++){
        int x;
        cin >> x;
        event.emplace_back(x,1,0);
    }
    for(int i=0;i<n;i++){
        int x,y,z;
        cin >> x >> y >> z;
        event.emplace_back(x,0,z-y);
        k-=y;
    }
    int ans=0;
    priority_queue<int> pq;
    sort(event.begin(),event.end());
    for(auto [x,t,v]:event){
        if(!t){
            pq.emplace(v);
        }else{
            if(!pq.empty()){
                pq.pop();
                ans++;
            }
        }
    }
    vector<int> a;
    while(!pq.empty()){
        a.emplace_back(pq.top());
        pq.pop();
    }
    reverse(a.begin(),a.end());
    for(auto x:a){
        if(x>k)break;
        k-=x;
        ans++;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}