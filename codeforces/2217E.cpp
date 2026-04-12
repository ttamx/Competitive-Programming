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
    vector<int> a(n),d(n);
    for(auto &x:a){
        cin >> x;
        x--;
    }
    for(auto &x:d){
        cin >> x;
    }
    vector<int> id(n,-1);
    for(int i=n-1;i>=0;i--){
        int p=-1;
        for(int j=n-1;j>=0;j--){
            if(d[i]==0){
                p=j;
                break;
            }
            if(id[j]!=-1&&a[id[j]]>a[i]){
                d[i]--;
            }
        }
        if(p==-1){
            cout << -1 << "\n";
            return;
        }
        for(int j=0;j<p;j++){
            id[j]=id[j+1];
        }
        id[p]=i;
    }
    vector<int> ans(n);
    for(int i=0;i<n;i++)ans[id[i]]=i;
    for(auto x:ans){
        cout << x+1 << " ";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}