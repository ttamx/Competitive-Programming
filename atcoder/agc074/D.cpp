#include<bits/stdc++.h>

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
    int m=n*(n-1)/2;
    vector<int> a(m);
    for(auto &x:a){
        cin >> x;
    }
    int c=(n-1)*(n-2)/2;
    int p=m;
    for(int i=0;i<m;i++){
        if(a[i]){
            c--;
        }
        if(c<0){
            p=i;
            break;
        }
    }
    int cnt=0,ans=0;
    for(int i=p+1;i<m;i++){
        if(a[i]==0){
            ans+=i-p-cnt;
            cnt++;
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