#include <bits/stdc++.h>

using namespace std;

const int N=1e6+5;
const int INF=INT_MAX/2;

int n;
int a[N];
int sl,sc,el,ec;
vector<pair<int,int>> adj[2*N];
int dist[2*N];

void link(int u,int v,int w){
    adj[u].emplace_back(v,w);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> sl >> sc >> el >> ec;
    sc--,ec--;
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<=n;i++){
        int si=i*2,ei=i*2+1;
        link(si,ei,a[i]);
        link(ei,si,a[i]);
    }
    for(int i=1;i<n;i++){
        int si=i*2,ei=i*2+1,sj=i*2+2,ej=i*2+3,j=i+1;
        link(sj,ei,1);
        link(ei,sj,1);
        link(si,sj,1);
        link(sj,si,1);
    }
    stack<int> s;
    for(int i=1;i<=n;i++){
        while(!s.empty()&&a[s.top()]>a[i]){
            int j=s.top();
            s.pop();
            link(i*2+1,j*2+1,a[j]-a[i]+i-j);
        }
        if(!s.empty()){
            int j=s.top();
            link(i*2+1,j*2+1,i-j);
        }
        s.emplace(i);
    }
    while(!s.empty())s.pop();
    for(int i=n;i>=1;i--){
        while(!s.empty()&&a[s.top()]>a[i]){
            int j=s.top();
            s.pop();
            link(i*2+1,j*2+1,a[j]-a[i]+j-i);
        }
        if(!s.empty()){
            int j=s.top();
            link(i*2+1,j*2+1,j-i);
        }
        s.emplace(i);
    }
    for(int i=0;i<=2*n+1;i++)dist[i]=INF;
    int mn=sc;
    for(int i=sl;i<=n;i++){
        mn=min(mn,a[i]);
        link(0,i*2,i-sl+sc);
        link(0,i*2+1,i-sl+abs(a[i]-mn));
        if(i==el)link(0,1,i-sl+abs(ec-mn));
    }
    mn=sc;
    for(int i=sl;i>=1;i--){
        mn=min(mn,a[i]);
        link(0,i*2,sl-i+sc);
        link(0,i*2+1,sl-i+abs(a[i]-mn));
        if(i==el)link(0,1,sl-i+abs(ec-mn));
    }
    mn=a[el];
    for(int i=el;i<=n;i++){
        mn=min(mn,a[i]);
        link(i*2,1,i-el+ec);
        link(i*2+1,1,i-el+abs(ec-mn));
    }
    mn=a[el];
    for(int i=el;i>=1;i--){
        mn=min(mn,a[i]);
        link(i*2,1,el-i+ec);
        link(i*2+1,1,el-i+abs(ec-mn));
    }
    using P = pair<int,int>;
    priority_queue<P,vector<P>,greater<P>> pq;
    pq.emplace(0,0);
    dist[0]=0;
    while(!pq.empty()){
        auto [d,u]=pq.top();
        pq.pop();
        if(d>dist[u])continue;
        for(auto [v,w]:adj[u])if(d+w<dist[v]){
            dist[v]=d+w;
            pq.emplace(dist[v],v);
        }
    }
    cout << dist[1];
}