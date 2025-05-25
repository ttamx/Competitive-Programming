#include<bits/stdc++.h>

using namespace std;

using uint = uint32_t;

const int N=20000;

int n;
uint a[4];
bool f[N];
uint ans;
vector<uint> pr;
int pos[N];

uint calc(uint p){
    uint c=0,f=0;
    for(uint v=n;v/=p;)c+=v;
    for(int i=0;i<4;i++)f=f*p+a[i];
    return c*f;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=0;i<4;i++)cin >> a[i];
    for(int i=2;i<N;i++)f[i]=true;
    for(int i=2;i<min(N,n+1);i++){
        if(!f[i])continue;
        ans+=calc(i);
        pr.emplace_back(i);
        int &j=pos[i];
        for(j=i;j<N;j+=i)f[j]=false;
        j-=N;
    }
    for(int st=N;st<=n;st+=N){
        for(int i=0;i<N;i++)f[i]=true;
        for(auto p:pr){
            int &i=pos[p];
            for(;i<N;i+=p)f[i]=false;
            i-=N;
        }
        for(int i=0;i<N&&st+i<=n;i++)if(f[i])ans+=calc(st+i);
    }
    cout << ans;
}