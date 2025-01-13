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
    int n,m,d;
    cin >> n >> m >> d;
    vector<string> a(n);
    for(auto &x:a){
        cin >> x;
    }
    int ans=0;
    for(int x1=0;x1<n;x1++){
        for(int y1=0;y1<m;y1++){
            if(a[x1][y1]!='.')continue;
            for(int x2=0;x2<n;x2++){
                for(int y2=0;y2<m;y2++){
                    if(a[x2][y2]!='.')continue;
                    int res=0;
                    for(int i=0;i<n;i++){
                        for(int j=0;j<m;j++){
                            if(a[i][j]=='.'){
                                int d1=abs(i-x1)+abs(j-y1);
                                int d2=abs(i-x2)+abs(j-y2);
                                if(min(d1,d2)<=d){
                                    res++;
                                }
                            }
                        }
                    }
                    ans=max(ans,res);
                }
            }
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}