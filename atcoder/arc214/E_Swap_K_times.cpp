#include "template.hpp"
#include "data-structure/fenwick-tree.hpp"

void runcase(){
    int n;
    ll k;
    cin >> n >> k;
    vector<int> a(n),b(n);
    for(auto &x:a)cin >> x,x--;
    for(auto &x:b)cin >> x,x--;
    vector<vector<int>> pos_a(n),pos_b(n);
    for(int i=0;i<n;i++)pos_a[a[i]].emplace_back(i);
    for(int i=0;i<n;i++)pos_b[b[i]].emplace_back(i);
    vector<int> pos(n);
    for(int i=0;i<n;i++){
        for(int j=0;j<pos_a[i].size();j++){
            pos[pos_b[i][j]]=pos_a[i][j];
        }
    }
    ll base=0;
    Fenwick<int> f(n);
    for(int i=0;i<n;i++)f.update(i,+1);
    for(int i=0;i<n;i++){
        f.update(pos[i],-1);
        base+=f.query(pos[i]);
    }
    ll t=(base+k-1)/k;
    if(t*k%2==base%2){
        cout << t << "\n";
        return;
    }
    int q=0;
    vector<vector<tuple<int,int,int,int>>> event(n);
    auto query=[&](int l,int r,int x,int y){
        event[r].emplace_back(q,x+1,y-1,1);
        if(l>0)event[l-1].emplace_back(q,x+1,y-1,-1);
        q++;
    };
    for(int i=0;i<n;i++){
        for(int j=0;j+1<pos_b[i].size();j++){
            query(pos_b[i][j],pos_b[i][j+1],pos_a[i][j],pos_a[i][j+1]);
        }
    }
    if(!q){
        if(k%2==1){
            cout << t+1 << "\n";
        }else{
            cout << -1 << "\n";
        }
        return;
    }
    vector<int> ans(q);
    for(int i=0;i<n;i++){
        f.update(pos[i],+1);
        for(auto [j,x,y,m]:event[i]){
            ans[j]+=f.query(x,y)*m;
        }
    }
    base+=*min_element(ans.begin(),ans.end())*2+1;
    ll cand=(base+k-1)/k;
    if(k%2==1)cand=min(cand,t+1);
    cout << cand << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}