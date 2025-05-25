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

const int S=2002000;

using BS = bitset<S>;

void runcase(){
    int s,k;
    cin >> s >> k;
    int d=-1;
    int lim=k*(k+1)/2;
    if(s>=lim){
        d=s-lim;
    }else{
        lim=s;
    }
    BS filter,cur;
    for(int i=0;i<=lim;i++)filter[i]=1;
    cur[0]=1;
    int dir=1;
    for(int i=k;i>=2;i--){
        if(dir)cur<<=i;
        else cur>>=i;
        for(int j=i;j<=lim;j<<=1){
            if(dir)cur|=cur<<j;
            else cur|=cur>>j;
        }
        cur&=filter;
        int p=s;
        if(d!=-1){
            p-=(d+i-1)/i*i;
        }
        if(cur[p]&&dir){
            cout << i << "\n";
            return;
        }
        dir^=1;
    }
    cout << 1 << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}