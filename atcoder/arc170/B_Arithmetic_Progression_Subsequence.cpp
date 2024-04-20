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
    vi pos(12,-1);
    vector<vi> pos2(12,vi(12,-1));
    ll ans=0;
    for(int i=0,p=-1;i<n;i++){
        int x;
        cin >> x;
        for(int j=-5;j<=5;j++){
            if(x+2*j>10||x+2*j<0)continue;
            p=max(p,pos2[x+j][x+2*j]);
        }
        for(int j=0;j<=10;j++){
            pos2[x][j]=max(pos2[x][j],pos[j]);
        }
        pos[x]=i;
        ans+=p+1;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    // cin >> t;
    while(t--)runcase();
}