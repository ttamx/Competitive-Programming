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
    int n,k;
    cin >> n >> k;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    sort(a.begin(),a.end());
    vector<pair<int,int>> b;
    for(auto x:a){
        if(!b.empty()&&x==b.back().second){
            b.back().first++;
        }else{
            b.emplace_back(1,x);
        }
    }
    map<int,int> mp;
    for(auto x:a){
        mp[x]++;
    }
    int need=0,sum=0,cnt=0,dup=0;
    for(int i=0;i<=n;i++){
        if(mp.count(i)){
            dup+=mp[i]-1;
        }else{
            need++;
        }
    }
    priority_queue<int> pq;
    int ans=n;
    for(int i=n;i>=0;i--){
        if(!mp.count(i)){
            need--;
        }
        while(!b.empty()&&b.back().second>i){
            int val=b.back().first;
            pq.emplace(val);
            sum+=val;
            dup+=val;
            b.pop_back();
            cnt++;
        }
        while(sum>k){
            sum-=pq.top();
            pq.pop();
        }
        if(min(k,dup)>=need){
            ans=min(ans,cnt-(int)pq.size());
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}