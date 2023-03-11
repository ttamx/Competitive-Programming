#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,s;
    cin >> n >> s;
    vector<int> a(n+1);
    for(int i=1;i<=n;i++)cin >> a[i];
    vector<bool> b(n+1);
    int ans=0;
    b[0]=true;
    while(!b[s]){
        b[s]=true;
        s=a[s];
        ans++;
    }
    cout << ans;
}