#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

struct Info{
    int val1,val2;
    mint ways1,ways2;
    Info():val1(-INF),val2(-INF),ways1(0),ways2(0){}
    void update(int v,mint w){
        if(v==val1){
            ways1+=w;
        }else if(v==val2){
            ways2+=w;
        }else if(v>val2){
            val2=v;
            ways2=w;
            if(val2>val1){
                swap(val1,val2);
                swap(ways1,ways2);
            }
        }
    }
};

void runcase(){
    int n,q;
    cin >> n >> q;
    vector<int> a(n+2);
    vector<array<int,64>> f(n+2);
    for(int i=1;i<=n;i++){
        cin >> a[i];
        f[i][a[i]]++;
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<64;j++){
            f[i][j]+=f[i-1][j];
        }
    }
    while(q--){
        int l,r;
        cin >> l >> r;
        array<int,64> cnt;
        for(int i=0;i<64;i++){
            cnt[i]=f[r][i]-f[l-1][i];
        }
        if(cnt[0]>0){
            cout << r-l << " " << cnt[0] << "\n";
            continue;
        }
        if(*max_element(cnt.begin(),cnt.end())>=2){
            mint ans=0;
            for(int i=0;i<64;i++){
                if(cnt[i]>=2){
                    ans+=1LL*cnt[i]*(cnt[i]-1)/2;
                }
            }
            cout << r-l-1 << " " << ans << "\n";
            continue;
        }
        int cur=0;
        array<Info,64> dp;
        dp[0].update(0,1);
        for(int i=l;i<=r;i++){
            cur^=a[i];
            auto ndp=dp;
            for(int j=0;j<64;j++){
                ndp[j^a[i]].update(dp[j].val1+1,dp[j].ways1);
                ndp[j^a[i]].update(dp[j].val2+1,dp[j].ways2);
            }
            dp=move(ndp);
        }
        if(dp[cur].val2>=0){
            cout << dp[cur].val2 << " " << dp[cur].ways2 << "\n";
        }else{
            cout << -1 << "\n";
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}