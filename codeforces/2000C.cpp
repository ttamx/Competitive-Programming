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
    vector<int> a(n);
    map<int,vector<int>> pos;
    for(int i=0;i<n;i++){
        cin >> a[i];
        pos[a[i]].emplace_back(i);
    }
    int q;
    cin >> q;
    while(q--){
        string s;
        cin >> s;
        if(s.size()!=n){
            cout << "NO\n";
            continue;
        }
        map<char,vector<int>> pos2;
        for(int i=0;i<n;i++){
            pos2[s[i]].emplace_back(i);
        }
        bool ok=true;
        for(int i=0;i<n;i++){
            if(!pos2[s[i]].empty()){
                if(pos[a[i]]!=pos2[s[i]]){
                    ok=false;
                    break;
                }
                pos2[s[i]].clear();
            }
        }
        cout << (ok?"YES":"NO") << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}