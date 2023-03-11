#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<int> a(n),cnt(m+1);
    for(auto &x:a)cin >> x;
    sort(a.begin(),a.end());
    int ans=2e9,l=0,r=0;
    for(int i=0;i<n;i++,r++){
        bool ok=true;
        for(int j=m/2+1;j<=m;j++){
            if(a[i]%j==0)cnt[j]++;
            if(cnt[j]==0)ok=false;
        }
        while(ok){
            ans=min(ans,a[r]-a[l]);
            for(int j=m/2+1;j<=m;j++){
                if(a[l]%j==0)cnt[j]--;
                if(cnt[j]==0)ok=false;
            }
            l++;
        }
    }
    if(ans==2e9)ans=-1;
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}