#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,k;
    cin >> k >> n;
    map<string,int> mp;
    for(int i=0;i<n;i++){
        string x;
        cin >> x;
        mp[x]=i;
    }
    vector<string> ans(n,string(n,'?'));
    for(int i=0;i<n;i++)ans[i][i]='B';
    while(k--){
        vector<string> v(n);
        for(auto &x:v)cin >> x;
        for(int i=0;i<n-1;i++){
            bool ok=false;
            for(int j=i+1;j<n;j++){
                ok|=v[j]<v[j-1];
                if(ok){
                    ans[mp[v[j]]][mp[v[i]]]='1';
                    ans[mp[v[i]]][mp[v[j]]]='0';
                }
            }
        }
    }
    for(auto x:ans)cout << x << '\n';
}