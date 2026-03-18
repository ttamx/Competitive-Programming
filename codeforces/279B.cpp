#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,t;
    cin >> n >> t;
    int ans=0,cur=0;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    for(int i=0,j=0;i<n;i++){
        if(a[i]>t){
            j=i+1;
            cur=0;
            continue;
        }
        while(j<n&&cur+a[j]<=t){
            cur+=a[j];
            j++;
        }
        ans=max(ans,j-i);
        cur-=a[i];
    }
    cout << ans << "\n";
}