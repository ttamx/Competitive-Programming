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
    set<int> s;
    int mn1=0,mx1=0;
    int l1=0,r1=0,cur1=0;
    for(int i=0;i<n;i++){
        if(abs(a[i])>1)break;
        cur1+=a[i];
        mn1=min(mn1,cur1);
        mx1=max(mx1,cur1);
        l1=min(l1,cur1-mx1);
        r1=max(r1,cur1-mn1);
    }
    for(int i=l1;i<=r1;i++){
        s.emplace(i);
    }
    int mn2=0,mx2=0;
    int l2=0,r2=0,cur2=0;
    for(int i=n-1;i>=0;i--){
        if(abs(a[i])>1)break;
        cur2+=a[i];
        mn2=min(mn2,cur2);
        mx2=max(mx2,cur2);
        l2=min(l2,cur2-mx2);
        r2=max(r2,cur2-mn2);
    }
    for(int i=l2;i<=r2;i++){
        s.emplace(i);
    }
    for(int i=0;i<n;i++){
        if(abs(a[i])>1){
            int l1=0,l2=0,r1=0,r2=0;
            int cur1=0,cur2=0;
            for(int j=i-1;j>=0;j--){
                cur1+=a[j];
                l1=min(l1,cur1);
                r1=max(r1,cur1);
            }
            for(int j=i+1;j<n;j++){
                cur2+=a[j];
                l2=min(l2,cur2);
                r2=max(r2,cur2);
            }
            for(int j=l1+l2;j<=r1+r2;j++){
                s.emplace(a[i]+j);
            }
            break;
        }
    }
    cout << s.size() << "\n";
    for(auto x:s){
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