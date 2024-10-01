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
const int MOD=998244353;
const ll LINF=0x1fffffffffffffff;
const db DINF=numeric_limits<db>::infinity();
const db EPS=1e-9;
const db PI=acos(db(-1));

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    string s,t;
    cin >> s >> t;
    int n=s.size(),m=t.size();
    for(int w=1;w<n;w++){
        vector<string> a(n);
        for(int i=0;i<n;i++)a[i%w].push_back(s[i]);
        for(auto x:a)if(x==t)cout << "Yes",exit(0);
    }
    cout << "No";
}