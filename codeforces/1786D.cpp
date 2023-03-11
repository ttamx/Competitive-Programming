#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    stack<int> s[3][3];
    string win="win";
    vector<tuple<int,int,int,int>> ans;
    for(int i=1;i<=n;i++){
        string str;
        cin >> str;
        int a[3]={};
        for(auto x:str){
            if(x=='w')a[0]++;
            if(x=='i')a[1]++;
            if(x=='n')a[2]++;
        }
        int mx=-1;
        for(int j=0;j<3;j++)if(a[j]>1)mx=j;
        for(int j=0;j<3;j++){
            if(j==mx||a[j]==1)continue;
            s[mx][j].push(i);
        }
    }
    for(int u=0;u<3;u++){
        for(int v=u+1;v<3;v++){
            while(!s[u][v].empty()&&!s[v][u].empty()){
                ans.push_back({s[u][v].top(),u,s[v][u].top(),v});
                s[u][v].pop();
                s[v][u].pop();
            }
        }
    }
    while(!s[0][1].empty()&&!s[1][2].empty()&&!s[2][0].empty()){
        ans.push_back({s[0][1].top(),0,s[1][2].top(),1});
        ans.push_back({s[1][2].top(),0,s[2][0].top(),2});
        s[0][1].pop();
        s[1][2].pop();
        s[2][0].pop();
    }
    while(!s[0][2].empty()&&!s[2][1].empty()&&!s[1][0].empty()){
        ans.push_back({s[0][2].top(),0,s[2][1].top(),2});
        ans.push_back({s[2][1].top(),0,s[1][0].top(),1});
        s[0][2].pop();
        s[2][1].pop();
        s[1][0].pop();
    }
    cout << ans.size() << '\n';
    for(auto [a,b,c,d]:ans)cout << a << ' ' << win[b] << ' ' << c << ' ' << win[d] << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}