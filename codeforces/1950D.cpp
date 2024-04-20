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

const int N=1e5+5;

vector<int> a;
bool dp[N];

void runcase(){
    int n;
    cin >> n;
    cout << (dp[n]?"YES":"NO") << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=1;i<N;i++){
        string s=to_string(i);
        bool ok=true;
        for(auto c:s)if(c!='0'&&c!='1'){
            ok=false;
            break;
        }
        if(!ok)continue;
        a.emplace_back(i);
        dp[i]=true;
    }
    for(int i=1;i<N;i++)if(!dp[i]){
        for(auto x:a){
            if(x>i)break;
            if(i%x)continue;
            if(dp[i/x]){
                dp[i]=true;
                break;
            }
        }
    }
    int t(1);
    cin >> t;
    while(t--)runcase();
}