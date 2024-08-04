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
    string s;
    cin >> n >> s;
    auto ans=s;
    int ans2=1;
    for(int k=2;k<=n;k++){
        string t1=s.substr(k-1,n);
        string t2=s.substr(0,k-1);
        if((n-k)%2==0)reverse(t2.begin(),t2.end());
        string t=t1+t2;
        if(t<ans){
            ans=t;
            ans2=k;
        }
    }
    cout << ans << "\n";
    cout << ans2 << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}