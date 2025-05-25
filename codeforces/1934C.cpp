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
    auto answer=[&](int x,int y){
        cout << "! " << x << " " << y << endl;
    };
    auto ask=[&](int x,int y){
        cout << "? " << x << " " << y << endl;
        int res;
        cin >> res;
        return res;
    };
    int d1=ask(1,1);
    if(d1==0)return answer(1,1);
    int d2=ask(n,1);
    if(d2==0)return answer(n,1);
    int d3=ask(1,m);
    if(d3==0)return answer(1,m);
    if((d1+d2-n+1)%2==0){
        int dy=(d1+d2-n+1)/2;
        int dx=d1-dy;
        int x=dx+1,y=dy+1;
        if(1<=x&&x<=n&&1<=y&&y<=m&&ask(x,y)==0){
            return answer(x,y);
        }
    }
    int dx=(d1+d3-m+1)/2;
    int dy=d1-dx;
    int x=dx+1,y=dy+1;
    answer(x,y);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}