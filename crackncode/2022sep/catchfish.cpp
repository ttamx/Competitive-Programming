#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=5e5+5;

int n,m,l,u;
int p[N],v[N];
ll qs[N];
ll ans;
deque<int> dq;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> l >> u;
    l*=2,u*=2;
    for(int i=1;i<=m;i++)cin >> p[i] >> v[i];
    int idx=0;
    p[m+1]=n+1;
    p[0]=1;
    for(int i=1;i<=m;i++){
        qs[i]=v[i]+qs[i-1];
        while(!dq.empty()&&p[i]-p[dq.front()+1]>u)dq.pop_front();
        while(idx<i&&(p[i+1]-1)-(p[idx]+1)>=l){
            if(p[i]-p[idx+1]>u){
                idx++;
                continue;
            }
            while(!dq.empty()&&qs[dq.back()]>qs[idx])dq.pop_back();
            dq.emplace_back(idx);
            idx++;
        }
        if(!dq.empty())ans=max(ans,qs[i]-qs[dq.front()]);
    }
    cout << ans;
}