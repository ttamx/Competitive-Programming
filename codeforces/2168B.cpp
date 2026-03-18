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

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    string phase;
    cin >> phase;
    if(phase[0]=='f'){
        int t;
        cin >> t;
        while(t--){
            int n;
            cin >> n;
            vector<int> pos(n);
            for(int i=0;i<n;i++){
                int x;
                cin >> x;
                pos[x-1]=i;
            }
            cout << (pos[0]<pos[n-1]) << "\n";
        }
    }else{
        auto ask=[&](int l,int r){
            cout << "? " << l << " " << r << endl;
            int res;
            cin >> res;
            return res;
        };
        int t;
        cin >> t;
        while(t--){
            int n,k;
            cin >> n >> k;
            int l=1,r=n;
            if(k){
                while(l<r){
                    int m=(l+r)/2;
                    if(ask(1,m)==n-1)r=m;
                    else l=m+1;
                }
            }else{
                while(l<r){
                    int m=(l+r+1)/2;
                    if(ask(m,n)==n-1)l=m;
                    else r=m-1;
                }
            }
            cout << "! " << l << endl;
        }
    }
}