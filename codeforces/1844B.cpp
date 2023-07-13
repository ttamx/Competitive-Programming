#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    if(n<=2){
        for(int i=1;i<=n;i++)cout << i << " \n"[i==n];
        return;
    }
    vector<int> ans(n);
    ans[0]=3;
    ans[n/2]=1;
    ans[n-1]=2;
    int cnt=4;
    for(int i=1;i<n-1;i++)if(i!=n/2)ans[i]=cnt++;
    for(auto x:ans)cout << x << " ";
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}