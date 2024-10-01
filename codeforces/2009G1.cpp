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
    int n,k,q;
    cin >> n >> k >> q;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    for(int i=0;i<n;i++)a[i]-=i;
    map<int,int> cnt;
    multiset<int> ms;
    vector<int> dp(n);
    for(int i=0;i<n;i++)ms.emplace(0);
    for(int i=0;i<n;i++){
        if(i>=k){
            ms.erase(ms.find(cnt[a[i-k]]));
            cnt[a[i-k]]--;
            ms.emplace(cnt[a[i-k]]);
        }
        ms.erase(ms.find(cnt[a[i]]));
        cnt[a[i]]++;
        ms.emplace(cnt[a[i]]);
        dp[i]=*ms.rbegin();
    }
    while(q--){
        int l,r;
        cin >> l >> r;
        l--,r--;
        cout << r-l+1-dp[r] << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}