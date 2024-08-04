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
    ll c;
    cin >> n >> c;
    vector<ll> a(n);
    for(auto &x:a)cin >> x;
    int mx=0;
    for(int i=0;i<n;i++)if(a[i]>a[mx])mx=i;
    vector<int> ans(n);
    int p=0;
    ll sum=c+a[p];
    while(p<mx&&pll(a[mx],-mx)<pll(sum,-p)){
        p++;
        sum+=a[p];
        ans[mx]++;
    }
    for(int i=0;i<n;i++)if(i!=mx){
        c+=a[i];
        if(i>mx){
            ans[i]=i;
        }else if(pll(c,-i)>pll(a[mx],-mx)){
            ans[i]=i;
        }else{
            ans[i]=i+1;
        }
    }
    for(auto x:ans)cout << x << " ";
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}