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
    vector<int> a(n+1);
    for(int i=0;i<n;i++)a[i+1]=a[i]+(s[i]=='1'?1:-1);
    if(a[n]==0)return void(cout << "EMPTY\n");
    vector<deque<char>> dp(2*n+1);
    auto upd=[&](int i,const string &s){
        i+=n;
        for(int j=0;j<s.size();j++){
            if(j==dp[i].size()||s[j]<dp[i][j]){
                for(int j=s.size()-1;j>=0;j++)dp[i].emplace_front(s[j]);
                return;
            }
            if(s[j]>dp[i][j])return;
        }
    };
    for(int i=n-1;i>=0;i--){

    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}