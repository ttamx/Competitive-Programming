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

template<class T>
struct fenwick{
    int n;
    vector<T> t;
    fenwick(int n=0){init(n);}
    void init(int _n){
        n=_n;
        t.assign(n+1,T{});
    }
    void update(int x,const T &v){
        for(int i=x+1;i<=n;i+=i&-i)t[i]=t[i]+v;
    }
    void update(int l,int r,const T &v){
        update(l,v),update(r+1,-v);
    }
    T query(int x){
        T res{};
        for(int i=x+1;i>0;i-=i&-i)res=res+t[i];
        return res;
    }
    T query(int l,int r){
        return query(r)-query(l-1);
    }
    int find(const T &k){
        int x=0;
        T cur{};
        for(int i=1<<31-__builtin_clz(n);i>0;i>>=1)
            if(x+i<=n&&cur+t[x+i]<k)x+=i,cur=cur+t[x];
        return x;
    }
};

void runcase(){
    int n;
    cin >> n;
    vector<vi> pos(n);
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        pos[x].emplace_back(i);
    }
    if(sz(pos[0])!=1)return void(cout << "NO\n");
    int cnt=n;
    vector<pii> range;
    range.emplace_back(0,n-1);
    for(int i=0;i<n;i++){
        if(range.empty())break;
        reverse(all(pos[i]));
        vector<pii> nrange;
        for(auto [l,r]:range){
            assert(l<=r);
            bool ok=false;
            while(!pos[i].empty()&&pos[i].back()<=r){
                ok=true;
                int x=pos[i].back();
                pos[i].pop_back();
                if(x!=l)nrange.emplace_back(l,x-1);
                l=x+1;
            }
            if(!ok)return void(cout << "NO\n");
            if(l<=r)nrange.emplace_back(l,r);
        }
        swap(range,nrange);
    }
    cout << "YES\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}