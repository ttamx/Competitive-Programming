#include<bits/stdc++.h>

using namespace std;

using ll = long long;

void solve(){
    int n,k;
    cin >> n >> k;
    string s;
    cin >> s;
    vector<pair<int,int>> a;
    int suf=1;
    a.emplace_back(1,0);
    for(int i=0;i<k;i++){
        int x;
        cin >> x;
        a.emplace_back(x,1);
        a.emplace_back(1,0);
        suf+=x+1;
    }
    vector<array<int,2>> f(n+3,{0,0});
    int pre=0;
    for(auto [x,c]:a){
        suf-=x;
        f[pre][c]++;
        f[n-suf+2][c]--;
        pre+=x;
    }
    string ans="";
    for(int i=1;i<=n;i++){
        f[i][0]+=f[i-1][0];
        f[i][1]+=f[i-1][1];
        if(f[i][0]&&f[i][1])ans.push_back('?');
        else if(f[i][0])ans.push_back('0');
        else if(f[i][1])ans.push_back('1');
        else assert(false);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}