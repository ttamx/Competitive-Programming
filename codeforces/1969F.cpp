#include<bits/stdc++.h>

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
    int n,k;
    cin >> n >> k;
    vector<int> a(n),cnt(k);
    for(auto &x:a){
        cin >> x;
        x--;
        cnt[x]++;
    }
    int tot=0;
    for(auto x:cnt)tot+=x/2;
    int ans=tot;
    int m=n/2;
    vector<uint64_t> hsh(k),pref(m);
    for(auto &x:hsh)x=rng();
    for(int i=0;i<m;i++)pref[i]=hsh[a[i*2]]^hsh[a[i*2+1]];
    for(int i=1;i<m;i++)pref[i]^=pref[i-1];
    vector<int> dp(m+1,INF);
    dp[0]=0;
    uint64_t all=0;
    for(auto x:hsh)all^=x;
    int st=0;
    while(st<m&&all!=0){
        all^=hsh[a[st*2]]^hsh[a[st*2+1]];
        st++;
    }
    st--;
    dp[st]=0;
    for(int i=0;i<st;i++){
        cnt[a[i*2]]--;
        cnt[a[i*2+1]]--;
    }
    for(int i=st;i<m;i++){
        cnt[a[i*2]]--;
        cnt[a[i*2+1]]--;
        unordered_map<uint64_t,int> nxt;
        for(int j=m-1;j>i;j--){
            nxt[pref[i]^pref[j]]=j;
        }
        for(int x=0;x<k;x++){
            for(int y=0;y<x;y++){
                uint64_t mask=hsh[x]^hsh[y];
                int val=0;
                if(cnt[x]%2==1)val++;
                if(cnt[y]%2==1)val++;
                if(nxt.count(mask)){
                    int j=nxt[mask];
                    dp[j]=min(dp[j],dp[i]+val);
                }else{
                    ans=min(ans,dp[i]+val);
                }
            }
        }
    }
    cout << tot-ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}