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
    int n,q;
    cin >> n >> q;
    vector<int> a(n);
    vector<int> cnt(n+1);
    for(auto &x:a){
        cin >> x;
        cnt[x]++;
    }
    for(int i=1;i<=n;i++){
        cnt[i]+=cnt[i-1];
    }
    vector<int> ans(n+1);
    for(int i=1;i<=n;i++){
        int l=0,r=i-1;
        while(l<r){
            int m=(l+r)/2;
            int tot=0;
            for(int j=0;j<=n;j+=i){
                tot+=cnt[min(j+m,n)]-(j?cnt[j-1]:0);
            }
            if(tot>=(n+2)/2)r=m;
            else l=m+1;
        }
        ans[i]=l;
    }
    while(q--){
        int x;
        cin >> x;
        cout << ans[x] << " ";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}