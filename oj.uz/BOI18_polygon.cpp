#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n;
int a[N];
string name[N],love[N];
map<string,int> mp;
int deg[N];
int ans=0;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> name[i] >> love[i];
        mp[name[i]]=i;
    }
    for(int i=1;i<=n;i++){
        a[i]=mp[love[i]];
        deg[a[i]]++;
    }
    queue<int> q;
    for(int i=1;i<=n;i++)if(!deg[i])q.emplace(i);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        
    }
}