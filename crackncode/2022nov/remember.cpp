#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;

int n,m,k,q;
int s1[N],s2[N];
vector<int> fc[N],fc2[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    k=sqrt(n);
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        fc[u].push_back(v);
        fc[v].push_back(u);
    }
    for(int i=1;i<=n;i++)for(auto j:fc[i])if(fc[j].size()>k)fc2[i].push_back(j);
    cin >> q;
    while(q--){
        char c;
        cin >> c;
        if(c=='U'){
            int x,y;
            cin >> x >> y;
            s1[x]+=y;
            if(fc[x].size()>k)s2[x]+=y;
            else for(auto i:fc[x])s1[i]+=y;
        }else{
            int x;
            cin >> x;
            int ans=s1[x];
            for(auto i:fc2[x])ans+=s2[i];
            cout << ans << '\n';
        }
    }
}