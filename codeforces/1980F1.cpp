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
    ll n,m,k;
    cin >> n >> m >> k;
    vector<pll> a(k);
    for(auto &[x,y]:a)cin >> y >> x;
    auto c=a;
    sort(all(a),[&](pll i,pll j){
        if(i.first==j.first)return i.second>j.second;
        return i.first<j.first;
    });
    vector<pll> b;
    ll ans=0;
    for(auto [x,y]:a){
        if(b.empty()){
            ans+=1LL*n*(x-1);
            b.emplace_back(x,y);
        }else if(b.back().second<y){
            ans+=1LL*(n-b.back().second)*(x-b.back().first);
            b.emplace_back(x,y);
        }
    }
    ans+=1LL*(n-b.back().second)*(m-b.back().first+1);
    cout << ans << "\n";
    sort(all(b));
    for(auto e:c){
        auto it=lower_bound(b.begin(),b.end(),e);
        cout << (it!=b.end()&&(*it)==e) << " ";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}