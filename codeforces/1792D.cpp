#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<vector<int>> a(n,vector<int>(m+1));
    map<vector<int>,bool> mp;
    for(auto &v:a){
        vector<int> res(m+1);
        for(int i=1;i<=m;i++)cin >> v[i];
        for(int i=1;i<=m;i++)for(int j=1;j<=m;j++){
            if(v[j]!=i)continue;
            res[j]=i;
            mp[res]=true;
        }
    }
    for(auto v:a){
        vector<int> res(m+1);
        int ans=0;
        for(int i=1;i<=m;i++){
            res[v[i]]=i;
            if(mp[res])ans=i;
        }
        cout << ans << ' ';
    }
    cout << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}