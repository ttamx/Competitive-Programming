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

const int N=2e7;

bool not_prime[N+1];
vector<int> primes;

void runcase(){
    int n,m;
    ll a,b;
    cin >> n >> m >> a >> b;
    int p=n;
    while(not_prime[p])p--;
    int st=max(1,p-100);
    int gx=n-st;
    int gy=n-p;
    vector<vector<bool>> vis(gx+1,vector<bool>(gy+1));
    vis[0][0]=true;
    if(a>b)swap(a,b);
    ll ans=a*st+b*p;
    for(int i=0;i<=gx;i++){
        for(int j=0;j<=gy;j++){
            if((j>0&&vis[i][j-1])||(i>0&&vis[i-1][j])){
                if(gcd(st+i,p+j)==1){
                    vis[i][j]=true;
                    ans=max(ans,a*(st+i)+b*(p+j));
                }
            }
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    not_prime[0]=not_prime[1]=true;
    for(int i=2;i<=N;i++){
        if(not_prime[i])continue;
        primes.emplace_back(i);
        for(int j=2;i*j<=N;j++){
            not_prime[i*j]=true;
        }
    }
    int t(1);
    cin >> t;
    while(t--)runcase();
}