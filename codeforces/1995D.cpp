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

template<class T,class U>
bool chmax(T &a,const U &b){
    return a<b?a=b,true:false;
}

template<class T,class U>
bool chmin(T &a,const U &b){
    return b<a?a=b,true:false;
}

void runcase(){
    int n,c,k;
    cin >> n >> c >> k;
    string s;
    cin >> s;
    if(n==1)return void(cout << "1\n");
    vector<int> a(n);
    for(int i=0;i<n;i++)a[i]=s[i]-'A';
    int m=1<<c;
    vector<int> dp(m,0);
    for(int x=0;x<c;x++){
        int pre=-1;
        for(int i=0;i<n;i++){
            if(a[i]!=x)continue;
            int mask=0;
            for(int j=i-1;j>pre;j--){
                int y=a[j];
                mask|=(1<<y);
                chmax(dp[mask],i-j);
            }
            pre=i;
        }
    }
    for(int i=0;i<m;i++){
        for(int j=0;j<c;j++){
            if(i>>j&1){
                chmax(dp[i],dp[i^(1<<j)]);
            }
        }
    }
    int x=a.back();
    int ans=0;
    for(int i=0;i<m;i++){
        if(!(i>>x&1)&&dp[i]<k){
            ans=max(ans,__builtin_popcount(i));
        }
    }
    cout << c-ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}