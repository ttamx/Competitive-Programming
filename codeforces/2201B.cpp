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
    int n,k;
    cin >> n >> k;
    if(n==k){
        cout << "YES\n";
        for(int i=1;i<=n;i++){
            cout << i << " " << i << " ";
        }
        cout << "\n";
        return;
    }
    if(k<n||n==1){
        cout << "NO\n";
        return;
    }
    k-=n+1;
    vector<int> cnt(n+1);
    vector<int> ans{1,2};
    cnt[1]=cnt[2]=1;
    for(int i=3;i<=n;i++){
        if(!k)break;
        k--;
        ans.emplace_back(i);
        ans.emplace_back(i-2);
        cnt[i-2]++;
        cnt[i]++;
    }
    if(k){
        cout << "NO\n";
        return;
    }
    for(int i=1;i<=n;i++){
        for(;cnt[i]<2;cnt[i]++){
            ans.emplace_back(i);
        }
    }
    cout << "YES\n";
    for(auto x:ans)cout << x << " ";
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}