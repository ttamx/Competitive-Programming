#include<bits/stdc++.h>

using namespace std;

short n;  
stack<char> ans;

struct node{
    char c;
    short cnt,lv;
    map<short,node*> adj;
    node(char c,short cnt=0):c(c),cnt(cnt){}
};
typedef node* pnode;

void insert(pnode pt,string &s,short idx){
    if(pt->adj.find(s[idx]-'a')==pt->adj.end())pt->adj[s[idx]-'a']=nullptr;
    pnode &t=pt->adj[s[idx]-'a'];
    if(!t)t=new node(s[idx]);
    if(idx==s.size()-1)t->cnt++;
    else insert(t,s,idx+1);
}

short dfs(pnode t){
    t->lv=0;
    for(auto [nk,nt]:t->adj)if(nt)t->lv=max(t->lv,dfs(nt));
    t->lv++;
    return t->lv;
}

void dfs2(pnode t){
    if(t->c!='*'){
        ans.emplace(t->c);
        for(short i=0;i<t->cnt;i++)ans.emplace('P');
    }
    pnode mx=nullptr;
    for(auto [nk,nt]:t->adj)if(nt)if(!mx||nt->lv>mx->lv)mx=nt;
    for(auto [nk,nt]:t->adj)if(nt&&nt!=mx)dfs2(nt);
    if(mx)dfs2(mx);
    ans.emplace('-');
}

pnode rt=new node('*');

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(short i=0;i<n;i++){
        string s;
        cin >> s;
        insert(rt,s,0);
    }
    dfs(rt);
    dfs2(rt);
    while(!ans.empty()&&ans.top()=='-')ans.pop();
    cout << ans.size() << "\n";
    while(!ans.empty()){
        cout << ans.top() << "\n";
        ans.pop();
    }
}