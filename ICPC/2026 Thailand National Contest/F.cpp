#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<int> a(n);
    for(int i=0;i<n;i++)a[i]=s[i]=='L';
    set<int> ans;
    for(int t=0;t<2;t++){
        vector<int> b(n);
        b[0]=t;
        for(int i=0;i+1<n;i++)b[i+1]=a[i]^b[i];
        if((a[n-1]^b[n-1])==b[0]){
            ans.emplace(accumulate(b.begin(),b.end(),0));
        }
    }
    if(ans.empty()){
        cout << -1 << "\n";
    }else{
        for(auto x:ans)cout << x << " ";
        cout << "\n";
    }
}