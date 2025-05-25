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

const db PHI=(1.0+sqrt(5.0))/2.0;
const db IPHI=1.0/PHI;

void runcase(){
    int s,a,b,c;
    cin >> s >> a >> b >> c;
    auto calc=[&](db x)->pair<db,db> {
        db l=0,r=s-x;
        auto eval=[&](db y){
            db z=s-x-y;
            return a*log(x)+b*log(y)+c*log(z);
        };
        while(r-l>EPS){
            db d=(r-l)*IPHI;
            db ml=r-d,mr=l+d;
            if(eval(ml)>eval(mr))r=mr;
            else l=ml;
        }
        db y=(l+r)/2;
        return make_pair(eval(y),y);
    };
    db l=0,r=s;
    while(r-l>EPS){
        db d=(r-l)*IPHI;
        db ml=r-d,mr=l+d;
        if(calc(ml).first>calc(mr).first)r=mr;
        else l=ml;
    }
    db x=(l+r)/2;
    db y=calc(x).second;
    db z=s-x-y;
    cout << fixed << setprecision(20) << x << " " << y << " " << z << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}