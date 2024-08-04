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

struct Sieve{
    int n;
    vector<int> primes;
    vector<bool> not_prime;
    Sieve(int _n):n(_n),not_prime(n+1){
        not_prime[0]=not_prime[1]=true;
        for(int i=2;i<=n;i++)if(!not_prime[i]){
            primes.emplace_back(i);
            for(int j=i+i;j<=n;j+=i)not_prime[j]=true;
        }
    }
}sieve(1e6);

void runcase(){
    int n;
    cin >> n;
    if(n==2)return void(cout << "1 1\n");
    int k=0;
    vector<pair<int,int>> edge;
    auto calc=[&](int k){
        if(k&1)return k*(k+1)/2;
        else return k*k/2+1;
    };
    while(calc(k)<n-1)k++;
    for(int i=0;i<k;i++){
        edge.emplace_back(i,i);
        if(k%2==1){
            for(int j=i+1;j<k;j++)edge.emplace_back(i,j);
        }else{
            if(i%2==1)edge.emplace_back(i-1,i);
            for(int j=i+2;j<k;j++)edge.emplace_back(i,j);
        }
    }
    int m=edge.size();
    vector<vector<pair<int,int>>> adj(k);
    vector<bool> used(m);
    for(int i=0;i<m;i++){
        auto [u,v]=edge[i];
        adj[u].emplace_back(v,i);
        adj[v].emplace_back(u,i);
    }
    vector<int> ans;
    vector<int> id(k);
    function<void(int)> dfs=[&](int u){
        for(int &i=id[u];i<adj[u].size();i++){
            auto [v,j]=adj[u][i];
            if(!used[j]){
                used[j]=true;
                dfs(v);
            }
        }
        ans.emplace_back(u);
    };
    dfs(0);
    ans.resize(n);
    for(auto x:ans)cout << sieve.primes[x] << " ";
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}