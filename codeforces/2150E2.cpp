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
    vector<int> p(2*n-1);
    iota(p.begin(),p.end(),1);
    shuffle(p.begin(),p.end(),rng);
    auto ask=[&](int l,int r,int x){
        cout << "? " << x << " " << r-l;
        for(int i=l;i<r;i++){
            cout << " " << p[i];
        }
        cout << endl;
        int res;
        cin >> res;
        return res;
    };
    int cnt=0;
    int lo=0,hi=2*n-1;
    int mid=(lo+hi)/2;
    vector<int> vl,vr;
    for(int i=1;i<=n;i++){
        if(!ask(lo,mid,i)){
            vr.emplace_back(i);
        }else if(!ask(mid,hi,i)){
            vl.emplace_back(i);
        }else{
            cnt++;
        }
    }
    vector<int> cands;
    if(vl.size()*2+cnt!=mid){
        cands=vl;
        hi=mid;
    }else{
        cands=vr;
        lo=mid;
    }
    for(auto x:cands){
        int l=lo,r=hi;
        while(r-l>1){
            int m=(l+r)/2;
            if(!ask(l,m,x)){
                l=m;
            }else if(!ask(m,r,x)){
                r=m;
            }else{
                break;
            }
        }
        if(r-l==1){
            cout << "! " << x << endl;
            return;
        }
    }
    assert(false);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}