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
    ll n;
    cin >> n;
    if(n<=10)return void(cout << n-1);
    n--;
    ll cur=9;
    ll tot=0;
    while(true){
        if(n<=cur*2){
            if(n<=cur){
                string s=to_string(n+tot);
                cout << s;
                s.pop_back();
                reverse(s.begin(),s.end());
                cout << s;
            }else{
                n-=cur;
                string s=to_string(n+tot);
                cout << s;
                reverse(s.begin(),s.end());
                cout << s;
            }
            return;
        }else{
            tot+=cur;
            n-=cur*2;
            cur*=10;
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}