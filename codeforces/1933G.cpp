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

vector<vector<vi>> p(8,vector<vi>(4,vi(4)));

void runcase(){
    int n,m,q;
    cin >> n >> m >> q;
    vi ok(8,1);
    cout << 8 << "\n";
    while(q--){
        int x,y;
        string s;
        cin >> x >> y >> s;
        int c=s=="circle";
        x--,y--;
        x%=4,y%=4;
        for(int i=0;i<8;i++)if(p[i][x][y]!=c)ok[i]=0;
        cout << accumulate(all(ok),0) << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=0;i<4;i++)for(int j=0;j<4;j++)p[0][i][j]=(i%2==0)^(j<2);
    for(int i=0;i<4;i++)for(int j=0;j<4;j++)p[1][i][j]=(i%2==0)^(0<j&&j<3);
    for(int i=0;i<4;i++)for(int j=0;j<4;j++)p[2][i][j]=(j%2==0)^(i<2);
    for(int i=0;i<4;i++)for(int j=0;j<4;j++)p[3][i][j]=(j%2==0)^(0<i&&i<3);
    for(int i=0;i<4;i++)for(int j=0;j<4;j++)p[4][i][j]=1-((i%2==0)^(j<2));
    for(int i=0;i<4;i++)for(int j=0;j<4;j++)p[5][i][j]=1-((i%2==0)^(0<j&&j<3));
    for(int i=0;i<4;i++)for(int j=0;j<4;j++)p[6][i][j]=1-((j%2==0)^(i<2));
    for(int i=0;i<4;i++)for(int j=0;j<4;j++)p[7][i][j]=1-((j%2==0)^(0<i&&i<3));
    int t(1);
    cin >> t;
    while(t--)runcase();
}