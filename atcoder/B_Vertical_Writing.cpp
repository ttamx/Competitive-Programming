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
    vector<string> a(n);
    int m=0;
    for(auto &x:a){
        cin >> x;
        m=max(m,(int)x.size());
    }
    vector<string> b(m,string(n,'*'));
    for(int i=0;i<n;i++){
        for(int j=0;j<(int)a[i].size();j++){
            b[j][n-i-1]=a[i][j];
        }
    }
    for(auto &x:b){
        while(x.back()=='*')x.pop_back();
        cout << x << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}