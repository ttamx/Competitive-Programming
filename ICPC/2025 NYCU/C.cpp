#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m,k;
    cin >> n >> m >> k;
    vector<int> a(n),b,c;
    for(auto &x:a){
        cin >> x;
        int y=1LL*x*x%m;
        b.emplace_back(x);
        c.emplace_back(y);
        c.emplace_back((m+k-x)%m);
    }
    sort(b.begin(),b.end());
    sort(c.begin(),c.end());
    b.erase(unique(b.begin(),b.end()),b.end());
    c.erase(unique(c.begin(),c.end()),c.end());
    int nn=b.size();
    int mm=c.size();
    auto get_b=[&](int x){
        return lower_bound(b.begin(),b.end(),x)-b.begin();
    };
    auto get_c=[&](int x){
        return lower_bound(c.begin(),c.end(),x)-c.begin();
    };
    vector<int> deg(nn+mm);
    vector<vector<pair<int,int>>> adj(nn+mm);
    auto link=[&](int u,int v,int i){
        deg[u]++;
        deg[v]--;
        adj[u].emplace_back(v,i);
    };
    for(int i=0;i<n;i++){
        int x=a[i];
        int y=1LL*x*x%m;
        link(nn+get_c(y),get_b(x),i);
        link(get_b(x),nn+get_c((m+k-x)%m),-1);
    }
    int st=-1;
    for(int i=0;i<nn+mm;i++){
        if(abs(deg[i])>1){
            cout << "NO\n";
            exit(0);
        }
        if(deg[i]==1){
            if(st==-1){
                st=i;
            }else{
                cout << "NO\n";
                exit(0);
            }
        }
    }
    if(st==-1){
        st=0;
    }
    vector<int> ans;
    function<void(int)> dfs=[&](int u){
        while(!adj[u].empty()){
            auto [v,i]=adj[u].back();
            adj[u].pop_back();
            dfs(v);
            if(i!=-1){
                ans.emplace_back(i);
            }
        }
    };
    dfs(st);
    reverse(ans.begin(),ans.end());
    if(ans.size()!=n){
        cout << "NO\n";
    }else{
        cout << "YES\n";
        for(auto i:ans){
            cout << a[i] << " ";
        }
        cout << "\n";
    }
}