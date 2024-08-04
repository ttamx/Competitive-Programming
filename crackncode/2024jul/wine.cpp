#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e5+5;

int n,q;
int a[N];
int ans[N];
ll sum,psum,ssum;
map<int,int> pre,suf;
vector<pair<int,int>> qr[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        sum+=a[i];
    }
    for(int i=1;i<=q;i++){
        int x,y;
        cin >> x >> y;
        ans[i]=n-1;
        if((sum+y)%n==0)qr[x].emplace_back(i,(sum+y)/n);
    }
    for(int i=1;i<=n;i++){
        psum+=a[i];
        for(auto [j,v]:qr[i])ans[j]-=pre[v];
        if(psum%i==0)pre[psum/i]++;
    }
    for(int i=n;i>=1;i--){
        ssum+=a[i];
        for(auto [j,v]:qr[i])ans[j]-=suf[v];
        if(ssum%(n-i+1)==0)suf[ssum/(n-i+1)]++;
    }
    for(int i=1;i<=q;i++)cout << ans[i] << "\n";
}