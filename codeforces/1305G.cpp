#include<bits/stdc++.h>

using namespace std;

using P = pair<int,int>;

const int N=2e5+5;
const int B=18;
const int S=1<<B;

int n;
int a[N];
int fa[N];
P dp[S][2];
P link[N];
long long ans=0;

void upd(int i,P v){
    if(dp[i][0].second==v.second){
        dp[i][0]=max(dp[i][0],v);
    }else{
        dp[i][1]=max(dp[i][1],v);
        if(dp[i][1]>dp[i][0])swap(dp[i][0],dp[i][1]);
    }
}

int fp(int u){
    return fa[u]=u==fa[u]?u:fp(fa[u]);
}

bool uni(int u,int v){
    u=fp(u),v=fp(v);
    if(u==v)return false;
    fa[u]=v;
    return true;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> a[i];
        ans-=a[i];
    }
    n++;
    iota(fa,fa+n,0);
    int comp=n;
    while(comp>1){
        for(int i=0;i<S;i++){
            for(int j=0;j<2;j++){
                dp[i][j]={-1,-1};
            }
        }
        for(int i=0;i<n;i++){
            link[i]={-1,-1};
            upd(a[i],{a[i],fp(i)});
        }
        for(int i=0;i<B;i++){
            for(int mask=0;mask<S;mask++){
                if(mask>>i&1){
                    for(int j=0;j<2;j++){
                        upd(mask,dp[mask^(1<<i)][j]);
                    }
                }
            }
        }
        for(int i=0;i<n;i++){
            int mask=((1<<B)-1)^a[i];
            int p=fp(i);
            for(int j=0;j<2;j++){
                auto [val,idx]=dp[mask][j];
                if(idx!=p){
                    link[p]=max(link[p],{val+a[i],idx});
                    break;
                }
            }
        }
        for(int i=0;i<n;i++){
            if(link[i].second!=-1&&uni(i,link[i].second)){
                ans+=link[i].first;
                comp--;
            }
        }
    }
    cout << ans << "\n";
}