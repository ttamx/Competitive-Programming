#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,k;
    cin >> n >> k;
    vector<int> a(n+1);
    int cnt=0;
    for(int i=1;i<=n;++i)cin >> a[i];
    vector<int> req;
    for(int i=1;i<=n;){
        int sum=0;
        while(i<=n&&a[i]<0)sum+=1-a[i],i++;
        if(sum)req.push_back(sum);
        if(i>n)break;
        cnt++;
        while(i<=n&&a[i]>0)i++;
    }
    sort(req.begin(),req.end());
    int ans=0;
    for(int i=0;i<cnt-k;i++)ans+=req[i];
    cout << ans;
}