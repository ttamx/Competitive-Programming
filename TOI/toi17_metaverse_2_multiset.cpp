#include<bits/stdc++.h>

using namespace std;

const int N=2e4+5;

int m,n,k,p;
int Wr[N],Wc[N],Or[N],Oc[N],dp[2][N];
vector<int> vr;
vector<int> W[N<<1],O[N<<1];
multiset<pair<int,int>> ms[2];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> m >> n >> k >> p;
    int ans1=m+n-2,ans2=0;
    for(int i=1;i<=k;i++){
        cin >> Wr[i] >> Wc[i] >> Or[i] >> Oc[i];
        vr.emplace_back(Wr[i]);
        vr.emplace_back(Or[i]);
        for(int j=0;j<=1;j++)dp[j][i]=Wr[i]+Wc[i]-2;
        if(dp[1][i]+m+n-Or[i]-Oc[i]<ans1)ans1=dp[1][i]+m+n-Or[i]-Oc[i],ans2=1;
    }
    sort(vr.begin(),vr.end());
    vr.erase(unique(vr.begin(),vr.end()),vr.end());
    int sr=vr.size();
    for(int i=1;i<=k;i++){
        W[lower_bound(vr.begin(),vr.end(),Wr[i])-vr.begin()+1].emplace_back(i);
        O[lower_bound(vr.begin(),vr.end(),Or[i])-vr.begin()+1].emplace_back(i);
    }
    for(int i=2;i<=p;i++){
        ms[0].clear();
        ms[1].clear();
        ms[0].emplace(0,2e9);
        ms[1].emplace(n+1,2e9);
        for(int l=1;l<=sr;l++){
            for(auto j:O[l]){
                int val=dp[i&1^1][j]-Or[j]-Oc[j];
                if(val<prev(ms[0].lower_bound({Oc[j]+1,-2e9}))->second){
                    auto it=ms[0].emplace(Oc[j],val);
                    while(next(it)!=ms[0].end()&&next(it)->second>=val)ms[0].erase(next(it));
                }
                val=dp[i&1^1][j]-Or[j]+Oc[j];
                if(val<ms[1].lower_bound({Oc[j],-2e9})->second){
                    auto it=ms[1].emplace(Oc[j],val);
                    while(next(it)!=ms[1].end()&&next(it)->first==Oc[j])ms[1].erase(next(it));
                    while(it!=ms[1].begin()&&prev(it)->second>=val)ms[1].erase(prev(it));
                }
            }
            for(auto j:W[l]){
                int x=prev(ms[0].lower_bound({Wc[j]+1,-2e9}))->second+Wr[j]+Wc[j];
                int y=ms[1].lower_bound({Wc[j],-2e9})->second+Wr[j]-Wc[j];
                dp[i&1][j]=min({dp[i&1][j],x,y});
            }
        }
        ms[0].clear();
        ms[1].clear();
        ms[0].emplace(0,2e9);
        ms[1].emplace(n+1,2e9);
        for(int l=sr;l>=1;l--){
            for(auto j:O[l]){
                int val=dp[i&1^1][j]+Or[j]-Oc[j];
                if(val<prev(ms[0].lower_bound({Oc[j]+1,-2e9}))->second){
                    auto it=ms[0].emplace(Oc[j],val);
                    while(next(it)!=ms[0].end()&&next(it)->second>=val)ms[0].erase(next(it));
                }
                val=dp[i&1^1][j]+Or[j]+Oc[j];
                if(val<ms[1].lower_bound({Oc[j],-2e9})->second){
                    auto it=ms[1].emplace(Oc[j],val);
                    while(next(it)!=ms[1].end()&&next(it)->first==Oc[j])ms[1].erase(next(it));
                    while(it!=ms[1].begin()&&prev(it)->second>=val)ms[1].erase(prev(it));
                }
            }
            for(auto j:W[l]){
                int x=prev(ms[0].lower_bound({Wc[j]+1,-2e9}))->second-Wr[j]+Wc[j];
                int y=ms[1].lower_bound({Wc[j],-2e9})->second-Wr[j]-Wc[j];
                dp[i&1][j]=min({dp[i&1][j],x,y});
            }
        }
        for(int j=1;j<=k;j++)if(dp[i&1][j]+m+n-Or[j]-Oc[j]<ans1)ans1=dp[i&1][j]+m+n-Or[j]-Oc[j],ans2=i;
    }
    cout << ans1 << ' ' << ans2;
}