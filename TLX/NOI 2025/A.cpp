#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e6+5;
const int MOD=1e9+7;

int lp[N];
vector<pair<int,int>> pos[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=2;i<N;i++){
        if(lp[i]){
            continue;
        }
        for(int j=i;j<N;j+=i){
            if(!lp[j]){
                lp[j]=i;
            }
        }
    }
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    for(int i=0;i<n;i++){
        int x=a[i];
        while(x>1){
            int p=lp[x];
            int cnt=0;
            while(x%p==0){
                cnt++;
                x/=p;
            }
            pos[p].emplace_back(i,cnt);
        }
    }
    ll ans=1;
    for(int i=2;i<N;i++){
        for(int j=0;j<pos[i].size();j++){
            int k=j;
            int st=pos[i][j].first;
            int ed=st;
            vector<int> good{pos[i][j].second};
            while(k+1<pos[i].size()&&pos[i][k+1].first==pos[i][k].first+1){
                good.emplace_back(pos[i][k+1].second);
                ed=pos[i][k+1].first;
                k++;
            }
            j=k;
            vector<ll> dp{1LL};
            if(st==0){
                for(int i=0;i<good[0];i++){
                    dp.emplace_back(1);
                }
            }
            for(auto v:good){
                vector<ll> ndp(v+1);
                for(int i=min(v,(int)dp.size()-1);i>=0;i--){
                    ndp[v]=(ndp[v]+dp[i])%MOD;
                }
                if(dp.size()>v){
                    for(int i=0;i<v;i++){
                        ndp[i]=dp[v];
                    }
                }
                dp=move(ndp);
            }
            ll mul=dp[0];
            if(ed==n-1){
                mul=accumulate(dp.begin(),dp.end(),0LL)%MOD;
            }
            ans=(ans*mul)%MOD;
        }
    }
    cout << ans << "\n";
}