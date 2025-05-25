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
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
        x--;
    }
    vector<int> l(n),r(n);
    {
        deque<int> lo,hi;
        l[0]=0;
        int last=0;
        for(int i=1;i<n;i++){
            if(a[i]>a[i-1]){
                lo.emplace_back(i-1);
                if(!hi.empty()&&a[i]>a[hi.back()]){
                    int cut=hi.back();
                    hi.clear();
                    while(!lo.empty()&&lo.front()<cut)lo.pop_front();
                    last=lo.front();
                }
            }else{
                hi.emplace_back(i-1);
                if(!lo.empty()&&a[i]<a[lo.back()]){
                    int cut=lo.back();
                    lo.clear();
                    while(!hi.empty()&&hi.front()<cut)hi.pop_front();
                    last=hi.front();
                }
            }
            l[i]=last;
        }
    }
    {
        deque<int> lo,hi;
        r[n-1]=n-1;
        int last=n-1;
        for(int i=n-2;i>=0;i--){
            if(a[i]>a[i+1]){
                lo.emplace_back(i+1);
                if(!hi.empty()&&a[i]>a[hi.back()]){
                    int cut=hi.back();
                    hi.clear();
                    while(!lo.empty()&&lo.front()>cut)lo.pop_front();
                    last=lo.front();
                }
            }else{
                hi.emplace_back(i+1);
                if(!lo.empty()&&a[i]<a[lo.back()]){
                    int cut=lo.back();
                    lo.clear();
                    while(!hi.empty()&&hi.front()>cut)hi.pop_front();
                    last=hi.front();
                }
            }
            r[i]=last;
        }
    }
    ll ans=0;
    vector<vector<int>> cmn(n+1),cmx(n+1);
    auto chmin=[&](int l,int r,int v){
        cmn[l].emplace_back(v);
        cmn[r+1].emplace_back(~v);
    };
    for(int i=0;i<n;i++){
        chmin(i,r[i],l[i]);
    }
    multiset<int> ms;
    for(int i=0;i<n;i++){
        for(auto v:cmn[i]){
            if(v>=0){
                ms.emplace(v);
            }else{
                ms.erase(ms.find(~v));
            }
        }
        int pos=i;
        pos=min(pos,*ms.begin());
        ans+=i-pos+1;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}