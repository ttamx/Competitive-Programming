#include<bits/stdc++.h>

using namespace std;

const int N=15005;

int n,m,sum;
int a[N],b[N],cnt[N];
bitset<N> dp[N],filt[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        sum+=a[i];
        cnt[a[i]]++;
    }
    cin >> m;
    for(int i=1;i<=m;i++)cin >> b[i];
    filt[0][0]=1;
    for(int i=1,k=0,sz=n;i<=sum;i++){
        filt[i]=filt[i-1];
        for(int j=0;j<sz;j++)filt[i][++k]=1;
        sz-=cnt[i];
    }
    dp[0][0]=1;
    for(int i=m;i>=1;i--){
        for(int j=1;j*b[i]<=sum;j++){
            dp[j]|=dp[j-1]<<b[i]&filt[j];
        }
    }
    int st=0;
    while(st<=sum&&!dp[st][sum])st++;
    if(st>sum)cout << -1,exit(0);
    priority_queue<pair<int,int>> pq;
    for(int i=1;i<=n;i++)pq.emplace(a[i],i);
    cout << st << "\n";
    for(int i=st,j=sum,p=1;i>0;i--){
        while(j<b[p]||!dp[i-1][j-b[p]])p++;
        j-=b[p];
        cout << b[p] << " ";
        vector<pair<int,int>> res;
        for(int t=1;t<=b[p];t++){
            auto [sz,id]=pq.top();
            pq.pop();
            cout << id << " \n"[t==b[p]];
            if(--sz)res.emplace_back(sz,id);
        }
        for(auto v:res)pq.emplace(v);
    }
}