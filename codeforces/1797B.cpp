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
    int n,k;
    cin >> n >> k;
    vector<vector<int>> a(n,vector<int>(n));
    for(auto &v:a)for(auto &x:v)cin >> x;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            int x=n-i-1,y=n-j-1;
            if(a[i][j]!=a[x][y]){
                a[i][j]^=1;
                k--;
            }
        }
    }
    cout << ((k>=0&&(k%2==0||n%2==1))?"YES":"NO") << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}