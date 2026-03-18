#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int q;
    cin >> q;
    vector<int> a(q+1),c(q+1);
    cin >> a[0] >> c[0];
    vector<int> dep(q+1),par(q+1),jump(q+1);
    for(int i=1;i<=q;i++){
        int op;
        cin >> op;
        if(op==1){
            cin >> par[i] >> a[i] >> c[i];
            dep[i]=dep[par[i]]+1;
            jump[i]=dep[par[i]]-dep[jump[par[i]]]==dep[jump[par[i]]]-dep[jump[jump[par[i]]]]?jump[jump[par[i]]]:par[i];
        }else{
            int u,w;
            cin >> u >> w;
            int cnt=0;
            ll bal=0;
            while(a[u]>0&&w>0){
                int v=u;
                while(v){
                    if(a[jump[v]]>0)v=jump[v];
                    else if(a[par[v]]>0)v=par[v];
                    else break;
                }
                int t=min(a[v],w);
                assert(t>0);
                a[v]-=t;
                w-=t;
                cnt+=t;
                bal+=1LL*t*c[v];
            }
            cout << cnt << " " << bal << endl;
        }
    }
}