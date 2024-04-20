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

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    ll a,b;
    cin >> a >> b;
    ll t=min(a/7,b/5);
    a-=7*t,b-=5*t;
    string s="wbwbwwbwbwbwwbwwbwbwwbwbwbwwbw";
    for(int i=0;i<24;i++){
        for(int j=0;j<24;j++){
            string t=s.substr(i,j);
            int x=0,y=0;
            for(auto c:t){
                if(c=='w')x++;
                else y++;
            }
            if(x==a&&y==b)cout << "Yes",exit(0);
        }
    }
    cout << "No";
}