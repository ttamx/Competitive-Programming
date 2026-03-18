#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    string s,t;
    cin >> s >> t;
    vector<vector<int>> pos(26);
    for(int i=0;i<s.size();i++){
        pos[s[i]-'a'].emplace_back(i);
    }
    int ans=1,cur=0;
    for(auto x:t){
        auto &v=pos[x-'a'];
        auto it=lower_bound(v.begin(),v.end(),cur);
        if(it==v.end()){
            cur=*v.begin()+1;
            ans++;
        }else{
            cur=*it+1;
        }
    }
    cout << ans << "\n";
}