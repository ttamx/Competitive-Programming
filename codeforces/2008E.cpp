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
    vector<vector<int>> pre(n,vector<int>(26));
    vector<vector<int>> suf(n,vector<int>(26));
    for(int i=0;i<n;i++){
        pre[i][s[i]-'a']++;
        suf[i][s[i]-'a']++;
    }
    for(int i=2;i<n;i++){
        for(int j=0;j<26;j++){
            pre[i][j]+=pre[i-2][j];
        }
    }
    for(int i=n-3;i>=0;i--){
        for(int j=0;j<26;j++){
            suf[i][j]+=suf[i+2][j];
        }
    }
    if(n%2==0){
        int mx1=0,mx2=0;
        for(int i=0;i<26;i++){
            mx1=max(mx1,pre[n-1][i]);
            mx2=max(mx2,pre[n-2][i]);
        }
        cout << n-mx1-mx2 << "\n";
    }else{
        int ans=INF;
        for(int i=0;i<n;i++){
            int mx1=0,mx2=0;
            for(int j=0;j<26;j++){
                int val1=0,val2=0;
                if(i>0){
                    val1+=pre[i-1][j];
                }
                if(i>1){
                    val2+=pre[i-2][j];
                }
                if(i+1<n){
                    val2+=suf[i+1][j];
                }
                if(i+2<n){
                    val1+=suf[i+2][j];
                }
                mx1=max(mx1,val1);
                mx2=max(mx2,val2);
            }
            ans=min(ans,n-1-mx1-mx2);
        }
        cout << ans+1 << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}