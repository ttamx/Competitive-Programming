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
    int n,q;
    cin >> n >> q;
    vector<tuple<ll,ll,ll>> p;
    ll s=0;
    for(int i=0;i<n;i++){
        ll t,x;
        cin >> t >> x;
        if(t==1){
            p.emplace_back(s,1,x);
            s++;
        }else{
            p.emplace_back(s,2,s);
            if(1.l*s*(x+1)>LINF){
                s=LINF;
            }else{
                s*=(x+1);
            }
        }
    }
    priority_queue<pll> qrs;
    for(int i=0;i<q;i++){
        ll x;
        cin >> x;
        x--;
        qrs.emplace(x,i);
    }
    reverse(all(p));
    vl ans(q);
    for(auto [s,t,x]:p){
        while(!qrs.empty()){
            auto [id,i]=qrs.top();
            if(id<s)break;
            qrs.pop();
            if(t==1){
                ans[i]=x;
            }else{
                qrs.emplace(id%s,i);
            }
        }
    }
    for(auto x:ans)cout << x << " ";
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}