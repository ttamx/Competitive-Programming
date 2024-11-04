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
    vector<string> a(n);
    for(auto &x:a){
        cin >> x;
    }
    int len=2*(n+m-2);
    int ans=0;
    for(int i=0;i*2<min(n,m)&&len>=4;i++){
        int x=i,y=i;
        deque<char> s{a[x][y]};
        int d=0;
        auto walk=[&]{
            if(d==0){
                if(y+1<m-i){
                    y++;
                }else{
                    d++;
                    x++;
                }
            }else if(d==1){
                if(x+1<n-i){
                    x++;
                }else{
                    d++;
                    y--;
                }
            }else if(d==2){
                if(y-1>=i){
                    y--;
                }else{
                    d++;
                    x--;
                }
            }else if(d==3){
                if(x-1>=i){
                    x--;
                }else{
                    d++;
                    y++;
                }
            }
            d%=4;
            return a[x][y];
        };
        for(int i=0;i<2;i++){
            s.emplace_back(walk());
        }
        for(int i=0;i<len;i++){
            s.emplace_back(walk());
            if(s==deque<char>{'1','5','4','3'}){
                ans++;
            }
            s.pop_front();
        }
        len-=8;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}