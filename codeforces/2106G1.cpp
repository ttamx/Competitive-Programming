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
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
    }
    auto ask=[&](vector<int> a){
        cout << "? 1 " << a.size();
        for(auto x:a)cout << " " << x+1;
        cout << endl;
        int res;
        cin >> res;
        return res;
    };
    auto toggle=[&](int x){
        cout << "? 2 " << x+1 << endl;
    };
    int t=ask({0});
    vector<int> ans(n);
    if((t&1)==0){
        int l=1,r=n-1;
        while(l<r){
            int m=(l+r)/2;
            vector<int> tmp;
            for(int i=l;i<=m;i++)tmp.emplace_back(i);
            int v1=ask(tmp);
            toggle(0);
            int v2=ask(tmp);
            int d=abs(v1-v2);
            if(d<2*(m-l+1))r=m;
            else l=m+1;
        }
        int root=l;
        ans[root]=ask({root});
        ans[0]=ask({0});
        for(int i=1;i<n;i++)if(i!=root)ans[i]=ask({i})-ans[0];
        ans[0]-=ans[root];
    }else{
        ans[0]=t;
        for(int i=1;i<n;i++)ans[i]=ask({i})-ans[0];
    }
    cout << "!";
    for(auto x:ans)cout << " " << x;
    cout << endl;

}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}