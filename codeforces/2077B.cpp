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

const int LOCAL=false;

void runcase(){
    int x,y;
    if(LOCAL){
        // cin >> x >> y;
        x=rng()&((1<<30)-1);
        y=rng()&((1<<30)-1);
    }
    auto ask=[&](int n){
        if(LOCAL){
            return (n|x)+(n|y);
        }else{
            cout << n << endl;
            int res;
            cin >> res;
            return res;
        }
    };
    int mask=0;
    for(int i=0;i<30;i+=2){
        mask|=1<<i;
    }
    int sum=ask(0);
    int sum2=ask(mask);
    vector<int> c(30);
    for(int i=1;i<30;i+=2){
        int a1=(sum>>i&1);
        int a2=(sum>>(i+1)&1);
        int b1=(sum2>>i&1);
        int b2=(sum2>>(i+1)&1);
        c[i]=b2*2+b1-1;
    }
    int carry=0;
    for(int i=0;i<30;i+=2){
        int a1=(sum>>i&1);
        int a2=(sum>>(i+1)&1);
        int b1=(sum2>>i&1);
        int b2=(sum2>>(i+1)&1);
        if(a1^carry){
            c[i]=1;
        }else{
            c[i]=(a2^(c[i+1]&1))*2;
        }
        carry=(c[i+1]*2+c[i]+carry)/4;
    }
    cout << "!" << endl;
    int n;
    if(LOCAL){
        n=rng()&((1<<30)-1);
    }else{
        cin >> n;
    }
    int ans=0;
    for(int i=0;i<30;i++){
        if(n>>i&1){
            ans+=2<<i;
        }else{
            ans+=c[i]<<i;
        }
    }
    cout << ans << endl;
    if(LOCAL){
        cerr << "OUTPUT " << bitset<30>(ans) << "\n";
        cerr << "ANSWER " << bitset<30>(ask(n)) << "\n";
        assert(ans==ask(n));
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}