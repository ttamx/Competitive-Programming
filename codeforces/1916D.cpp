#include<bits/stdc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()

using namespace std;

using ll = long long;
using ull = unsigned long long;
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

vector<string> ans[100];

void runcase(){
    int n;
    cin >> n;
    for(auto x:ans[n])cout << x << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    ans[1]={"1"};
    ans[3]={"169","196","961"};
    for(int i=5;i<100;i+=2){
        ans[i]=ans[i-2];
        for(auto &x:ans[i])x+="00";
        ans[i].emplace_back("1"+string((i-3)/2,'0')+"6"+string((i-3)/2,'0')+"9");
        ans[i].emplace_back("9"+string((i-3)/2,'0')+"6"+string((i-3)/2,'0')+"1");
    }
    int t(1);
    cin >> t;
    while(t--)runcase();
}