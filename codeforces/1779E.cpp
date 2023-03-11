#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    auto ask=[&](int x,vector<int> v){
        string s(n,'0');
        for(auto i:v)s[i-1]='1';
        cout << "? " << x << " " << s << endl;
        int res;
        cin >> res;
        return res;
    };
    vector<vector<int>> adj(n+1),rev(n+1);
    vector<int> pa(n+1);
    iota(pa.begin(),pa.end(),0);
    int p=1;
    for(int i=2;i<=n;i++){
        if(ask(i,{p})){
            adj[i].push_back(p);
            rev[p].push_back(i);
            pa[p]=i;
            p=i;
        }else{
            adj[p].push_back(i);
            rev[i].push_back(p);
            pa[i]=p;
        }
    }
    vector<int> v;
    vector<bool> can(n+1);
    string ans(n,'0');
    function<void(int)> dfs=[&](int u){
        if(can[u])return;
        can[u]=true;
        v.push_back(u);
        ans[u-1]='1';
        for(auto v:rev[u]){
            dfs(v);
        }
    };
    dfs(p);
    for(int i=n;i>=1;i--){
        if(can[i])continue;
        if(ask(i,v)){
            dfs(i);
        }
    }
    cout << "! " << ans << endl;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}