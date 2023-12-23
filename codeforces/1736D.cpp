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
const int MOD=1000000007;
// const int MOD=998224353;
const ll LINF=0x1fffffffffffffff;
const db DINF=numeric_limits<db>::infinity();
const db EPS=1e-9;
const db PI=acos(db(-1));

void runcase(){
    int n;
    string s;
    cin >> n >> s;
    bool ok=true;
    for(auto x:s)ok^=x=='1';
    if(!ok)return void(cout << "-1\n");
    vi v;
    for(int i=0,c=0;i<2*n;i+=2)if(s[i]!=s[i+1])v.emplace_back(i+(s[i]-'0'==(c^=1)));
    cout << v.size() << " ";
    for(auto x:v)cout << x+1 << " ";
    cout << "\n";
    for(int i=1;i<=n;i++)cout << 2*i << " \n"[i==n];
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}