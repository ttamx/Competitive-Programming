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
    auto ask=[&](vector<int> a){
        cout << "? " << a.size();
        for(auto x:a){
            cout << " " << x+1;
        }
        cout << endl;
        int res;
        cin >> res;
        return res;
    };
    vector<int> pos,pos2;
    pos.emplace_back(0);
    vector<int> ans(2*n,-1);
    for(int i=1;i<2*n;i++){
        pos.emplace_back(i);
        int res=ask(pos);
        if(res!=0){
            pos.pop_back();
            pos2.emplace_back(i);
            ans[i]=res;
        }
    }
    for(int i=0;i<2*n;i++){
        if(ans[i]!=-1)continue;
        pos2.emplace_back(i);
        ans[i]=ask(pos2);
        pos2.pop_back();
    }
    cout << "!";
    for(auto x:ans){
        cout << " " << x;
    }
    cout << endl;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}