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
    vector<int> deg(n);
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        deg[u]++,deg[v]++;
    }
    string s;
    cin >> s;
    if(s[0]!='?'){
        int base=0,cnt=0;
        for(int i=1;i<n;i++){
            if(deg[i]==1){
                if(s[i]=='?'){
                    cnt++;
                }else if(s[i]!=s[0]){
                    base++;
                }
            }
        }
        cout << base+(cnt+1)/2 << "\n";
    }else{
        int c[2]={};
        int cnt=0,dump=0;
        for(int i=1;i<n;i++){
            if(deg[i]==1){
                if(s[i]=='?'){
                    cnt++;
                }else{
                    c[s[i]-'0']++;
                }
            }else{
                if(s[i]=='?'){
                    dump++;
                }
            }
        }
        int ans=max(c[0],c[1])+cnt/2;
        if(dump%2==1){
            ans=max(ans,min(c[0],c[1])+(cnt+1)/2);
        }
        cout << ans << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}