#include<bits/stdc++.h>

using namespace std;

const int B=30;

struct Node;
using Ptr = Node*;
struct Node{
    int cnt;
    array<Ptr,2> ch;
    Node():cnt(0),ch{nullptr,nullptr}{}
};

Ptr root=new Node();

void update(int x,int v){
    Ptr u=root;
    u->cnt+=v;
    for(int i=B-1;i>=0;i--){
        int c=x>>i&1;
        if(!u->ch[c])u->ch[c]=new Node();
        u=u->ch[c];
        u->cnt+=v;
    }
}

int query(int x){
    Ptr u=root;
    int res=0;
    for(int i=B-1;i>=0;i--){
        int c=x>>i&1;
        if(u->ch[c^1]&&u->ch[c^1]->cnt){
            res|=1<<i;
            u=u->ch[c^1];
        }else{
            u=u->ch[c];
        }
    }
    return res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int q;
    cin >> q;
    update(0,+1);
    while(q--){
        char op;
        int x;
        cin >> op >> x;
        if(op=='?')cout << query(x) << "\n";
        else update(x,op=='+'?1:-1);
    }
}