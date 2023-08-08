#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef tuple<int,int,int,int> t4;

const int N=1e5+5;
const int Q=5e5+5;

int n,q;
int p[N];
ll ans[Q];
priority_queue<t4,vector<t4>,greater<t4>> pq;
int fa[N];
ll sum,add;

int fp(int u){
    if(u==fa[u])return u;
    return fa[u]=fp(fa[u]);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    iota(fa,fa+n+1,0);
    for(int i=1;i<=n;i++)cin >> p[i] >> p[i];
    for(int i=1;i<=q;i++){
        int t;
        cin >> t;
        if(t==0)ans[i]=n;
        else pq.emplace(t,3,i,0);
    }
    sort(p+1,p+n+1);
    for(int i=2;i<=n;i++){
        int dif=p[i]-p[i-1];
        pq.emplace(dif,1,i,i+1);
    }
    int ct=0,cnt=n;
    while(!pq.empty()){
        auto [t,ty,x,y]=pq.top();
        pq.pop();
        sum+=4ll*(t-ct)*cnt;
        if(ty==1){
            add+=t-1;
            pq.emplace(t+1,2,t-1,0);
            sum-=2*t;
            cnt--;
        }else if(ty==2){
            add-=x;
        }else if(ty==3){
            ans[x]=sum+add;
        }
        ct=t;
    }
    for(int i=1;i<=q;i++)cout << ans[i] << "\n";
}