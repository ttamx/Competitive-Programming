#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,k;
    cin >> n >> k;
    vector<int> mn(k+2,n+1),mx(k+2,0),l(k+2,n+1),r(k+2,0);
    for(int i=1;i<=n;i++){
        int x;
        cin >> x;
        mn[x]=min(mn[x],i);
        mx[x]=max(mx[x],i);
    }
    for(int i=k;i>=1;i--){
        l[i]=min(mn[i],l[i+1]);
        r[i]=max(mx[i],r[i+1]);
    }
    for(int i=1;i<=k;i++){
        cout << (mn[i]<=mx[i]?(r[i]-l[i]+1)*2:0) << " \n"[i==k];
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}