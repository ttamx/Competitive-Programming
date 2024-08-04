#include<bits/stdc++.h>

using namespace std;

const int X=2e6;

int n,m;
pair<int,int> nxt[X+5];
bool vis[X+5];
int ans;
priority_queue<int> pq;

int calc(int x){
    if(vis[x])return 0;
    vis[x]=true;
    return calc(nxt[x].first)+nxt[x].second;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=X;i++)nxt[i]={i+1,0};
    for(int i=0;i<n;i++){
        int l,r;
        cin >> l >> r;
        nxt[l]={r+1,1};
        nxt[r]={l+1,1};
    }
    vis[X+1]=true;
    ans=calc(1);
    for(int i=2;i<=X;i++)if(!vis[i])pq.emplace(calc(i));
    while(!pq.empty()&&m>0){
        ans+=pq.top()+2;
        pq.pop();
        m--;
    }
    cout << ans+m/2*4+m%2;
}