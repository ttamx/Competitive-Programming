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

using ull = unsigned long long;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

int n,m;

vector<vi> a;
vector<vector<ull>> hsh;
vector<ull> hsh2;

vector<vi> rot(int op,const vector<vi> &a){
    int x=op&1,y=op>>1;
    auto b=a;
    for(int i=0;i<n-1;i++){
        for(int j=0;j<m-1;j++){
            b[i+x][j+y]=a[n-i-2+x][m-j-2+y];
        }
    }
    return b;
}

ull hashing(const vector<vi> &a){
    ull res=0;
    for(int i=0;i<n;i++)for(int j=0;j<m;j++)res+=hsh[i][j]*hsh2[a[i][j]];
    return res;
}

map<ull,int> mp1,mp2;

void solve1(const vector<vi> &a,int cnt,int op){
    ull res=hashing(a);
    auto it=mp1.find(res);
    if(it==mp1.end()){
        mp1[res]=cnt;
    }else{
        it->second=min(it->second,cnt);
    }
    if(cnt<10){
        for(int i=0;i<4;i++)if(i!=op){
            solve1(rot(i,a),cnt+1,i);
        }
    }
}

void solve2(const vector<vi> &a,int cnt,int op){
    ull res=hashing(a);
    auto it=mp2.find(res);
    if(it==mp2.end()){
        mp2[res]=cnt;
    }else{
        it->second=min(it->second,cnt);
    }
    if(cnt<10){
        for(int i=0;i<4;i++)if(i!=op){
            solve2(rot(i,a),cnt+1,i);
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    a.assign(n,vi(m));
    hsh.assign(n,vector<ull>(m));
    hsh2.assign(n*m,0);
    for(auto &x:a)for(auto &y:x)cin >> y,y--;
    for(auto &x:hsh)for(auto &y:x)y=rng();
    for(auto &x:hsh2)x=rng();
    solve1(a,0,-1);
    vector<vi> b(n,vi(m));
    for(int i=0;i<n;i++)for(int j=0;j<m;j++)b[i][j]=i*m+j;
    solve2(b,0,-1);
    int ans=21;
    for(auto [val,cnt]:mp1){
        auto it=mp2.find(val);
        if(it==mp2.end())continue;
        ans=min(ans,cnt+it->second);
    }
    if(ans>20)ans=-1;
    cout << ans << "\n";
}