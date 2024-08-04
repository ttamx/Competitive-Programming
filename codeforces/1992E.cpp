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
    if(n==1){
        cout << 9999 << "\n";
        for(int i=2;i<=10000;i++)cout << i << " " << i-1 << "\n";
    }else{
        string s="";
        vector<pair<int,int>> ans;
        for(int a=1;a<=10000;a++){
            s+=to_string(n);
            int m=s.size();
            for(int b=max(1,m-10);b<=min({10000,a*n,m-1});b++){
                if(to_string(n*a-b)==s.substr(0,m-b)){
                    ans.emplace_back(a,b);
                }
            }
        }
        cout << ans.size() << "\n";
        for(auto [a,b]:ans)cout << a << " " << b << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}