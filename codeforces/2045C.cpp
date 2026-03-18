#include<bits/stdc++.h>

using namespace std;

const int INF=1e9;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    string s,t;
    cin >> s >> t;
    tuple<int,int,int> ans(INF,-1,-1);
    vector<int> pos(256,-1);
    for(int i=1;i<s.size();i++){
        if(pos[s[i]]==-1){
            pos[s[i]]=i;
        }
    }
    for(int i=0;i+1<t.size();i++){
        if(pos[t[i]]!=-1){
            ans=min(ans,make_tuple(int(pos[t[i]]+t.size()-i),pos[t[i]],i));
        }
    }
    auto [_,x,y]=ans;
    if(x==-1)cout << -1 << "\n";
    else cout << s.substr(0,x) << t.substr(y,t.size()-y) << "\n";
}