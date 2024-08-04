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
    string s;
    cin >> s;
    for(int i=1;i<s.size();i++){
        if(s[i]==s[i-1]){
            if(s[i]=='a'){
                cout << s.substr(0,i) << 'b' << s.substr(i,s.size()) << "\n";
            }else{
                cout << s.substr(0,i) << 'a' << s.substr(i,s.size()) << "\n";
            }
            return;
        }
    }
    if(s.back()=='a')s+="b";
    else s+="a";
    cout << s << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}