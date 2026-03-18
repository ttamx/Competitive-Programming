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

int n,m;
ll ans=0;
vector<int> a;
int base=0;

// contains c copies of [0,2^(b+1))
void dnc(int l,int r,int d,int b,ll c){
    if(l==r||d<0)return;
    int p=l;
    while(p<r&&!(a[p]>>d&1))p++;
    // cerr << d << " : " << l << " " << p << " " << r << " x" << c << "\n";
    if(d>b){
        if(base>>d&1){
            if(p<r){
                dnc(p,r,d-1,b,c);
            }else{
                // cerr << "NOT FOUND +" << (1LL<<(b+d+1)) << "\n";
                ans+=1LL<<(b+d+1);
                dnc(l,p,d-1,b,c);
            }
        }else{
            if(l<p){
                dnc(l,p,d-1,b,c);
            }else{
                // cerr << "NOT FOUND +" << (1LL<<(b+d+1)) << "\n";
                ans+=1LL<<(b+d+1);
                dnc(p,r,d-1,b,c);
            }
        }
        return;
    }
    if(p==l||p==r){
        ans+=c<<(b*2);
        c*=2;
    }
    // cerr << ans << "\n";
    dnc(l,p,d-1,b-1,c);
    dnc(p,r,d-1,b-1,c);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    a.resize(n);
    for(auto &x:a){
        cin >> x;
    }
    sort(a.begin(),a.end());
    for(int i=29;i>=1;i--){
        if(m>>i&1){
            ll tmp=ans;
            // cerr << "AT BIT " << i << "\n";
            dnc(0,n,29,i-1,1);
            // cerr << i << " : " << ans-tmp << "\n";
            base|=1<<i;
        }
    }
    if(m&1){
        m--;
        int mn=INF;
        for(auto x:a){
            mn=min(mn,m^x);
        }
        ans+=mn;
    }
    cout << ans << "\n";
}