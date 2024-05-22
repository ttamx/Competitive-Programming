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
    int n,k,s1,s2;
    cin >> n >> k >> s1 >> s2;
    s1--,s2--;
    vi p(n);
    vl a(n);
    for(auto &x:p)cin >> x,x--;
    for(auto &x:a)cin >> x;
    auto calc=[&](int s){
        ll res=0,sum=0;
        for(int i=1;i<=min(n,k);i++){
            sum+=a[s];
            res=max(res,sum+a[s]*(k-i));
            s=p[s];
        }
        return res;
    };
    ll v1=calc(s1),v2=calc(s2);
    if(v1>v2)cout << "Bodya\n";
    else if(v1<v2)cout << "Sasha\n";
    else cout << "Draw\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}