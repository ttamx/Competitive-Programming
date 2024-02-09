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
    int n;
    cin >> n;
    int m=0;
    while((1<<m)<n)m++;
    cout << m << endl;
    for(int i=0;i<m;i++){
        vi a;
        for(int j=0;j<n;j++)if(j>>i&1)a.emplace_back(j);
        cout << sz(a);
        for(auto &x:a)cout << " " << x+1;
        cout << endl;
    }
    string s;
    cin >> s;
    int ans=0;
    for(int i=0;i<m;i++)if(s[i]=='1')ans|=1<<i;
    cout << ans+1 << endl;
}