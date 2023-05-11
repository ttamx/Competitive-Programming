#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=5005;
const int M=505;

int n,m;
ll p[N];
ll ans;

struct node{
        int val,sz;
        node *p;
        node(int val):val(val),sz(1),p(this){}
    };
typedef node* pnode;

void uni(pnode &t,pnode u,pnode v){
    if(u->sz<v->sz)swap(u,v);
    
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> m >> n;
    for(int i=1;i<=n;i++)cin >> p[i];
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){

        }
    }
}