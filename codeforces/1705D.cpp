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
    string s,t;
    cin >> s >> t;
    if(s[0]!=t[0])return void(cout << "-1\n");
    queue<int> a,b;
    for(int i=0;i<n-1;i++){
        if(s[i]!=s[i+1])a.emplace(i);
        if(t[i]!=t[i+1])b.emplace(i);
    }
    if(a.size()!=b.size())return void(cout << "-1\n");
    ll ans=0;
    while(!a.empty()){
        ans+=abs(a.front()-b.front());
        a.pop(),b.pop();
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}