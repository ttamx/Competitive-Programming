#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    int mx=-2e9;
    int ans=0;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        mx=max(mx,x);
        if(x<0)ans=x;
    }
    if(ans<0)mx=ans;
    cout << mx << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}