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

int t[300];

void runcase(){
    int n;
    string s;
    cin >> n >> s;
    vi c(n);
    cout << s.substr(0,2);
    for(int i=2;i<n-1;i++){
        if(!t[s[i]]&&t[s[i+1]])cout << ".";
        cout << s[i];
    }
    if(n>2)cout << s[n-1];
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    t['a']=t['e']=1;
    int t(1);
    cin >> t;
    while(t--)runcase();
}