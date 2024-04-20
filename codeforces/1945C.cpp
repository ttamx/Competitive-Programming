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
    string s;
    cin >> s;
    int cnt=0;
    for(auto x:s)cnt+=x=='1';
    int sum=0;
    pii ans(INF,n);
    for(int i=0;i<n;i++){
        if(i-sum>=(i+1)/2&&cnt-sum>=(n-i+1)/2){
            ans=min(ans,pii(abs(n-2*i),i));
        }
        sum+=s[i]=='1';
    }
    cout << ans.second << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}