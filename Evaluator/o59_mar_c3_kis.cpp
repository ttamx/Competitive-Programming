#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const ll LIM = (1LL<<62)+1;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    ll k;
    cin >> n >> m >> k;
    vector<int> a(n),pos(n);
    for(int i=0;i<n;i++){
        cin >> a[i];
        pos[a[i]]=i;
    }
    vector<vector<ll>> dp(n,vector<ll>(m+1));
    ll ways=0;
    for(int i=n-1;i>=0;i--){
        dp[i][0]=1;
        for(int j=i+1;j<n;j++){
            for(int x=0;x<=m;x++){
                if(a[i]<a[j]){
                    dp[i][x]=min(dp[i][x]+dp[j][x],LIM);
                }else if(x>0){
                    dp[i][x]=min(dp[i][x]+dp[j][x-1],LIM);
                }
            }
        }
        for(auto x:dp[i]){
            ways=min(ways+x,LIM);
        }
    }
    if(k>=ways){
        cout << -1;
        exit(0);
    }
    vector<int> ans;
    int last=-1,cnt=0;
    k++;
    for(int t=0;t<n;t++){
        if(k==0){
            break;
        }
        k--;
        for(int i=0;i<n;i++){
            if(pos[i]<=last){
                continue;
            }
            int rem=m-cnt;
            if(!ans.empty()&&ans.back()>i){
                rem--;
            }
            if(rem<0){
                continue;
            }
            ll tot=0;
            for(int j=0;j<=rem;j++){
                tot=min(tot+dp[pos[i]][j],LIM);
            }
            if(k>=tot){
                k-=tot;
            }else{
                if(!ans.empty()&&ans.back()>i){
                    cnt++;
                }
                ans.emplace_back(i);
                last=pos[i];
                break;
            }
        }
    }
    for(auto x:ans){
        cout << x << " ";
    }
}