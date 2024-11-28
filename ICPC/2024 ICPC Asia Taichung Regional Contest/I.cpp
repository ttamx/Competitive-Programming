#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int N=1e6+5;

int n,q;
vector<tuple<int,int,string>> qr;
vector<pair<string,int>> a;
int ord[N];

struct Node;
using Ptr = Node*;
struct Node{
    Ptr par;
    set<pair<int,int>> s;
    map<int,Ptr> ch;
    Node(Ptr p):par(p),s(),ch(){}
    void insert(int i){
        s.emplace(ord[i],i);
    }
    void erase(int i){
        s.erase(make_pair(ord[i],i));
    }
    int query(){
        if(s.empty())return -1;
        return s.begin()->second;
    }
};

Ptr root=new Node(nullptr);
Ptr cur=root;

void insert(int i){
    string &s=a[ord[i]].first;
    Ptr u=root;
    u->insert(i);
    for(auto c:s){
        if(!u->ch[c]){
            u->ch[c]=new Node(u);
        }
        u=u->ch[c];
        u->insert(i);
    }
}

void erase(int i){
    string &s=a[ord[i]].first;
    Ptr u=root;
    u->erase(i);
    for(auto c:s){
        assert(u->ch[c]);
        u=u->ch[c];
        u->erase(i);
    }
}

signed main() {
    cin.tie(nullptr)->ios::sync_with_stdio(false);
    cin >> q;
    qr.resize(q);
    for(auto &[o,x,s]:qr){
        string op;
        cin >> op;
        if(op=="add"){
            o=1;
            cin >> x >> s;
            a.emplace_back(s,x);
        }else if(op=="delete"){
            o=2;
            cin >> x;
        }else if(op=="append"){
            o=3;
            cin >> s;
        }else if(op=="backspace"){
            o=4;
            cin >> x;
        }else{
            assert(false);
        }
    }
    sort(a.begin(),a.end(),[&](const pair<string,int> &x,const pair<string,int> &y){
        if(x.first.size()!=y.first.size())return x.first.size()>y.first.size();
        for(int i=0;i<x.first.size();i++){
            if(x.first[i]!=y.first[i]){
                return x.first[i]<y.first[i];
            }
        }
        return x.second<y.second;
    });
    for(int i=0;i<a.size();i++){
        ord[a[i].second]=i;
    }
    for(auto &[o,x,s]:qr){
        if(o==1){
            insert(x);
        }else if(o==2){
            erase(x);
        }else if(o==3){
            for(auto c:s){
                if(!cur->ch[c]){
                    cur->ch[c]=new Node(cur);
                }
                cur=cur->ch[c];
            }
        }else if(o==4){
            for(int i=0;i<x&&cur->par;i++){
                cur=cur->par;
            }
        }else{
            assert(false);
        }
        cout << cur->query() << "\n";
    }
}