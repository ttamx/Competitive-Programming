#include "template.hpp"
#include "data-structure/fenwick-tree.hpp"

void runcase(){
    int n,q;
    cin >> n >> q;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    vector<vector<pair<int,int>>> qr(n);
    vector<ll> ans(q);
    for(int i=0;i<q;i++){
        int l,r;
        cin >> l >> r;
        l--,r--;
        qr[l].emplace_back(r,i);
    }
    Fenwick<ll> f(n);
    vector<int> pos(n+1);
    for(int i=0;i<n;i++)pos[a[i]]=i;
    vector<vector<int>> pre(n);
    vector<ll> dp(n);
    for(int i=n-1;i>=0;i--){
        dp[i]=1;
        f.update(i,1);
        int x=a[i];
        vector<int> nxt;
        for(int j=x*2;j<=n;j+=x){
            int k=pos[j];
            if(k>i){
                pre[k].emplace_back(i);
                nxt.emplace_back(k);
            }
        }
        sort(nxt.begin(),nxt.end());
        for(auto j:nxt){
            f.update(j,-dp[j]);
            dp[j]=1;
            for(auto p:pre[j]){
                dp[j]+=dp[p];
            }
            f.update(j,dp[j]);
        }
        for(auto [j,id]:qr[i]){
            ans[id]=f.query(i,j);
        }
    }
    for(int i=0;i<q;i++)cout << ans[i] << " \n"[i==q-1];
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}