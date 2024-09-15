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
    vector<int> a(2*n+1);
    for(int i=0;i<2*n;i++){
        a[i+1]=a[i]+(s[i]=='('?1:-1);
    }
    if(*min_element(a.begin(),a.end())==0){
        cout << 0 << "\n";
        return;
    }
    int p=max_element(a.begin(),a.end())-a.begin();
    int l=0,r=2*n;
    int li=0,ri=2*n;
    while(a[l]>=0){
        l++;
        if(a[l]>=a[li]){
            li=l;
        }
    }
    while(a[r]>=0){
        r--;
        if(a[r]>=a[ri]){
            ri=r;
        }
    }
    for(int i=li+1;i<=ri;i++){
        if(a[i]>a[li]+a[ri]){
            cout << 2 << "\n";
            cout << 1 << " " << p << "\n";
            cout << p+1 << " " << 2*n << "\n";
            return;
        }
    }
    cout << 1 << "\n";
    cout << li+1 << " " << ri << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}