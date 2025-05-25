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
    int n,m;
    cin >> n >> m;
    vector<vector<int>> a(n,vector<int>(m)),b(n,vector<int>(m));
    for(auto &v:a){
        for(auto &x:v){
            cin >> x;
            x--;
        }
    }
    for(auto &v:b){
        for(auto &x:v){
            cin >> x;
            x--;
        }
    }
    int curi=0,curj=0;
    auto next_pos=[&](){
        curj++;
        if(curj==m){
            curi++;
            curj=0;
        }
    };
    int match=0;
    for(int i=0;i<n;i++){
        int ans=n*m-match;
        for(int j=0;j<m;j++){
            while(curi<n&&b[curi][curj]!=a[i][j]){
                next_pos();
            }
            if(curi>=n){
                cout << n*m-match << "\n";
                return;
            }
            match++;
            next_pos();
            while(curi==i&&j+1<m){
                j++;
                if(a[i][j]!=b[curi][curj]){
                    cout << ans << "\n";
                    return;
                }
                match++;
                next_pos();
            }
        }
    }
    cout << n*m-match << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}