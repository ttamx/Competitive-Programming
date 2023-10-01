#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,m,k;
    cin >> n >> m >> k;
    vector<vector<pair<int,int>>> vec(n+1);
    for(int i=0;i<k;i++){
        int x1,y1,x2,y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if(x1>x2)swap(x1,x2),swap(y1,y2);
        if(y1<y2)vec[x1].emplace_back(y1,0);
        else vec[x1].emplace_back(y2,1);
    }
    vector<int> cur(m+1,-1);
    int lz=0;
    for(int i=1;i<=n;i++){
        if(vec[i].empty())continue;
        sort(vec[i].begin(),vec[i].end());
        int cnt=0;
        for(int j=1;j<vec[i].size();j++)if(vec[i][j-1].first==vec[i][j].first&&vec[i][j-1].second!=vec[i][j].second)return void(cout << "NO\n");
        for(auto [x,t]:vec[i]){
            if(cur[x]<0||cur[x]^lz==t)continue;
            if(++cnt>1)return void(cout << "NO\n");
            lz^=1;
        }
        for(auto [x,t]:vec[i]){
            if(cur[x]<0)cur[x]=t^lz;
            if(cur[x]^lz!=t)return void(cout << "NO\n");
        }
    }
    cout << "YES\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}