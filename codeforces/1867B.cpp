#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    string s;
    cin >> s;
    int l=0,r=n-1;
    int cnt=0;
    while(l<r){
        cnt+=s[l]!=s[r];
        l++,r--;
    }
    vector<int> ans(n+1);
    for(int i=0;i<=n;i++){
        if(i>n-cnt)break;
        if(i==cnt)ans[i]=1;
        if(i>0){
            if(n&1)ans[i]|=ans[i-1];
            else if(i>1)ans[i]|=ans[i-2];
        }
    }
    for(auto x:ans)cout << x;
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}