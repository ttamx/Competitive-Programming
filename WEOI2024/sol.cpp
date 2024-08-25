#include<bits/stdc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()

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
    for(int a=1;a<=9;a++){
        for(int b=1;b<=9;b++){
            for(int c=1;c<=9;c++){
                for(int d=1;d<=9;d++){
                    set<int> s{a,b,c,d};
                    if(s.size()<4)continue;
                    if(a*b*c-d==153){
                        cout << a << " " << b << " " << c << " " << d << "\n";
                        return 0;
                    }
                }
            }
        }
    }
}