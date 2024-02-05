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
    int n,k,m;
    cin >> n >> k >> m;
    string s;
    cin >> s;
    for(int i=0;i<k;i++){
        int st='a'+i;
        int id=0;
        while(id<m&&s[id]!=st)id++;
        if(id>=m){
            cout << "NO\n";
            cout << string(n,st) << "\n";
            return;
        }
        vi cnt(k);
        int uniq=0;
        string res(1,st);
        for(int j=id+1;j<m&&sz(res)<n;j++){
            if(cnt[s[j]-'a']++==0)uniq++;
            if(uniq==k){
                res.push_back(s[j]);
                cnt=vi(k);
                uniq=0;
            }
        }
        if(sz(res)<n){
            int k=0;
            while(cnt[k])k++;
            cout << "NO\n";
            cout << res+string(n-sz(res),'a'+k) << "\n";
            return;
        }
    }
    cout << "YES\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}