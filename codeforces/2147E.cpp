#pragma GCC optimize("Ofast,unroll-loops")
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

using T = tuple<int,int,int>;

const int N=1e5+5;
const int B=31;

int a[N],ver[N];
int cnt[B];
priority_queue<T,vector<T>,greater<T>> pq[B];

inline void insert(int id){
    int x=a[id];
    for(int i=0;i<B;i++){
        if(x>>i&1){
            cnt[i]++;
        }
    }
    ver[id]++;
    for(int i=0;i<B;i++){
        pq[i].emplace((1<<i)-(x&((1<<i)-1)),id,ver[id]);
    }
}

inline void erase(int id){
    int x=a[id];
    for(int i=0;i<B;i++){
        if(x>>i&1){
            cnt[i]--;
        }
    }
}

void runcase(){
    int n,q;
    cin >> n >> q;
    for(int i=0;i<n;i++){
        ver[i]=0;
        cin >> a[i];
        insert(i);
    }
    int s=0;
    for(int i=0;i<B;i++)if(cnt[i]>0)s++;
    vector<int> ans(s+1,0);
    int cost=0;
    for(int i=0;i<B;i++){
        if(cnt[i])continue;
        for(int j=i;j>=0;j--){
            if(cnt[j])continue;
            while(true){
                auto [c,id,v]=pq[j].top();
                if(v==ver[id])break;
                pq[j].pop();
            }
            auto [c,id,_]=pq[j].top();
            erase(id);
            a[id]+=c;
            insert(id);
            cost+=c;
        }
        ans.emplace_back(cost);
    }
    while(q--){
        int x;
        cin >> x;
        cout << upper_bound(ans.begin(),ans.end(),x)-ans.begin()-1 << "\n";
    }
    for(int i=0;i<B;i++)cnt[i]=0;
    for(int i=0;i<B;i++){
        while(!pq[i].empty()){
            pq[i].pop();
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}