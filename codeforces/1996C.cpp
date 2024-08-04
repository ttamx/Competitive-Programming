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
    int n,q;
    cin >> n >> q;
    string a,b;
    cin >> a >> b;
    vector<vector<int>> c1(n,vector<int>(26)),c2(n,vector<int>(26));
    for(int i=0;i<n;i++){
        c1[i][a[i]-'a']++;
        c2[i][b[i]-'a']++;
    }
    for(int i=1;i<n;i++){
        for(int j=0;j<26;j++){
            c1[i][j]+=c1[i-1][j];
            c2[i][j]+=c2[i-1][j];
        }
    }
    while(q--){
        int l,r;
        cin >> l >> r;
        l--,r--;
        int l1=0,l2=0,ans=0;
        for(int i=0;i<26;i++){
            int d1=c1[r][i];
            int d2=c2[r][i];
            if(l>0){
                d1-=c1[l-1][i];
                d2-=c2[l-1][i];
            }
            ans+=abs(d1-d2);
        }
        cout << ans/2 << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}