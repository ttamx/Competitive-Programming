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

ofstream out("1992E.txt");

void solve(int n){
    vector<pair<int,int>> ans;
    string s="";
    for(int a=1;a<=10000;a++){
        s+=to_string(n);
        int m=s.size();
        for(int b=max(1,m-10);b<=min({10000,a*n,m-1});b++){
            if(to_string(n*a-b)==s.substr(0,m-b)){
                cerr << "FOUND " << n << " " << a << " " << b << "\n";
                ans.emplace_back(a,b);
            }
        }
    }
    if(!ans.empty()){
        out << "dp[" << n << "]={";
        for(int i=0;i<ans.size();i++){
            out << "{" << ans[i].first << "," << ans[i].second << "}";
            out << ",}"[i==ans.size()-1];
        }
        out << ";\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=2;i<=100;i++)solve(i);
}