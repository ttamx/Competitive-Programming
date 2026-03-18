#include<bits/stdc++.h>

using namespace std;

const int MOD=1e9+7;
const int INF=INT_MAX/2;

using ll = long long;

struct Info{
    int val;
    ll ways;
    void update(const Info &o){
        if(o.val<val){
            val=o.val;
            ways=o.ways;
        }else if(o.val==val){
            ways=(ways+o.ways)%MOD;
        }
    }
};

void runcase(){
    string s,t;
    cin >> s >> t;
    int n=s.size();
    int m=t.size();
    vector<bool> f(n);
    bool ok=false;
    for(int i=0;i+m<=n;i++){
        if(s.substr(i,m)==t){
            f[i]=true;
            ok=true;
        }
    }
    if(!ok){
        cout << 0 << " " << 1 << "\n";
        return;
    }
    vector<ll> fac(n+1);
    fac[0]=1;
    for(int i=1;i<=n;i++){
        fac[i]=fac[i-1]*i%MOD;
    }
    vector<Info> dp(n+1,Info{INF,1});
    dp[0]={0,1};
    for(int i=m;i<=n;i++){
        if(f[i-m]){
            dp[i]={INF,1};
            for(int j=i-m;j>=0;j--){
                if(j+m<=i-m&&f[j])break;
                Info cur=dp[j];
                cur.val++;
                dp[i].update(cur);
            }
        }
    }
    Info ans={INF,1};
    for(int i=n;i>=m;i--){
        if(f[i-m]){
            ans.update(dp[i]);
        }
        if(f[i-1])break;
    }
    cout << ans.val << " " << ans.ways << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}