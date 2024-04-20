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

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    string s,t;
    cin >> s >> t;
    s+='X';
    int p=0;
    int n=sz(s);
    for(auto c:t){
        while(p<n&&toupper(s[p])!=c)p++;
        if(p>=n)cout << "No",exit(0);
        p++;
    }
    cout << "Yes";
}