#include<bits/stdc++.h>

using namespace std;

int main(){
    ifstream fin("10.in");
    ofstream fout("10.out");
    int n;
    fin >> n;
    vector<vector<int>> v(n,vector<int>(n));
    vector<tuple<int,int,int,int>> ans;
    multiset<tuple<int,int,int>> pq;
    for(int i=0;i<n;i++)for(int j=0;j<n;j++){
        fin >> v[i][j];
        if(v[i][j]){
            pq.emplace(v[i][j],i,j);
            cout << v[i][j] << ' ' << i << ' ' << j << '\n';
        }
    }
    cout << "-----\n";
    while(!pq.empty()){
        auto [w,x,y]=*prev(pq.end());
        vector<vector<int>> vec(4,vector<int>(5));
        for(int i=0;i<4;i++)vec[i][1]=vec[i][3]=x,vec[i][2]=vec[i][4]=y;
        cout << x << ' ' << y << '\n';
        for(int i=x;i>=0;i--){
            if(v[i][y]==0)break;
            vec[0][0]++;
            vec[0][1]=i;
            vec[0][2]=y;
        }
        for(int i=x+1;i<=n-1;i++){
            if(v[i][y]==0)break;
            vec[0][0]++;
            vec[0][3]=i;
            vec[0][4]=y;
        }
        for(int i=y;i>=0;i--){
            if(v[x][i]==0)break;
            vec[1][0]++;
            vec[1][1]=x;
            vec[1][2]=i;
        }
        for(int i=y+1;i<=n-1;i++){
            if(v[x][i]==0)break;
            vec[1][0]++;
            vec[1][3]=x;
            vec[1][4]=i;
        }
        for(int i=x,j=y;i>=0&&j>=0;i--,j--){
            if(v[i][j]==0)break;
            vec[2][0]++;
            vec[2][1]=i;
            vec[2][2]=j;
        }
        for(int i=x+1,j=y+1;i<=n-1&&j<=n-1;i++,j++){
            if(v[i][j]==0)break;
            vec[2][0]++;
            vec[2][3]=i;
            vec[2][4]=j;
        }
        for(int i=x,j=y;i>=0&&j<=n-1;i--,j++){
            if(v[i][j]==0)break;
            vec[3][0]++;
            vec[3][1]=i;
            vec[3][2]=j;
        }
        for(int i=x+1,j=y-1;i<=n-1&&j>=0;i++,j--){
            if(v[i][j]==0)break;
            vec[3][0]++;
            vec[3][3]=i;
            vec[3][4]=j;
        }
        sort(vec.rbegin(),vec.rend());
        for(auto i:vec){
            for(auto ii:i){
                cout << ii << ' ';
            }
            cout << '\n';
        }
        int a=vec[0][1],b=vec[0][2],c=vec[0][3],d=vec[0][4];
        ans.emplace_back(a+1,b+1,c+1,d+1);
        while(a!=c||b!=d){
            cout << v[a][b] << ' ' << a << ' ' << b << '\n';
            pq.erase(pq.find({v[a][b],a,b}));
            if(--v[a][b]>0)pq.emplace(v[a][b],a,b);
            if(a<c)a++;
            if(a>c)a--;
            if(b<d)b++;
            if(b>d)b--;
        }
        pq.erase(pq.find({v[a][b],a,b}));
        if(--v[a][b]>0)pq.emplace(v[a][b],a,b);
    }
    for(auto [x,y,z,w]:ans)fout << x << ' ' << y << ' ' << z << ' ' << w << '\n';
    fout << -1;
}