#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,t;
    cin >> n >> t;
    vector<int> a(n+1);
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    int q;
    cin >> q;
    vector<vector<pair<int,int>>> qr(n+1);
    vector<int> ans(q,-1);
    for(int i=0;i<q;i++){
        int l,r;
        cin >> l >> r;
        if(a[r]-a[l]>t&&r-l+1>2){
            qr[r].emplace_back(l,i);
        }else{
            ans[i]=min(r-l+1,2);
        }
    }
    vector<int> pre(n+1),jump(n+1),dep(n+1),pre2(n+1),jump2(n+1),dp(n+1),dep2(n+1);
    auto work=[&](int i){
        int u=pre[i];
        dep[i]=dep[u]+1;
        if(dep[u]-dep[jump[u]]==dep[jump[u]]-dep[jump[jump[u]]]){
            jump[i]=jump[jump[u]];
        }else{
            jump[i]=u;
        }
    };
    auto work2=[&](int i){
        int u=pre2[i];
        dp[i]+=dp[u];
        dep2[i]=dep2[u]+1;
        if(dep2[u]-dep2[jump2[u]]==dep2[jump2[u]]-dep2[jump2[jump2[u]]]){
            jump2[i]=jump2[jump2[u]];
        }else{
            jump2[i]=u;
        }
    };
    auto lca=[&](int u,int v){
        if(dep[u]<dep[v])swap(u,v);
        while(dep[u]>dep[v]){
            u=dep[jump[u]]>=dep[v]?jump[u]:pre[u];
        }
        while(u!=v){
            if(jump[u]!=jump[v])u=jump[u],v=jump[v];
            else u=pre[u],v=pre[v];
        }
        return u;
    };
    auto calc=[&](int i,int l){
        int u=i;
        while(true){
            if(jump[u]>=l)u=jump[u];
            else if(pre[u]>=l)u=pre[u];
            else break;
        }
        return dep[i]-dep[u]+1;
    };
    for(int i=1,j=1;i<=n;i++){
        while(j+1<=n&&a[i]-a[j+1]>t){
            j++;
        }
        if(a[i]-a[j]>t){
            pre[i]=j;
        }
        work(i);
        int x=lca(i,i-1);
        dp[i]=dep[i]+dep[i-1]-2*dep[x];
        pre2[i]=x;
        work2(i);
        for(auto [l,id]:qr[i]){
            int u=i;
            while(true){
                if(jump2[u]>=l)u=jump2[u];
                else if(pre2[u]>=l)u=pre2[u];
                else break;
            }
            ans[id]=dp[i]-dp[u];
            if(u==l)ans[id]++;
            else ans[id]+=calc(u,l)+calc(u-1,l);
        }
    }
    for(auto x:ans){
        assert(x!=-1);
        cout << x << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}