#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,k;
    cin >> n >> k;
    vector<array<int,26>> nodes;
    auto new_node=[&](){
        array<int,26> a;
        for(int i=0;i<26;i++)a[i]=-1;
        nodes.emplace_back(a);
        return nodes.size()-1;
    };
    new_node();
    for(int i=0;i<n;i++){
        string s;
        cin >> s;
        int u=0;
        for(auto ch:s){
            int c=ch-'a';
            if(nodes[u][c]==-1){
                nodes[u][c]=new_node();
            }
            u=nodes[u][c];
        }
    }
    int m=nodes.size();
    vector<bool> dp(m),dp2(m);
    function<void(int)> dfs=[&](int u){
        int ch=0;
        for(auto v:nodes[u]){
            if(v==-1)continue;
            dfs(v);
            if(!dp[v])dp[u]=true;
            if(!dp2[v])dp2[u]=true;
            ch++;
        }
        if(ch==0)dp2[u]=true;
    };
    dfs(0);
    if(dp[0]){
        if(dp2[0]||k%2==1){
            cout << "First\n";
        }else{
            cout << "Second\n";
        }
    }else{
        cout << "Second\n";
    }
}