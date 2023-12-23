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
const int MOD=1000000007;
// const int MOD=998224353;
const ll LINF=0x1fffffffffffffff;
const db DINF=numeric_limits<db>::infinity();
const db EPS=1e-9;
const db PI=acos(db(-1));

struct trie{
    int n;
    vl cnt;
    vector<array<int,26>> adj;
    trie():adj(1),n(1){}
    void insert(const string &s){
        int u=0;
        for(auto x:s){
            if(!adj[u][x-'a']){
                adj[u][x-'a']=n++;
                adj.resize(n);
                cnt.resize(n);
            }
            u=adj[u][x-'a'];
            cnt[u]++;
        }
    }
    ll query(const string &s){
        int u=0;
        ll res=0,sz=0;
        for(auto x:s){
            if(!adj[u][x-'a'])break;
            u=adj[u][x-'a'];
            res+=cnt[u];
        }
        return res;
    }
}t;

const int N=1e6+5;

int n;
string s[N];
ll ans;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> s[i];
        ans+=2ll*sz(s[i])*n;
        auto s2=s[i];
        reverse(s2.begin(),s2.end());
        t.insert(s2);
    }
    for(int i=1;i<=n;i++)ans-=2*t.query(s[i]);
    cout << ans << "\n";
}