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

using P = pair<ll,ll>;

ll cross(P a,P b){
    return a.first*b.second-a.second*b.first;
}

ll dot(P a,P b){
    return a.first*b.first+a.second*b.second;
}

bool same(P a,P b){
    return cross(a,b)==0&&dot(a,b)>0;
}

void runcase(){
    int n,q;
    cin >> n >> q;
    vector<P> a(n);
    for(auto &[x,y]:a)cin >> x >> y;
    vector<int> ord(n);
    iota(ord.begin(),ord.end(),0);
    sort(ord.begin(),ord.end(),[&](int i,int j){
        int u=a[i]>P(0,0),v=a[j]>P(0,0);
        if(u!=v)return u>v;
        return cross(a[i],a[j])<0;
    });
    vector<int> l(n),r(n);
    for(int i=0;i<n;i++){
        l[ord[i]]=r[ord[i]]=i;
    }
    for(int i=1;i<n;i++){
        if(same(a[ord[i]],a[ord[i-1]])){
            l[ord[i]]=l[ord[i-1]];
        }
    }
    for(int i=n-2;i>=0;i--){
        if(same(a[ord[i]],a[ord[i+1]])){
            r[ord[i]]=r[ord[i+1]];
        }
    }
    while(q--){
        int x,y;
        cin >> x >> y;
        x--,y--;
        x=l[x],y=r[y];
        if(x>y)y+=n;
        cout << y-x+1 << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}