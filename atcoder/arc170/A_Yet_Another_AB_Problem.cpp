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
    string s,t;
    cin >> s >> t;
    bool ok=false;
    int ans=0,ca=0,rem=0,pa=-1,pb=-1;
    for(int i=0;i<n;i++){
        if(s[i]!=t[i]){
            if(t[i]=='A')ca++,pa=i;
            else{
                ans++;
                if(!ok)return void(cout << "-1\n");
                if(ca)ca--;
            }
        }
        if(t[i]=='A')ok=true;
        else pb=i;
    }
    if(ca>0&&pb<pa)return void(cout << "-1\n");
    cout << ans+ca << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    // cin >> t;
    while(t--)runcase();
}