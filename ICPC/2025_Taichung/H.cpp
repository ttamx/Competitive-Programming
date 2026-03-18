#include<bits/stdc++.h>

using namespace std;

struct DS{
    int n;
    vector<int> pos,rank;
    DS(int n):n(n),pos(n),rank(n){
        iota(pos.begin(),pos.end(),0);
    }
    void concat(DS o){
        vector<int> ord(n),new_rank(n);
        iota(ord.begin(),ord.end(),0);
        sort(ord.begin(),ord.end(),[&](int i,int j){
            if(rank[i]==rank[j])return o.rank[pos[i]]<o.rank[pos[j]];
            return rank[i]<rank[j];
        });
        for(int i=1;i<n;i++){
            int u=ord[i],v=ord[i-1];
            new_rank[u]=(rank[u]==rank[v]&&o.rank[pos[u]]==o.rank[pos[v]])?new_rank[v]:i;
        }
        rank=move(new_rank);
        for(int i=0;i<n;i++){
            pos[i]=o.pos[pos[i]];
        }
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int k,t;
    cin >> k >> t;
    string s;
    cin >> s;
    int n=1<<k;
    t=(k-t%k)%k;
    DS cur(n);
    for(int i=0;i<n;i++){
        cur.rank[i]=s[i];
        cur.pos[i]=(i+(1<<t))%n;
    }
    int step=n>>t;
    for(int i=0;i<k-t;i++){
        cur.concat(cur);
    }
    for(int i=0;i<n;i++){
        cur.pos[i]=(i+1)%n;
    }
    for(int i=0;i<t;i++){
        cur.concat(cur);
    }
    int p=0;
    while(cur.rank[p]!=0){
        p++;
    }
    string ans="";
    for(int i=0;i<(1<<t);i++){
        for(int j=i;j<n;j+=1<<t){
            ans.push_back(s[(p+j)%n]);
        }
    }
    cout << ans << "\n";
}