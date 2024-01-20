#include<bits/stdc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()

using namespace std;

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

namespace std {

template<class Fun>
class y_combinator_result {
    Fun fun_;
public:
    template<class T>
    explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}

    template<class ...Args>
    decltype(auto) operator()(Args &&...args) {
        return fun_(std::ref(*this), std::forward<Args>(args)...);
    }
};

template<class Fun>
decltype(auto) y_combinator(Fun &&fun) {
    return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}

} // namespace std

void runcase(){
    ll hh,h,w,xa,ya,xb,yb;
    cin >> hh >> w >> xa >> ya >> xb >> yb;
    h=xb-xa;
    if(h<=0||xa==hh||xb==1)return void(cout << "Draw\n");
    auto solve=[&](ll w,ll xa,ll ya,ll xb,ll yb){
        ll h=llabs(xb-xa);
        if(ya==yb)return 1;
        if(ya<yb){
            return (yb-1)*2<=h?1:0;
        }else{
            return (w-yb)*2<=h?1:0;
        }
    };
    if(h%2==0){
        cout << (solve(w,xa,ya,xb,yb)?"Bob":"Draw") << "\n";
    }else{
        if(llabs(ya-yb)<=1){
            cout << "Alice\n";
        }else if(h>1){
            int res=0;
            if(xa+1<hh)for(int i=-1;i<=1;i++)if(1<=ya+i&&ya+i<=w){
                res=max(res,solve(w,xb,yb,xa+1,ya+i));
            }
            cout << (res?"Alice":"Draw") << "\n";
        }else{
            cout << "Draw\n";
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}