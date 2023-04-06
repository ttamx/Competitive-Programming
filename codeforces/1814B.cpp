#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int a,b;
    cin >> a >> b;
    int ans=2e9+10;
    if(a<b)swap(a,b);
    int tmp=-1;
    for(int r=1;r<=1e5;r++){
        int res=0;
        res+=r-1;
        res+=(b+r-1)/r;
        res+=(a+r-1)/r;
        if(res<ans)tmp=r;
        ans=min(ans,res);
    }
    ans=min(ans,b+(int)ceil(1.0*a/b));
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}