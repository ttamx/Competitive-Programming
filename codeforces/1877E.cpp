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
    vector<int> a(n),deg(n);
    for(auto &x:a){
        cin >> x;
        x--;
        deg[x]++;
    }
    vector<int> q;
    vector<int> keep(n,1);
    vector<bool> vis(n);
    for(int i=0;i<n;i++){
        if(deg[i]==0){
            q.emplace_back(i);
        }
    }
    for(int i=0;i<q.size();i++){
        int u=q[i];
        int v=a[u];
        vis[u]=true;
        keep[v]&=!keep[u];
        if(--deg[v]==0){
            q.emplace_back(v);
        }
    }
    for(int i=0;i<n;i++){
        if(vis[i])continue;
        if(keep[i])continue;
        int pre=0;
        for(int u=i;!vis[u];u=a[u]){
            vis[u]=true;
            keep[u]&=!pre;
            pre=keep[u];
        }
    }
    for(int i=0;i<n;i++){
        if(vis[i])continue;
        int cnt=0;
        for(int u=i;!vis[u];u=a[u]){
            vis[u]=true;
            keep[u]=cnt&1;
            cnt++;
        }
        if(cnt%2==1){
            cout << -1 << "\n";
            return;
        }
    }
    vector<int> ans;
    for(int i=0;i<n;i++){
        if(keep[i]){
            ans.emplace_back(i);
        }
    }
    cout << ans.size() << "\n";
    for(auto x:ans){
        cout << a[x]+1 << " ";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}