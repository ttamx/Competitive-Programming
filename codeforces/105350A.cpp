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
    int ans=0;
    auto check=[&](int a,int b,int c,int d){
        if(a+3<c)return true;
        if(b+2<d)return true;
        if(c+3<a)return true;
        if(d+2<b)return true;
        return false;
    };
    for(int i=3;i<n;i++){
        for(int j=2;j<m;j++){
            for(int x=3;x<n;x++){
                for(int y=2;y<m;y++){
                    ans+=check(i,j,x,y);
                }
            }
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