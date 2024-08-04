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
    vector a(n,vector<int>(m)),b(n,vector<int>(m));
    for(auto &x:a){
        string s;
        cin >> s;
        for(int i=0;i<m;i++)x[i]=s[i]-'0';
    }
    for(auto &x:b){
        string s;
        cin >> s;
        for(int i=0;i<m;i++)x[i]=s[i]-'0';
    }
    for(int i=0;i+1<n;i++){
        for(int j=0;j+1<m;j++){
            int d=(b[i][j]-a[i][j]+3)%3;
            a[i][j]=(a[i][j]+d)%3;
            a[i+1][j+1]=(a[i+1][j+1]+d)%3;
            a[i+1][j]=(a[i+1][j]+d*2)%3;
            a[i][j+1]=(a[i][j+1]+d*2)%3;
        }
    }
    for(int i=0;i<n;i++)for(int j=0;j<m;j++)if(a[i][j]!=b[i][j])return void(cout << "NO\n");
    cout << "YES\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}