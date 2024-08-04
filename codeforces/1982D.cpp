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
    int n,m,k;
    cin >> n >> m >> k;
    vector<vector<int>> a(n,vector<int>(m)),b(n,vector<int>(m));
    for(auto &x:a)for(auto &y:x)cin >> y;
    ll sum=0;
    for(int i=0;i<n;i++){
        string s;
        cin >> s;
        for(int j=0;j<m;j++){
            if(s[j]=='1'){
                sum+=a[i][j];
                b[i][j]=1;
            }else{
                sum-=a[i][j];
                b[i][j]=-1;
            }
            if(i)b[i][j]+=b[i-1][j];
            if(j)b[i][j]+=b[i][j-1];
            if(i&&j)b[i][j]-=b[i-1][j-1];
        }
    }
    sum=abs(sum);
    if(sum==0)return void(cout << "YES\n");
    int g=0;
    for(int i=k-1;i<n;i++){
        for(int j=k-1;j<m;j++){
            int v=b[i][j];
            if(i>=k)v-=b[i-k][j];
            if(j>=k)v-=b[i][j-k];
            if(i>=k&&j>=k)v+=b[i-k][j-k];
            g=gcd(g,abs(v));
        }
    }
    cout << (g>0&&sum%g==0?"YES":"NO") << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}