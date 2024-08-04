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
    vector<int> prime;
    vector<bool> is_prime;
    Sieve(int _n):n(_n),is_prime(n+1,true){
        is_prime[0]=is_prime[1]=false;
        for(int i=2;i<=n;i++){
            if(is_prime[i])prime.push_back(i);
            for(auto p:prime){
                if(i*p>n)break;
                is_prime[i*p]=false;
                if(i%p==0)break;
            }
        }
    }
    bool check(int x){
        if(x<=n)return is_prime[x];
        for(auto p:prime){
            if(p*p>x)break;
            if(x%p==0)return false;
        }
        return true;
    }
}sieve(1000000);

void runcase(){
    int x;
    cin >> x;
    while(!sieve.check(x))x++;
    ll ans=x;
    x++;
    while(!sieve.check(x))x++;
    ans*=x;
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}