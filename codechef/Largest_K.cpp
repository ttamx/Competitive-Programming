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
    map<int,int> cnt;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        cnt[x]++;
    }
    vector<int> a;
    for(auto [x,y]:cnt){
        a.emplace_back(y);
    }
    sort(a.rbegin(),a.rend());
    int m=a.size();
    int cur=0;
    int ans=0;
    for(int i=1;i<=m;i++){
        cur+=a[i-1];
        for(int j=i;j<=cur;j+=i){
            ans=max(ans,j);
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