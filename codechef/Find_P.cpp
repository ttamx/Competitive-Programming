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
    ll n,l,r;
    cin >> n >> l >> r;
    if(l==1){
        for(int i=n;i>=1;i--)cout << i << " \n"[i==1];
        return;
    }
    if(r==n*(n+1)/2){
        for(int i=1;i<=n;i++)cout << i << " \n"[i==n];
        return;
    }
    ll s=r-l+1;
    vector<int> ans,suf;
    ll cur=0;
    int num=n;
    while(cur<=s){
        cur+=num;
        suf.emplace_back(num);
        num--;
    }
    ll tar=r+1-cur;
    for(;num>0;num--){
        if(tar>=num){
            tar-=num;
            ans.emplace_back(num);
        }else{
            suf.emplace_back(num);
        }
    }
    for(auto x:suf)ans.emplace_back(x);
    for(auto x:ans)cout << x << " ";
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}