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

const int N=1e5+5;

int pos[N];

void runcase(){
    int n,k;
    cin >> n >> k;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    vector<int> f;
    for(int i=1;i*i<=k;i++)if(k%i==0){
        f.emplace_back(i);
        if(i*i<k)f.emplace_back(k/i);
    }
    int m=f.size();
    sort(f.begin(),f.end());
    for(int i=0;i<m;i++)pos[f[i]]=i;
    vector<bool> ok(m);
    ok[0]=true;
    int ans=1;
    for(auto x:a)if(k%x==0&&x>1){
        for(int i=m-1;i>=0;i--)if(ok[i]&&k%(1LL*x*f[i])==0){
            ok[pos[x*f[i]]]=true;
        }
        if(ok[m-1]){
            ans++;
            for(int i=1;i<m;i++)ok[i]=false;
            ok[pos[x]]=true;
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}