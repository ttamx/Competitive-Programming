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
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
        x--;
    }
    string s;
    cin >> s;
    vector<int> dp(n,-1);
    for(int i=0;i<n;i++)if(dp[i]==-1){
        vector<int> c{i};
        for(int j=a[i];j!=i;j=a[j]){
            c.emplace_back(j);
        }
        int cnt=0;
        for(auto j:c){
            if(s[j]=='0'){
                cnt++;
            }
        }
        for(auto j:c){
            dp[j]=cnt;
        }
    }
    for(auto x:dp)cout << x << " ";
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}