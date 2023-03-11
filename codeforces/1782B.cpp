#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    sort(a.begin(),a.end());
    a.push_back(n);
    int ans=0;
    if(a[0]>0)ans++;
    for(int i=0;i<n;i++){
        while(i<n){
            if(a[i]>i)i=a[i];
            else if(a[i]==a[i+1])i++;
            else break;
        }
        while(i<n&&a[i]<=i)i++;
        ans++;
    }
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}