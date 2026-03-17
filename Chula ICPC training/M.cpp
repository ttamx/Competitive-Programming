#include<bits/stdc++.h>

using namespace std;

void solve(){
    int n,m;
    cin >> n >> m;
    vector<bool> to_die(n);
    vector<pair<int,int>> a(m);
    for(auto &[u,v]:a){
        cin >> u >> v;
        u--,v--;
    }
    int s;
    cin >> s;
    for(int i=0;i<s;i++){
        int x;
        cin >> x;
        x--;
        to_die[x]=true;
    }
    string ans="";
    reverse(a.begin(),a.end());
    for(auto [u,v]:a){
        if(to_die[v]&&!to_die[u]){
            to_die[v]=false;
            ans.push_back('T');
        }else{
            ans.push_back('N');
        }
    }
    for(auto x:to_die){
        if(x){
            cout << "NIE\n";
            return ;
        }
    }
    reverse(ans.begin(),ans.end());
    cout << "TAK\n";
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)solve();
}