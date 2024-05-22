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
    vi a(n);
    for(auto &x:a)cin >> x;
    int l=1,r=n;
    auto check=[&](int k){
        vi cnt(30),v(30);
        for(int i=0;i<k;i++){
            for(int j=0;j<30;j++)if(a[i]>>j&1){
                cnt[j]++;
                v[j]=1;
            }
        }
        for(int i=k;i<n;i++){
            for(int j=0;j<30;j++)if(a[i-k]>>j&1){
                cnt[j]--;
            }
            for(int j=0;j<30;j++){
                cnt[j]+=a[i]>>j&1;
                if(v[j]!=(cnt[j]>0))return false;
            }
        }
        return true;
    };
    while(l<r){
        int m=(l+r)/2;
        if(check(m))r=m;
        else l=m+1;
    }
    cout << l << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}