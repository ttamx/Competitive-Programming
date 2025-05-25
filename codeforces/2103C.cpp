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
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
        x=x<=k?1:-1;
    }
    int l=1,r=n-2;
    {
        int cur=a[0];
        while(l<n&&cur<0)cur+=a[l++];
    }
    {
        int cur=a[n-1];
        while(r>=0&&cur<0)cur+=a[r--];
    }
    if(l<=r){
        cout << "YES\n";
        return;
    }
    for(int t=0;t<2;t++){
        int cur=0;
        vector<int> lis{0};
        for(int i=0;i<n-1;i++){
            cur+=a[i];
            if(cur>=0){
                int idx=upper_bound(lis.begin(),lis.end(),cur)-lis.begin();
                if(idx>=2){
                    cout << "YES\n";
                    return;
                }
                if(idx==lis.size())lis.emplace_back(cur);
                else lis[idx]=cur;
            }
        }
        reverse(a.begin(),a.end());
    }
    cout << "NO\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}