#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,q,c;
    cin >> n >> q >> c;
    vector<int> a(n+2),pre(n+2),ans(n+2);
    for(int i=1;i<=n;i++){
        cin >> a[i];
        ans[i]=max(a[i],1);
        pre[i]=max(pre[i-1],ans[i]);
    }
    vector<int> con(n+2,n+1);
    vector<pair<int,int>> qr(q);
    for(auto &[l,r]:qr){
        cin >> l >> r;
        con[r]=min(con[r],l);
    }
    for(int i=1,p=1,id=0,mx=0;i<=n;i++){
        if(con[i]<=n){
            while(p<=con[i]){
                if(!a[p])id=p;
                p++;
            }
            int mxl=max(mx,pre[con[i]]);
            int mxr=max(mx,pre[i-1]);
            if(mxl<mxr){
                ans[id]=mxl=mxr;
                mx=max(mx,mxr);
            }
            ans[i]=max(ans[i],mxl+1);
        }
        pre[i]=max(pre[i-1],ans[i]);
    }
    for(int i=1;i<=n;i++){
        if(!ans[i])ans[i]=1;
        if(ans[i]>c||(a[i]&&a[i]!=ans[i]))return void(cout << "-1\n");
        pre[i]=max(pre[i-1],ans[i]);
    }
    for(auto [l,r]:qr)if(pre[l]<pre[r-1]||ans[r]<=pre[l])return void(cout << "-1\n");
    for(int i=1;i<=n;i++)cout << ans[i] << " \n"[i==n];
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}