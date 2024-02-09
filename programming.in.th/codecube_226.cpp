#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;

int n,q;
int p[N],id[N],pos[N];

bool same(int u,int v){
    return id[u]==id[v];
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;i++)cin >> p[i];
    for(int i=1;i<=n;i++)if(!id[i]){
        int u=i,cnt=0;
        do{
            pos[u]=cnt++;
            id[u]=i;
            u=p[u];
        }while(u!=i);
    }
    while(q--){
        int s,e,a,b;
        cin >> s >> e >> a >> b;
        if(!same(a,b)){
            cout << (same(s,e)||(same(s,a)&&same(e,b))||(same(s,b)&&same(e,a))?"DEAD":"SURVIVE") << "\n";
            continue;
        }
        if(!same(s,a)||!same(e,a)){
            cout << (same(s,e)?"DEAD":"SURVIVE") << "\n";
            continue;
        }
        if(pos[a]>pos[b])swap(a,b);
        auto calc=[&](int u){
            return pos[a]<pos[u]&&pos[u]<=pos[b];
        };
        cout << ((calc(s)^calc(e))?"SURVIVE":"DEAD") << "\n";
    }
}