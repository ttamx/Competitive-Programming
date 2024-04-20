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
    string s;
    cin >> s;
    int cnt[300]={};
    for(auto x:s)cnt[x]++;
    vi a(sz(s)+1);
    for(int c='a';c<='z';c++)a[cnt[c]]++;
    for(int c='a';c<='z';c++)if(cnt[c]){
        int x=a[cnt[c]];
        if(x!=0&&x!=2)cout << "No",exit(0);
    }
    cout << "Yes";
}