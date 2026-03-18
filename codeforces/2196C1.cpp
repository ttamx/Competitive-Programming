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
    auto ask=[&](int k){
        cout << "? " << k << endl;
        int s;
        cin >> s;
        vector<int> a(s);
        for(auto &x:a)cin >> x;
        return a;
    };
    int last=0;
    vector<pair<int,int>> ans;
    for(int i=1;i<=n;i++){
        int l=last+1,r=(1<<n);
        while(l<r){
            int mid=(l+r+1)/2;
            auto path=ask(mid);
            if(!path.empty()&&path[0]==i)l=mid;
            else r=mid-1;
        }
        int tmp=l;
        for(int cur=tmp;cur>last+1;){
            auto path=ask(cur);
            assert(path.size()>1&&path[0]==i);
            int j=path[1];
            ans.emplace_back(i,j);
            int l=last+1,r=cur-1;
            while(l<r){
                int mid=(l+r+1)/2;
                auto path=ask(mid);
                assert(path.size()>1&&path[0]==i);
                if(path.size()<2||path[1]<j)l=mid;
                else r=mid-1;
            }
            cur=l;
        }
        last=tmp;
    }
    cout << "! " << ans.size() << endl;
    for(auto [u,v]:ans)cout << u << " " << v << endl;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}