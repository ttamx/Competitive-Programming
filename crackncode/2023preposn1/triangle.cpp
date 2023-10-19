#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,m;
    cin >> n >> m;
    long long ans=0;
    for(int x1=0;x1<=n;x1++)for(int x2=x1;x2<=n;x2++)for(int x3=x2;x3<=n;x3++)for(int y1=0;y1<=m;y1++)for(int y2=0;y2<=m;y2++)for(int y3=0;y3<=m;y3++){
        if(x1==x2&&y1>y2)continue;
        if(x2==x3&&y2>y3)continue;
        ans+=abs(x1*y2+x2*y3+x3*y1-y1*x2-y2*x3-y3*x1);
    }
    cout << ans;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}