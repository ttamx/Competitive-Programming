#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=5e5+5;
const int M=2*N;
const ll MOD=1e9+7;
const ll INV=5e8+4;

int n,m;
ll a[N],b[N];
ll vals[2*N];
ll pw[N]; 
ll ans;

int cl[M],cr[M];
ll dpl[M],dpr[M];

ll getl(int i){
    return cl[i]?0LL:dpl[i];
}

ll getr(int i){
    return cr[i]?0LL:dpr[i];
}

void process(){
    for(int i=1;i<=n;i++)dpl[i]=dpr[i]=1;
    for(int i=n;i>=1;i--){
        for(int j=1;j<a[i];j++)cr[j]++;
        for(int j=b[i];j<=m;j++)dpr[j]=(dpr[j]*2LL)%MOD;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<a[i];j++)cr[j]--;
        for(int j=b[i];j<=m;j++)dpr[j]=(dpr[j]*INV)%MOD;
        for(int j=a[i]+1;j<=m;j++){
            ans+=(vals[j]-vals[a[i]])*(MOD+getl(j)-getl(j-1))%MOD*(MOD+pw[n-i]-getr(j))%MOD;
            ans+=(vals[j]-vals[a[i]])*(MOD+getr(j)-getr(j-1))%MOD*(MOD+pw[i-1]-getl(j-1))%MOD;
            ans%=MOD;
        }
        for(int j=b[i]+1;j<=m;j++){
            ans+=(vals[j]-vals[b[i]])*(MOD+getl(j)-getl(j-1))%MOD*(MOD+pw[n-i]-getr(j))%MOD;
            ans+=(vals[j]-vals[b[i]])*(MOD+getr(j)-getr(j-1))%MOD*(MOD+pw[i-1]-getl(j-1))%MOD;
            ans%=MOD;
        }
        for(int j=1;j<a[i];j++)cl[j]++;
        for(int j=b[i];j<=m;j++)dpl[j]=(dpl[j]*2LL)%MOD;
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<=n;i++)cin >> b[i];
    for(int i=1;i<=n;i++){
        if(a[i]>b[i])swap(a[i],b[i]);
        vals[i*2-1]=a[i],vals[i*2]=b[i];
    }
    sort(vals+1,vals+2*n+1);
    m=unique(vals+1,vals+2*n+1)-vals-1;
    for(int i=1;i<=n;i++){
        a[i]=lower_bound(vals+1,vals+m+1,a[i])-vals;
        b[i]=lower_bound(vals+1,vals+m+1,b[i])-vals;
    }
    pw[0]=1;
    for(int i=1;i<=n;i++)pw[i]=pw[i-1]*2LL%MOD;
    process();
    cout << ans;
}