#include<bits/stdc++.h>

using namespace std;

void runcase(){
    vector<int> a(3);
    for(auto &x:a)cin >> x;
    sort(a.begin(),a.end());
    if((a[1]-a[0])%2==1||(a[2]-a[1])%2==1)return void(cout << -1 << '\n');
    int ans=0;
    int val=min(a[1]-a[0],a[2]-a[1]);
    ans+=val/2;
    a[0]+=val;
    a[2]-=val;
    if(a[0]!=a[1]){
        int dif=a[1]-a[0];
        if(dif%6)return void(cout << -1 << '\n');
        ans+=dif/3;
    }
    if(a[2]!=a[1]){
        int dif=a[2]-a[1];
        if(dif%6)return void(cout << -1 << '\n');
        ans+=dif/3;
    }
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}