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
    if(n==2){
        cout << "1 1\n";
        cout << "1 2\n";
        cout << "\n";
        return;
    }
    if(n==3){
        cout << "2 1\n";
        cout << "2 3\n";
        cout << "3 1\n";
        cout << "\n";
        return;
    }
    cout << "1 1\n";
    cout << "1 2\n";
    cout << "3 1\n";
    cout << n << " " << n << "\n";
    for(int i=0;i<n-4;i++)cout << i+4 << " " << 1 << "\n";
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}