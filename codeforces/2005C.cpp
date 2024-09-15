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
    int n,m;
    cin >> n >> m;
    vector<string> a(n);
    for(auto &x:a){
        cin >> x;
    }
    vector<int> dp(5,-INF);
    dp[0]=0;
    string t="narek";
    auto check=[&](char c){
        for(auto x:t){
            if(c==x){
                return true;
            }
        }
        return false;
    };
    for(auto &s:a){
        auto ndp=dp;
        for(int i=0;i<5;i++){
            int score=dp[i];
            int cur=i;
            for(int j=0;j<m;j++){
                if(check(s[j])){
                    score--;
                }
                if(s[j]==t[cur]){
                    cur++;
                    if(cur==5){
                        score+=10;
                        cur=0;
                    }
                }
            }
            ndp[cur]=max(ndp[cur],score);
        }
        swap(dp,ndp);
    }
    cout << *max_element(dp.begin(),dp.end()) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}