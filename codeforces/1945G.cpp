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
    int n,d;
    cin >> n >> d;
    vector<int> a(n),b(n);
    for(int i=0;i<n;i++){
        cin >> a[i] >> b[i];
    }
    map<int,deque<int>,greater<int>> mp;
    int mx=0;
    for(int i=n-1;i>=0;i--){
        if(a[i]<=mx){
            mp.begin()->second.emplace_front(i);
        }else{
            mx=a[i];
            mp.insert(mp.begin(),make_pair(mx,deque<int>{i}));
        }
    }
    using T = tuple<int,int,int>;
    priority_queue<T,vector<T>,greater<T>> pq;
    vector<bool> vis(n);
    int cnt=0;
    for(int t=1;t<=d;t++){
        int i=mp.begin()->second.front();
        mp.begin()->second.pop_front();
        if(mp.begin()->second.empty()){
            mp.erase(mp.begin());
        }
        if(!vis[i]){
            vis[i]=true;
            cnt++;
            if(cnt==n){
                cout << t << "\n";
                return;
            }
        }
        if(t+b[i]<=d){
            pq.emplace(t+b[i],b[i],i);
        }
        while(!pq.empty()&&get<0>(pq.top())<=t){
            int j=get<2>(pq.top());
            pq.pop();
            auto it=mp.lower_bound(a[j]);
            if(it!=mp.end()&&it->first==a[j]){
                it->second.emplace_back(j);
            }else{
                mp.insert(it,make_pair(a[j],deque<int>{j}));
            }
        }
    }
    cout << -1 << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}