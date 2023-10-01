#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,k;
    cin >> n >> k;
    vector<int> a(n);
    int xx=0,yy=0;
    for(auto &x:a){
        cin >> x;
        xx+=(x==1);
        yy+=(x==-1);
    }
    int ans=0;
    for(int i=0;i<k;i++){
        int x=xx,y=yy;
        for(int j=i;j<n;j+=k){
            x-=(a[j]==1);
            y-=(a[j]==-1);
        }
        ans=max(ans,abs(x-y));
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}