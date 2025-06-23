#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    ll cx,cy,k;
    cin >> cx >> k >> cy;
    vector<int> a(n+2),b(m+2);
    a[0]=0,a[n+1]=1;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        a[i]++;
    }
    b[0]=0,b[m+1]=1;
    for(int i=1;i<=m;i++){
        cin >> b[i];
        b[i]++;
    }
    vector<int> pos(n+2);
    for(int i=0;i<=n+1;i++)pos[a[i]]=i;
    ll ans=0;
    for(int i=0;i<=m;i++){
        int l=pos[b[i]],r=pos[b[i+1]];
        if(r<=l)cout << -1 << "\n",exit(0);
        int mx=max(b[i],b[i+1]);
        bool f=false;
        for(int j=l+1;j<r;j++){
            if(a[j]>mx){
                f=true;
            }
        }
        int cnt=r-l-1;
        if(f){
            cnt-=k;
            ans+=cx;
            if(cnt<0)cout << -1 << "\n",exit(0);
        }
        if(cy*k>cx){
            ans+=(cnt/k)*cx;
            cnt%=k;
        }
        ans+=cnt*cy;
    }
    cout << ans << "\n";
}