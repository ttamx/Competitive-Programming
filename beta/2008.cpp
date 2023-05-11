#include<bits/stdc++.h>

using namespace std;

const int N=25005;

int n;  
vector<char> ans;

struct node{
    char c;
    int cnt,lv;
    map<int,node*> adj;
    node(char c,int cnt=0):c(c),cnt(cnt){}
};
typedef node* pnode;

void insert(pnode pt,string &s,int idx){
    if(pt->adj.find(s[idx]-'a')==pt->adj.end())pt->adj[s[idx]-'a']=nullptr;
    pnode &t=pt->adj[s[idx]-'a'];
    if(!t)t=new node(s[idx]);
    if(idx==s.size()-1)t->cnt++;
    else insert(t,s,idx+1);
}

int dfs(pnode t){
    t->lv=0;
    for(auto [nk,nt]:t->adj)if(nt)t->lv=max(t->lv,dfs(nt));
    t->lv++;
    return t->lv;
}

void dfs2(pnode t){
    if(t->c!='*'){
        ans.emplace_back(t->c);
        for(int i=0;i<t->cnt;i++)ans.emplace_back('P');
    }
    pnode mx=nullptr;
    for(auto [nk,nt]:t->adj)if(nt)if(!mx||nt->lv>mx->lv)mx=nt;
    for(auto [nk,nt]:t->adj)if(nt&&nt!=mx)dfs2(nt);
    if(mx)dfs2(mx);
    ans.emplace_back('-');
}

pnode rt=new node('*');

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=0;i<n;i++){
        string s;
        cin >> s;
        insert(rt,s,0);
    }
    dfs(rt);
    dfs2(rt);
    while(!ans.empty()&&ans.back()=='-')ans.pop_back();
    cout << ans.size() << "\n";
    for(auto x:ans)cout << x << "\n";
}