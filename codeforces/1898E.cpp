#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,m;
    cin >> n >> m;
    string a,b;
    cin >> a >> b;
    for(auto &x:a)x-='a';
    for(auto &x:b)x-='a';
    int id=0;
    queue<int> q[30];
    for(int i=0;i<m;i++){
        while(id<n&&q[b[i]].empty())q[a[id]].emplace(id++);
        if(q[b[i]].empty())return void(cout << "NO\n");
        for(int j=0;j<b[i];j++)while(!q[j].empty()&&q[j].front()<q[b[i]].front())q[j].pop();
        q[b[i]].pop();
    }
    cout << "YES\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}