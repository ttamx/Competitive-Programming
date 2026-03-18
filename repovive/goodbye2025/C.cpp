#include<bits/stdc++.h>

using namespace std;

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

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n),b(n);
    for(int i=0;i<n;i++){
        cin >> a[i] >> b[i];
    }
    vector<bool> vis(n);
    priority_queue<pair<int,int>> pq;
    for(int i=0;i<n;i++){
        pq.emplace(a[i],i);
    }
    ll ans=0;
    while(!pq.empty()){
        auto [v,i]=pq.top();
        pq.pop();
        if(vis[i])continue;
        vis[i]=true;
        ans+=v;
        if(i>0){
            pq.emplace(v-b[i-1],i-1);
        }
        if(i+1<n){
            pq.emplace(v-b[i+1],i+1);
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