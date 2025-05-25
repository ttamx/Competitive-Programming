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
    auto ask=[&](int i,int j){
        cout << "? " << i+1 << " " << j+1 << endl;
        int res;
        cin >> res;
        return res;
    };
    for(int i=0;i<n;i++){
        if(deg[i]==0){
            int j=(i+1)%n;
            int d=ask(i,j);
            cout << "! " << (d==0?'A':'B') << endl;
            return;
        }
    }
    int mn=min_element(a.begin(),a.end())-a.begin();
    int mx=max_element(a.begin(),a.end())-a.begin();
    if(ask(mn,mx)<n-1||ask(mx,mn)<n-1){
        cout << "! A" << endl;
    }else{
        cout << "! B" << endl;
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}