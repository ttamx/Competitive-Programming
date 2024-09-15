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
    for(auto &x:a){
        cin >> x;
    }
    vector<int> b;
    for(int i=0;i<n-1;i++){
        b.emplace_back(abs(a[i+1]-a[i]));
    }
    ll ans=n;
    map<int,int> cnt;
    for(auto g:b){
        map<int,int> new_cnt;
        new_cnt[g]++;
        for(auto [x,y]:cnt){
            new_cnt[gcd(g,x)]+=y;
        }
        swap(cnt,new_cnt);
        for(auto [x,y]:cnt){
            if(x==(x&-x)){
                ans+=y;
            }
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}