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
    string s[2];
    for(int i=0;i<2;i++)cin >> s[i];
    int ans=0;
    for(int t=0;t<2;t++){
        for(int i=1;i+1<n;i++){
            if(s[0][i]=='.'&&s[1][i]=='.'&&s[0][i-1]=='.'&&s[0][i+1]=='.'&&s[1][i-1]=='x'&&s[1][i+1]=='x'){
                ans++;
            }
        }
        swap(s[0],s[1]);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}