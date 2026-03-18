#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    int mn=INT_MAX,mn2=INT_MAX;
    for(auto &x:a){
        cin >> x;
        mn2=min(mn2,x);
        if(mn2<mn)swap(mn,mn2);
    }
    int ans=(mn+1)/2+(mn2+1)/2;
    for(int i=0;i+1<n;i++){
        int x=a[i],y=a[i+1];
        if(x<y)swap(x,y);
        int t=min(x-y,y);
        x-=2*t,y-=t;
        if(y==0){
            ans=min(ans,t+(x+1)/2);
            continue;
        }
        int tt=x/3;
        x-=tt*3;
        ans=min(ans,t+tt*2+x);
    }
    for(int i=0;i+2<n;i++){
        int x=a[i],y=a[i+2];
        ans=min(ans,min(x,y)+(abs(x-y)+1)/2);
    }
    cout << ans << "\n";
}