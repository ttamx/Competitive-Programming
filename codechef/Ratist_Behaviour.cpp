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
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    string s;
    cin >> s;
    if(n==1)return void(cout << 1 << "\n");
    vector<int> good,bad;
    for(int i=0;i<n;i++)(s[i]=='0'?good:bad).emplace_back(a[i]);
    sort(good.begin(),good.end());
    sort(bad.begin(),bad.end());
    if(bad.empty())return void(cout << n << "\n");
    int ans=good.size();
    vector<pair<int,int>> b;
    for(auto x:bad){
        if(!b.empty()&&x==b.back().first)b.back().second++;
        else b.emplace_back(x,1);
    }
    for(int i=0;i<bad.size();i++){
        
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}