#include<bits/stdc++.h>

using namespace std;

void runcase(){
    long long n,m,a,b,c,d;
    cin >> n >> m >> a >> b >> c >> d;
    int ans=4;
    if(a==1||a==n){
        ans=min(ans,3);
        if(b==1||b==m)ans=min(ans,2);
    }
    if(b==1||b==m)ans=min(ans,3);
    swap(a,c);
    swap(b,d);
    if(a==1||a==n){
        ans=min(ans,3);
        if(b==1||b==m)ans=min(ans,2);
    }
    if(b==1||b==m)ans=min(ans,3);
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}