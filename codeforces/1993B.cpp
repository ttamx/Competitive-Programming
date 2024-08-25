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
    vector<vector<int>> a(2);
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        a[x&1].emplace_back(x);
    }
    for(auto &v:a){
        sort(v.begin(),v.end());
        if(v.empty()){
            cout << "0\n";
            return;
        }
    }
    int mx=a[1].back();
    int ans=0;
    for(auto x:a[0]){
        if(x<mx){
            x+=mx;
            mx=max(mx,x);
            ans++;
        }else{
            ans+=2;
            mx+=a[0].back();
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}