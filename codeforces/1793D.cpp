#include<bits/stdc++.h>

using namespace std;

void runcase(){
    long long n;
    cin >> n;
    vector<long long> l(n+1),r(n+1);
    for(long long i=1;i<=n;i++){
        long long x;
        cin >> x;
        l[x]=i;
    }
    for(long long i=1;i<=n;i++){
        long long x;
        cin >> x;
        r[x]=i;
    }
    for(long long i=1;i<=n;i++)if(l[i]>r[i])swap(l[i],r[i]);
    long long a=l[1],b=r[1];
    long long ans=1;
    ans+=((a-1)*a/2)+((b-a-1)*(b-a)/2)+((n-b)*(n-b+1)/2);
    for(long long i=2;i<=n;i++){
        if(r[i]<a)ans+=(a-r[i])*(n-b+1);
        else if(l[i]>b)ans+=a*(l[i]-b);
        else if(l[i]<a&&b<r[i])ans+=(a-l[i])*(r[i]-b);
        a=min(a,l[i]);
        b=max(b,r[i]);
    }
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}