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
    string s;
    cin >> s;
    int k=1;
    while(k*k<n)k++;
    if(k*k!=n){
        cout << "No\n";
        return;
    }
    vector<string> a(k);
    for(int i=0;i<k;i++){
        a[i]=s.substr(i*k,k);
    }
    for(int i=0;i<k;i++)if(a[0][i]!='1')return void(cout << "No\n");
    for(int i=0;i<k;i++)if(a[k-1][i]!='1')return void(cout << "No\n");
    for(int i=1;i<k-1;i++)if(a[i][0]!='1')return void(cout << "No\n");
    for(int i=1;i<k-1;i++)if(a[i][k-1]!='1')return void(cout << "No\n");
    for(int i=1;i<k-1;i++){
        for(int j=1;j<k-1;j++){
            if(a[i][j]!='0'){
                return void(cout << "No\n");
            }
        }
    }
    cout << "Yes\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}