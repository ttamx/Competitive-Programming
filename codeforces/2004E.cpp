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

const int N=1e7+5;;

int lp[N];
vector<int> prime;
int nimber[N];

void runcase(){
    int n;
    cin >> n;
    int ans=0;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        ans^=nimber[x];
    }
    cout << (ans?"Alice":"Bob") << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    lp[1]=1;
    for(int i=2;i<N;i++){
        if(!lp[i]){
            lp[i]=i;
            prime.emplace_back(i);
        }
        for(int j=0;i*prime[j]<N;j++){
            lp[i*prime[j]]=prime[j];
            if(prime[j]==lp[i])break;
        }
    }
    int cnt=0;
    for(int i=1;i<N;i+=2){
        if(lp[i]==i){
            nimber[i]=++cnt;
        }else{
            nimber[i]=nimber[lp[i]];
        }
    }
    int t(1);
    cin >> t;
    while(t--)runcase();
}