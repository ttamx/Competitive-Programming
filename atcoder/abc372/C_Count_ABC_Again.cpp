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
    string s;
    cin >> s;
    vector<int> a(n);
    auto calc=[&](int i){
        if(i<0||i+2>=n)return 0;
        if(s.substr(i,3)=="ABC")return 1;
        return 0;
    };
    int ans=0;
    for(int i=0;i<n;i++){
        a[i]=calc(i);
        ans+=a[i];
    }
    while(q--){
        int x;
        char c;
        cin >> x >> c;
        x--;
        s[x]=c;
        for(int i=max(0,x-2);i<=x;i++){
            ans-=a[i];
            a[i]=calc(i);
            ans+=a[i];
        }
        cout << ans << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}