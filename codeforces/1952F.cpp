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
    vector<string> s(21);
    for(auto &x:s)cin >> x;
    int ans=0;
    for(int i=3;i<21;i++){
        for(int j=3;j<21;j++){
            int sum=0;
            for(int x=0;x<4;x++){
                for(int y=0;y<4;y++){
                    sum+=s[i-x][j-y]-'0';
                }
            }
            ans=max(ans,sum);
        }
    }
    cout << ans;
}