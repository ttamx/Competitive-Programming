#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m,k;
    cin >> n >> m >> k;
    vector<string> s(n);
    vector<vector<vector<int>>> id(m,vector<vector<int>>(26));
    for(int i=0;i<n;i++){
        cin >> s[i];
        for(int j=0;j<m;j++)if(s[i][j]!='.'){
            id[j][s[i][j]-'A'].emplace_back(i);
        }
    }
    for(int b=0;b<n;b++){
        vector<int> cnt(n);
        int a=-1;
        for(int i=0;i<m;i++)if(s[b][i]!='.'){
            for(auto j:id[i][s[b][i]-'A'])if(j<b){
                if(++cnt[j]==k)a=max(a,j);
            }
        }
        if(a!=-1)cout << a+1 << " " << b+1,exit(0);
    }
    cout << -1;
}