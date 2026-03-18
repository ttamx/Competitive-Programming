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
    }
    string s;
    cin >> s;
    int l=-1,r=-1;
    for(int i=0;i<n;i++){
        if(a[i]==1)l=i;
        if(a[i]==n)r=i;
    }
    if(l>r)swap(l,r);
    if(s[0]=='1'||s[n-1]=='1'||s[l]=='1'||s[r]=='1'){
        cout << -1 << "\n";
        return;
    }
    l++,r++;
    cout << 5 << "\n";
    cout << 1 << " " << l << "\n";
    cout << 1 << " " << r << "\n";
    cout << l << " " << r << "\n";
    cout << l << " " << n << "\n";
    cout << r << " " << n << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}