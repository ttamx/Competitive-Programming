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
    vector<bool> used(n+1);
    vector<int> ans;
    auto work=[&](int x){
        ans.emplace_back(x);
        ans.emplace_back(x-1);
        ans.emplace_back(3);
        ans.emplace_back(1);
    };
    if(n%2==1){
        work(n);
        cout << n << "\n";
    }else if(n>6){
        ans.emplace_back(n);
        int m=n;
        while(m!=(m&-m)){
            m--;
        }
        m--;
        work(m);
        cout << (n|m) << "\n";
    }else{
        ans={3,5,6,4,2,1};
        cout << 7 << "\n";
    }
    for(auto x:ans){
        used[x]=true;
    }
    for(int i=1;i<=n;i++){
        if(!used[i]){
            ans.emplace_back(i);
        }
    }
    reverse(ans.begin(),ans.end());
    for(auto x:ans){
        cout << x << " ";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}