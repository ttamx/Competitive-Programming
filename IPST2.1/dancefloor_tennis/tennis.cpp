#include<bits/stdc++.h>

using namespace std;

int main(){
    ifstream fin("10.in");
    ofstream fout("10.out");
    int n;
    fin >> n;
    vector<vector<int>> v(n,vector<int>(n));
    vector<tuple<int,int,int,int>> a;
    priority_queue<tuple<int,int,int>> pq;
    for(int i=0;i<n;i++)for(int j=0;j<n;j++){
        fin >> v[i][j];
        if(v[i][j])pq.emplace(v[i][j],i,j);
    }
    while(!pq.empty()){
        auto [w,x,y]=pq.top();
        pq.pop();
        for(int i=x;i<=n;i++){
            if(v[i][y]==0)break;
            
        }
    }
    for(auto [x,y,z,w]:a)fout << x << ' ' << y << ' ' << z << ' ' << w << '\n';
    fout << -1;
}