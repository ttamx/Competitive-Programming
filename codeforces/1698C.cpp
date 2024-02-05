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
    vl a(n);
    for(auto &x:a)cin >> x;
    sort(all(a));
    if(n<=5){
        for(int i=0;i<n;i++){
            for(int j=0;j<i;j++){
                for(int k=0;k<j;k++){
                    if(find(all(a),a[i]+a[j]+a[k])==a.end())return void(cout << "NO\n");
                }
            }
        }
        cout << "YES\n";
    }else if(a[1]!=0||a[n-2]!=0){
        cout << "NO\n";
    }else if(a[0]==0||a[n-1]==0){
        cout << "YES\n";
    }else{
        cout << (a[0]+a[n-1]==0?"YES":"NO") << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}