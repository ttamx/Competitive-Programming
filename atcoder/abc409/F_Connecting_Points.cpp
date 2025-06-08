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
    int n,q;
    cin >> n >> q;
    int m=n+q;
    vector<int> bel(m);
    iota(bel.begin(),bel.end(),0);
    function<int(int)> fp=[&](int u){
        return bel[u]=u==bel[u]?u:fp(bel[u]);
    };
    vector<pair<int,int>> a;
    using T = tuple<int,int,int>;
    priority_queue<T,vector<T>,greater<T>> pq;
    auto ins=[&](){
        int x,y;
        cin >> x >> y;
        int j=a.size();
        for(int i=0;i<j;i++){
            pq.emplace(abs(x-a[i].first)+abs(y-a[i].second),i,j);
        }
        a.emplace_back(x,y);
    };
    for(int i=0;i<n;i++)ins();
    while(q--){
        int op;
        cin >> op;
        if(op==1){
            ins();
        }else if(op==2){
            int ans=-1;
            while(!pq.empty()){
                auto [d,u,v]=pq.top();
                if(ans!=-1&&d>ans)break;
                pq.pop();
                if(fp(u)==fp(v))continue;
                if(ans==-1)ans=d;
                bel[fp(u)]=v;
            }
            cout << ans << "\n";
        }else{
            int u,v;
            cin >> u >> v;
            u--,v--;
            cout << (fp(u)==fp(v)?"Yes":"No") << "\n";
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}