#include<bits/stdc++.h>

using namespace std;

const int N=1e6+5;

int n,k,p;
int a[N],cnt[2*N];
long long ans;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        if(a[i]==k)p=i;
    }
    for(int i=p,lo=0,hi=0;i>=1;i--){
        if(a[i]<k)lo++;
        if(a[i]>k)hi++;
        cnt[hi-lo+N]++;
    }
    for(int i=p,lo=0,hi=0;i<=n;i++){
        if(a[i]<k)lo++;
        if(a[i]>k)hi++;
        ans+=cnt[lo-hi+N];
    }
    cout << ans;
}