#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<tuple<int,int,int>> in;
    vector<pair<int,int>> l,r;
    for(int i=0;i<n;++i){
        int x,y,c;
        cin >> x >> y >> c;
        in.emplace_back(x,y,c);
        l.emplace_back(x,i);
        r.emplace_back(y,i);
    }
    sort(l.begin(),l.end());
    vector<pair<int,int>> tmp;
    vector<vector<pair<int,int>>> mx(n);
    for(auto [xx,i]:l){
        auto [x,y,c]=in[i];
        if(tmp.empty()){
            tmp.emplace_back(y,c);
        }else if(tmp.size()==1){
            if(tmp[0].second==c)tmp[0].first=max(tmp[0].first,y);
            else tmp.emplace_back(y,c);
        }else{
            if(tmp[0].second==c)tmp[0].first=max(tmp[0].first,y);
            else if(tmp[1].second==c)tmp[1].first=max(tmp[1].first,y);
            else tmp.emplace_back(y,c);
        }
        sort(tmp.rbegin(),tmp.rend());
        if(tmp.size()==3)tmp.pop_back();
        mx[i]=tmp;
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}