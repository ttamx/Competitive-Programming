#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e5+5;
const int Q=2005;

int n,m,q;
int a[N];
int qr[Q];
int pre[N],suf[N];
ll sum[N],cnt[N];
ll ans[N];

void dnc(int l,int r,vector<pair<int,int>> p){
    if(l==r)return;
    int m=(l+r)/2;
    for()
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
    }
    cin >> m;
    for(int i=0;i<m;i++){
        int l,r;
        cin >> l >> r;
        if(l>r)swap(l,r);
        pre[r+1]++;
        suf[l-1]++;
    }
    cin >> q;
    for(int i=1;i<=q;i++){
        cin >> qr[i];
    }
    for(int i=1;i<=n;i++){
        pre[i]+=pre[i-1];
    }
    for(int i=n;i>=1;i--){
        suf[i]+=suf[i+1];
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=q;j++){
            if(qr[j]>a[i]+n)break;
            if(qr[j]<=a[i])continue;
            int x=qr[j]-a[i];
            ans[j]+=(m-suf[i])*cnt[x]-sum[x];
        }
        sum[a[i]]+=pre[i];
        cnt[a[i]]++;
    }
    for(int i=1;i<=q;i++){
        cout << ans[i] << "\n";
    }
}