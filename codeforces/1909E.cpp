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

const int N=19;

vector<pii> masks[5];

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<vi> adj(n);
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
    }
    if(n<5)return void(cout << "-1\n");
    if(n>=20){
        cout << n << "\n";
        for(int i=1;i<=n;i++)cout << i << " \n"[i==n];
        return;
    }
    int c=n/5,filter=(1<<n)-1;
    for(auto [mx,mask]:masks[c]){
        if(mx>=n)break;
        mask&=filter;
        bool ok=true;
        for(int i=0;i<n&&ok;i++)if(mask>>i&1){
            for(auto j:adj[i])if(!(mask>>j&1)){
                ok=false;
                break;
            }
        }
        if(ok){
            cout << __builtin_popcount(mask) << "\n";
            for(int i=0;i<n;i++)if(mask>>i&1)cout << i+1 << " ";
            cout << "\n";
            return;
        }
    }
    cout << -1 << "\n";
}

int getmask(int req){
    int state=0,mask=0;
    for(int j=0;j<N;j++)if((state^req)>>j&1){
        mask|=1<<j;
        for(int k=j;k<N;k+=j+1)state^=1<<k;
    }
    return mask;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=1;i<1<<N;i++){
        int c=__builtin_popcount(i);
        if(c>3)continue;
        int l=31-__builtin_clz(i);
        masks[c].emplace_back(l,getmask(i));
    }
    for(int i=1;i<4;i++){
        for(auto &x:masks[i-1])masks[i].emplace_back(x);
        sort(all(masks[i]));
    }
    int t(1);
    cin >> t;
    while(t--)runcase();
}