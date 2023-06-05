#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n),b(n);
    for(auto &x:a)cin >> x;
    for(auto &x:b)cin >> x;
    vector<int> c1(2*n+1),c2(2*n+1);
    int cnt=1;
    c1[a[0]]=1;
    for(int i=1;i<n;i++){
        if(a[i]==a[i-1])cnt++;
        else cnt=1;
        c1[a[i]]=max(c1[a[i]],cnt);
    }
    cnt=1;
    c2[b[0]]=1;
    for(int i=1;i<n;i++){
        if(b[i]==b[i-1])cnt++;
        else cnt=1;
        c2[b[i]]=max(c2[b[i]],cnt);
    }
    int ans=1;
    for(int i=1;i<=2*n;i++)ans=max(ans,c1[i]+c2[i]);
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}