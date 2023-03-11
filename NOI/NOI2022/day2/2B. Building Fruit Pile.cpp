#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1e5+5;

int n;
int a[N];
ll w[N],v[N];
ll dp[N],b[N];
vector<int> lv[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;++i)dp[i]=1e18,b[i]=1e18;
    for(int i=1;i<=n;++i){
        cin >> a[i];
        lv[a[i]].emplace_back(i);
    }
    for(int i=1;i<=n;++i){
        cin >> w[i];
    }
    for(int i=1;i<=n;++i){
        cin >> v[i];
    }
    for(auto i:lv[1])dp[i]=v[i];
    for(int i=1;i<=n;++i){
        int x=0,y=0;
        while(x<lv[i].size()&&y<lv[i+1].size()){
            if(lv[i][x])
        }
    }
    /*
    for(auto i:lv[1])dp[i]=v[i],b[i]=w[i];
    for(int i=2;i<=n;++i){
        ll ans=1e18;
        for(auto j:lv[i]){
            for(auto k:lv[i-1]){
                ll tmp=dp[k]+((abs(k-j)+v[j])*b[k]);
                if(tmp<dp[j]){
                    dp[j]=tmp;
                    b[j]=b[k]*w[j];
                }else if(tmp==dp[j]){
                    b[j]=min(b[j],b[k]*w[j]);
                }
            }
            ans=min(ans,dp[j]);
        }
        if(lv[i+1].empty()){
            cout << ans;
            return 0;
        }
    }
    */
}
