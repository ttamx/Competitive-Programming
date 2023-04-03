#include<bits/stdc++.h>

using namespace std;

const int N=3e5+5;
const int M=20;

int n,m;
int a[N][M],all[M],cur[M];
bool req[M];
int mx[1<<M][2];
vector<int> vec[1<<M];
pair<int,int> dp[1<<M];
vector<int> b[M+1];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=0;i<1<<m;i++)b[__builtin_popcount(i)].emplace_back(i);
    for(int i=1;i<=n;i++){
        int cnt=0,hsh=0;
        for(int j=0;j<m;j++){
            cin >> a[i][j];
            all[j]+=a[i][j];
            hsh+=((a[i][j]^1)<<j);
            cnt+=a[i][j];
        }
        cnt=m-cnt;
        cerr << i << " : " << bitset<12>(hsh) << "\n";
        if(cnt>dp[hsh].first){
            dp[hsh].second=dp[hsh].first;
            dp[hsh].first=cnt;
        }else{
            dp[hsh].second=max(dp[hsh].second,cnt);
        }
    }
    for(int i=m;i>0;i--){
        for(auto j:b[i]){
            if(dp[j].first==0)continue;
            for(int k=0;k<m;k++){
                if(((j>>k)&1)==0)continue;
                int res=dp[j].first-((j>>k)&1);
                int idx=j^(1<<k);
                if(res>dp[idx].first){
                    dp[idx].second=max(dp[idx].first,dp[j].second);
                    dp[idx].first=res;
                }else{
                    dp[idx].second=max(dp[idx].second,res);
                }
            }
        }
    }
    for(int i=0;i<m;i++){
        for(auto j:b[i]){
            if(dp[j].first==0)continue;
            for(int k=0;k<m;k++){
                if(((j>>k)&1)==1)continue;
                int res=dp[j].first;
                int idx=j^(1<<k);
                if(res>dp[idx].first){
                    dp[idx].second=max(dp[idx].first,dp[j].second);
                    dp[idx].first=res;
                }else{
                    dp[idx].second=max(dp[idx].second,res);
                }
            }
        }
    }
    for(int i=0;i<1<<m;i++){
        cerr << bitset<12>(i) << " " << dp[i].first << '\n';
    }
    for(int i=1;i<=n;i++){
        int ans=0,hsh=0;
        for(int j=0;j<m;j++){
            cur[j]=all[j]-a[i][j];
            if(cur[j]>n/2)ans++;
            req[j]=(cur[j]==n/2);
            hsh+=(req[j]<<j);
        }
        int sum=0;
        for(int k=0;k<m;k++)if(req[k]&&a[i][k]==0)sum++;
        cerr << i << " : " << sum << " " << bitset<12>(hsh) << " -> " << dp[hsh].first << " " << dp[hsh].second << '\n';
        int res=dp[hsh].first;
        if(res==sum)res=dp[hsh].second;
        cout << ans+res << '\n';
    }
}