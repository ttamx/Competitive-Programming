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
    int n,m;
    cin >> n >> m;
    tuple<int,int,int> mx(0,0,0);
    for(int i=0;i<n;i++){
        string s;
        cin >> s;
        int l=0,r=m-1;
        while(l<m&&s[l]=='.')l++;
        while(r>=l&&s[r]=='.')r--;
        mx=max(mx,{r-l+1,i,(l+r)/2});
    }
    cout << get<1>(mx)+1 << " " << get<2>(mx)+1 << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}