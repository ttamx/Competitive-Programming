#include<bits/stdc++.h>

using namespace std;

const int INF=INT_MAX/2;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<int> mn(n,INF),mx(n,-INF);
    for(int i=0;i<m;i++){
        int x;
        cin >> x;
        x--;
        mn[x]=min(mn[x],i);
        mx[x]=max(mx[x],i);
    }
    int ans=0;
    for(int i=0;i<n;i++){
        if(mx[i]<0)ans++;
    }
    for(int i=0;i+1<n;i++){
        if(mx[i]<=mn[i+1])ans++;
    }
    for(int i=1;i<n;i++){
        if(mx[i]<=mn[i-1])ans++;
    }
    cout << ans << "\n";
}