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
    auto ask=[&](int l,int r,int x){
        cout << "? " << x << " " << r-l;
        for(int i=l;i<r;i++){
            cout << " " << i;
        }
        cout << endl;
        int res;
        cin >> res;
        return res;
    };
    function<void(int,int,vector<int>,vector<int>)> rec=[&](int l,int r,vector<int> a,vector<int> b){
        if((r-l-b.size())%2==0){
            return;
        }
        if(a.size()==1){
            cout << "! " << a[0] << endl;
            return;
        }
        assert(r-l>1);
        int m=(l+r)/2;
        vector<int> al,ar,bl,br;
        for(auto x:a){
            if(ask(l,m,x)){
                if(ask(m,r,x)){
                    bl.emplace_back(x);
                    br.emplace_back(x);
                }else{
                    al.emplace_back(x);
                }
            }else{
                ar.emplace_back(x);
            }
        }
        for(auto x:b){
            if(ask(l,m,x)){
                bl.emplace_back(x);
            }else{
                br.emplace_back(x);
            }
        }
        rec(l,m,al,bl);
        rec(m,r,ar,br);
    };
    vector<int> a(n);
    iota(a.begin(),a.end(),1);
    rec(1,2*n,a,{});
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}