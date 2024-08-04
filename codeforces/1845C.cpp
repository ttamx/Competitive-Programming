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
    int n=s.size();
    int m;
    cin >> m;
    string l,r;
    cin >> l >> r;
    int cur=0;
    vector<int> id(10);
    for(int i=0;i<m;i++){
        int mx=cur;
        for(int j=l[i]-'0';j<=r[i]-'0';j++){
            id[j]=max(id[j],cur);
            while(id[j]<n&&s[id[j]]!=('0'+j))id[j]++;
            mx=max(mx,id[j]);
        }
        if(mx==n)return void(cout << "YES\n");
        cur=mx+1;
    }
    cout << "NO\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}