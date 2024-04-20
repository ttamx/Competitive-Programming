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

vector<int> manacher(string s){
    string t="#";
    for(auto c:s){
        t+=c;
        t+='#';
    }
    int n=t.size();
    vector<int> r(n);
    for(int i=0,j=0;i<n;i++){
        if(2*j-i>=0&&j+r[j]>i)r[i]=min(r[2*j-i],j+r[j]-i);
        while(i-r[i]>=0&&i+r[i]<n&&t[i-r[i]]==t[i+r[i]])r[i]++;
        if(i+r[i]>j+r[j])j=i;
    }
    return r;
}

void runcase(){
    string s;
    cin >> s;
    auto man=manacher(s);
    int n=sz(s);
    auto check=[&](int l,int r){
        return man[l+r+1]>=r-l+1;
    };
    if(!check(0,n-1)){
        cout << "YES\n";
        cout << 1 << "\n";
        cout << s << "\n";
        return;
    }
    for(int i=1;i<n;i++){
        if(!check(0,i-1)&&!check(i,n-1)){
            cout << "YES\n";
            cout << 2 << "\n";
            cout << s.substr(0,i) << " " << s.substr(i,n-i) << "\n";
            return;
        }
    }
    cout << "NO\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}