#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;
const int K=2e5+5;
const int inf=1e9;

int n,q,k;
int a[N],s[N],d[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;i++)cin >> a[i];
    sort(a+1,a+n+1);
    a[0]=-1,a[n+1]=inf;
    while(q--){
        cin >> k;
        for(int i=1;i<=k;i++)cin >> s[i];
        sort(s+1,s+k+1);
        int ans=0,mx=-inf;
        auto upd=[&](int x){
            ans=max(ans,mx+x);
            mx=max(mx,x);
        };
        if(a[1]<s[1])upd(s[1]-a[1]);
        if(a[n]>s[k])upd(a[n]-s[k]);
        int idx=1;
        while(idx<=n&&a[idx]<s[1])idx++;
        for(int i=2;i<=k;i++){
            int mid=(s[i]+s[i-1])/2;
            auto it=upper_bound(a+1,a+n+1,mid);
            int r=*it;
            int l=*(--it);
            int res=-1;
            if(l>s[i-1])res=max(res,l-s[i-1]);
            if(r<s[i])res=max(res,s[i]-r);
            if(res>=0)upd(res);
            int st=idx;
            while(idx<=n&&a[idx]<=s[i])idx++;
            int ed=idx-1;
            for(int l=st,r=st;r<=ed;r++){
                while((a[r]-a[l])*2>s[i]-s[i-1])l++;
                ans=max(ans,a[r]-a[l]);
            }
            for(int l=st,r=st;r<=ed;r++){
                while(l<r&&(a[r]-a[l+1])*2>=s[i]-s[i-1])l++;
                if((a[r]-a[l])*2>=s[i]-s[i-1])ans=max(ans,s[i]-s[i-1]-a[r]+a[l]);
            }
        }
        cout << ans << "\n";
    }
}