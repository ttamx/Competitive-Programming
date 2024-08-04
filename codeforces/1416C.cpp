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

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    int ans=0;
    ll ans2=0;
    for(int b=29;b>=0;b--){
        unordered_map<int,array<int,2>> cnt;
        array<ll,2> v{0,0};
        for(auto x:a){
            int i=x>>(b+1),j=x>>b&1;
            auto &c=cnt[i];
            c[j]++;
            v[j]+=c[j^1];
        }
        if(v[1]<v[0])ans|=(1<<b);
        ans2+=min(v[1],v[0]);
    }
    cout << ans2 << " " << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}