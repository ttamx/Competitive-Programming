#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    map<int,vector<int>> mp;
    for(int i=0;i<n;i++){
        int x,y;
        cin >> x >> y;
        mp[x].emplace_back(y);
    }
    vector<vector<pair<int,int>>> ans;
    int px=0,py=0,side=0;
    for(auto &[x,v]:mp){
        sort(v.begin(),v.end());
        if(side)reverse(v.begin(),v.end());
        if(px){
            vector<pair<int,int>> tmp;
            tmp.emplace_back(px,py);
            if(side){
                int y=v.back();
                v.pop_back();
                if(y<py)tmp.emplace_back(px,y);
                if(y>py)tmp.emplace_back(x,py);
                tmp.emplace_back(x,y);
            }else{
                int y=v.back();
                v.pop_back();
                if(y>py)tmp.emplace_back(px,y);
                if(y<py)tmp.emplace_back(x,py);
                tmp.emplace_back(x,y);
            }
            ans.emplace_back(tmp);
            px=py=0;
        }
        side^=1;
        while(v.size()>=2){
            vector<pair<int,int>> tmp;
            tmp.emplace_back(x,v.back());
            v.pop_back();
            tmp.emplace_back(x,v.back());
            v.pop_back();
            ans.emplace_back(tmp);
        }
        if(!v.empty()){
            px=x;
            py=v[0];
        }
    }
    cout << ans.size() << "\n";
    for(auto &v:ans){
        cout << v.size();
        for(auto [x,y]:v)cout << " " << x << " " << y;
        cout << "\n";
    }
}