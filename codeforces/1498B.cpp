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
    int n,w;
    cin >> n >> w;
    vector<int> cnt(20);
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        cnt[__builtin_ctz(x)]++;
    }
    int ans=0;
    while(n>0){
        ans++;
        int cur=0;
        for(int i=19;i>=0;i--){
            while(cnt[i]>0&&cur+(1<<i)<=w){
                cnt[i]--,n--;
                cur+=1<<i;
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