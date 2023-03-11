#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<long long> a(n+1),b(n+1),qs(n+1),t(n+2),lf(n+2);
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    for(int i=1;i<=n;i++){
        cin >> b[i];
        qs[i]=b[i]+qs[i-1];
    }
    for(int i=1;i<=n;i++){
        int idx=upper_bound(qs.begin(),qs.end(),qs[i-1]+a[i])-qs.begin()-1;
        t[i]++;
        t[idx+1]--;
        lf[idx+1]+=a[i]-qs[idx]+qs[i-1];
    }
    for(int i=1;i<=n;i++)t[i]+=t[i-1];
    for(int i=1;i<=n;i++)cout << t[i]*b[i]+lf[i] << ' ';
    cout << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}