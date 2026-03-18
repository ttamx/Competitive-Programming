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
    vector<int> a(n),b(m),c(m);
    for(auto &x:a){
        cin >> x;
    }
    for(auto &x:b){
        cin >> x;
    }
    for(auto &x:c){
        cin >> x;
    }
    priority_queue<int> pq;
    priority_queue<int,vector<int>,greater<int>> sw;
    vector<pair<int,int>> d;
    for(int i=0;i<m;i++){
        d.emplace_back(b[i],c[i]);
    }
    sort(d.begin(),d.end());
    int p=0;
    for(auto x:a){
        sw.emplace(x);
    }
    int ans=0,bad=0;
    while(!sw.empty()){
        int dm=sw.top();
        sw.pop();
        while(p<m&&d[p].first<=dm){
            if(d[p].second){
                pq.emplace(d[p].second);
            }else{
                bad++;
            }
            p++;
        }
        if(pq.empty()){
            if(bad>0){
                bad--;
                ans++;
            }
            continue;
        }
        ans++;
        dm=max(dm,pq.top());
        pq.pop();
        sw.emplace(dm);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}