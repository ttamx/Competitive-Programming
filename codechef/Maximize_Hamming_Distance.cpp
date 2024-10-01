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
    vector<array<int,2>> cnt(n,{0,0});
    for(int i=0;i<m;i++){
        string s;
        cin >> s;
        for(int j=0;j<n;j++){
            if(s[j]=='0'){
                cnt[j][0]++;
            }else if(s[j]=='1'){
                cnt[j][1]++;
            }
        }
    }
    ll ans=0;
    for(int i=0;i<n;i++){
        if(cnt[i][0]<cnt[i][1]){
            swap(cnt[i][0],cnt[i][1]);
        }
        if(cnt[i][0]<m/2){
            cnt[i][0]=m/2;
        }
        ans+=1LL*cnt[i][0]*(m-cnt[i][0]);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}