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

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

void runcase(){
    int n;
    cin >> n;
    vector<unsigned ll> hsh(n),a(n+1);
    generate(all(hsh),rng);
    vi freq(n);
    map<unsigned ll,int> fhsh;
    vector<queue<int>> q(n);
    fhsh[0]++;
    ll ans=0;
    int pos=0;
    for(int i=1;i<=n;i++){
        int x;
        cin >> x;
        x--;
        q[x].emplace(i);
        if(q[x].size()>3){
            while(pos<q[x].front())fhsh[a[pos++]]--;
            q[x].pop();
        }
        int pre=freq[x];
        freq[x]=(freq[x]+1)%3;
        a[i]=a[i-1]+(freq[x]-pre)*hsh[x];
        ans+=fhsh[a[i]]++;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}