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
    vector<ll> a(n);
    for(auto &x:a)cin >> x;
    vector<ll> ans(n);
    for(int i=1;i<n;i++){
        if(a[i]==a[i-1]){
            ans[i]=ans[i-1];
        }else if(a[i]<a[i-1]){
            if(a[i]==1)return void(cout << "-1\n");
            ll x=a[i];
            ans[i]=ans[i-1];
            while(x<a[i-1]){
                ans[i]++;
                x*=x;
            }
        }else if(a[i-1]==1){
            ans[i]=0;
        }else{
            ll x=a[i-1];
            ans[i]=ans[i-1]+1;
            while(x<=a[i]){
                ans[i]--;
                x*=x;
            }
            ans[i]=max(ans[i],0LL);
        }
    }
    cout << accumulate(ans.begin(),ans.end(),0LL) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}