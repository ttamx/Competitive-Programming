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

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m,k;
    cin >> n >> m >> k;
    vi c(n),cnt(n),freq(n),cnt2(n);
    for(auto &x:c)cin >> x,cnt[--x]++;
    for(int i=0;i<n;i++)c.emplace_back(c[i]);
    int uniq=0,ans=0;
    for(int l=0,r=0;l<n;l++){
        while(r<l+n&&uniq<m){
            if((freq[c[r]]++)%k==0){
                uniq++;
                ans+=min(k,cnt[c[r]]-(cnt2[c[r]]++)*k);
            }
            r++;
        }
        cout << ans << "\n";
        if((--freq[c[l]])%k==0){
            uniq--;
            ans-=min(k,cnt[c[l]]-(--cnt2[c[l]])*k);
        }
    }
}