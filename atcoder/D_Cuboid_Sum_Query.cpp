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
    vector a(n+1,vector(n+1,vector<int>(n+1)));
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            for(int k=1;k<=n;k++){
                cin >> a[i][j][k];
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            for(int k=1;k<=n;k++){
                a[i][j][k]+=a[i-1][j][k]+a[i][j-1][k]+a[i][j][k-1]-a[i-1][j-1][k]-a[i-1][j][k-1]-a[i][j-1][k-1]+a[i-1][j-1][k-1];
            }
        }
    }
    int q;
    cin >> q;
    while(q--){
        int x1,y1,z1,x2,y2,z2;
        cin >> x1 >> x2 >> y1 >> y2 >> z1 >> z2;
        cout << a[x2][y2][z2]-a[x1-1][y2][z2]-a[x2][y1-1][z2]-a[x2][y2][z1-1]+a[x1-1][y1-1][z2]+a[x1-1][y2][z1-1]+a[x2][y1-1][z1-1]-a[x1-1][y1-1][z1-1] << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}