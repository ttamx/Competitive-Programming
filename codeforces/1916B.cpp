#include<bits/stdc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()

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

const int N=32005;

bool b[N];
vl p;

void runcase(){
    ll a,b;
    cin >> a >> b;
    ll g=gcd(a,b);
    a/=g,b/=g;
    if(a==1)cout << b*b*g << "\n";
    else cout << a*b*g << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=2;i<N;i++)if(!b[i]){
        p.emplace_back(i);
        for(int j=i+i;j<N;j+=i)b[i]=true;
    }
    int t(1);
    cin >> t;
    while(t--)runcase();
}